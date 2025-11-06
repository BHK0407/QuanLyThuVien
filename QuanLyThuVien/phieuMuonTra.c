#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "time_helpers.h"
#include "currency_vnd.h"
#include "phieuMuonTra.h"
#include "docGia.h"
#include "sach.h"

int phieu_count = 0;
char phieu_id[MAX_PHIEU][20];				// Ma phieu
char phieu_maDocGia[MAX_PHIEU][20];			// Ma doc gia ghi tren phieu
int phieu_ngayMuon[MAX_PHIEU];				// Ngay muon
int phieu_ngayTraDuKien[MAX_PHIEU];			// Ngay du kien tra
int phieu_ngayTraThucTe[MAX_PHIEU];			// Ngay thuc te tra
int phieu_soSach[MAX_PHIEU];				// So sanh muon				
char phieu_ISBN[MAX_PHIEU][200];			// ISBN duoc note
double phieu_tienPhat[MAX_PHIEU];			// so tien phat

// lapPhieuMuon() la ham lap phieu muon
void lapPhieuMuon() {
	FILE* fptrSach = fopen("sach.txt", "r");
	if (fptrSach == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}
	fscanf(fptrSach, "%d\n", &sach_count);
	for (int i = 0; i < sach_count; i++) {
		fscanf(fptrSach, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptrSach);

	FILE* fptrDocGia = fopen("docgia.txt", "r");
	if (fptrDocGia == NULL) {
		printf("Khong tim thay file du lieu docgia.txt\n");
		return;
	}

	fscanf(fptrDocGia, "%d\n", &docgia_count);
	for (int i = 0; i < docgia_count; i++) {
		fscanf(fptrDocGia,
			"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
			docgia_id[i],
			docgia_ten[i],
			docgia_CCCD[i],
			docgia_gioiTinh[i],
			docgia_email[i],
			docgia_diachi[i],
			&docgia_birth[i],
			&docgia_create_date[i],
			&docgia_expire_date[i]);
	}

	fclose(fptrDocGia);

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                       LAP PHIEU MUON SACH                    |\n");
	printf("|______________________________________________________________|\n\n");

	char strNgayMuon[20];

	// Nhap ma doc gia
	printf("Nhap ma doc gia: ");
	scanf("%s", phieu_maDocGia[phieu_count]);

	int timThayDocGia = 0;
	for (int i = 0; i < docgia_count; i++) {
		if (strcmp(docgia_id[i], phieu_maDocGia[phieu_count]) == 0) {
			timThayDocGia = 1;
			break;
		}
	}

	if (!timThayDocGia) {
		printf("Khong ton tai doc gia voi ma '%s' tren he thong!\n", phieu_maDocGia[phieu_count]);
		return;
	}

	// Nhap ngay muon sach
	printf("Nhap ngay muon sach(DD/MM/YYYY): ");
	scanf("%s", strNgayMuon);

	phieu_ngayMuon[phieu_count] = change_date(strNgayMuon);
	if (phieu_ngayMuon[phieu_count] == -1) {
		printf("Loi: Ngay muon khong hop le!\n");
		return;
	}

	// Ngay tra du kien = Ngay muon + 7 ngay
	phieu_ngayTraDuKien[phieu_count] = add_days(phieu_ngayMuon[phieu_count], 7);

	// Ma phieu sau khi tao: PYYYYMMDD_XXXX ("P" + "Ngay muon" + "4 so cuoi ma DG")
	int length = strlen(phieu_maDocGia[phieu_count]);
	char cuoiMaDG[5];
	strcpy(cuoiMaDG, phieu_maDocGia[phieu_count] + (length - 4));
	sprintf(phieu_id[phieu_count], "P%d_%s", phieu_ngayMuon[phieu_count], cuoiMaDG);

	// Nhap so sach muon
	printf("Nhap so luong sach muon (toi da %d): ", MAX_SACH_MUON);
	scanf("%d", &phieu_soSach[phieu_count]);
	if (phieu_soSach[phieu_count] > MAX_SACH_MUON) {
		printf("Vuot qua so sach duoc muon!\n");
		return;
	}

	char thongTinSachMuon[200] = "";
	for (int i = 0; i < phieu_soSach[phieu_count]; i++) {
		char isbnSachMuon[20];
		int timThaySachMuon = 0;

		do{
			printf("Nhap ISBN sach thu %d: ", i + 1);
			scanf("%s", isbnSachMuon);

			for (int j = 0; j < sach_count; j++) {
				if (strcmp(isbnSachMuon, sach_ISBN[j]) == 0) {
					timThaySachMuon = 1;
					break;
				}
			}

			if (!timThaySachMuon) {
				printf("Ma ISBN '%s' khong ton tai trong thu vien. Vui long nhap lai!\n", isbnSachMuon);
			}
		} while (!timThaySachMuon);

		strcat(thongTinSachMuon, isbnSachMuon);
		if (i < phieu_soSach[phieu_count] - 1) {
			strcat(thongTinSachMuon, ",");
		}
	}
	strcpy(phieu_ISBN[phieu_count], thongTinSachMuon);

	// Cap nhat lai so luong sach trong thu vien khi doc gia muon sach
	char isbnCopy[200];
	strcpy(isbnCopy, phieu_ISBN[phieu_count]);

	char isbnHienTai[30];
	int chiSoKyTu = 0;

	for (int k = 0; ; k++) {
		char kiTu = isbnCopy[k];

		//  ',' hoac ket thuc chuoi
		if (kiTu == ',' || kiTu == '\0') {
			isbnHienTai[chiSoKyTu] = '\0';  // Ket thuc ISBN hien tai

			// Kiem tra lai ISBN trong danh sach
			for (int j = 0; j < sach_count; j++) {
				if (strcmp(isbnHienTai, sach_ISBN[j]) == 0) {
					if (sach_soLuong[j] > 0) {
						sach_soLuong[j]--;
					}
					else {
						printf("Sach '%s' da het! Khong the muon.\n", sach_ten[j]);
					}
					break;
				}
			}

			chiSoKyTu = 0; // reset lai ban dau de doc ISBN tiep theo

			if (kiTu == '\0') break; // het chuoi thi thoat ra
		}
		else {
			isbnHienTai[chiSoKyTu++] = kiTu;
		}
	}

	FILE* fptrUpdate = fopen("sach.txt", "w");
	if (fptrUpdate == NULL) {
		perror("Khong mo duoc sach.txt de cap nhat!");
		return;
	}

	fprintf(fptrUpdate, "%d\n", sach_count);
	for (int i = 0; i < sach_count; i++) {
		fprintf(fptrUpdate, "%s|%s|%s|%s|%d|%s|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			sach_namXB[i],
			sach_theLoai[i],
			sach_giaTien[i],
			sach_soLuong[i]);
	}
	fclose(fptrUpdate);


	// Lap phieu muon thi ngay tra thuc te va tien phat chua tinh, nen gia tri mac dinh la 0
	phieu_ngayTraThucTe[phieu_count] = 0;
	phieu_tienPhat[phieu_count] = 0;

	FILE *fptr = fopen("phieu.txt", "a");
	if (fptr == NULL) {
		perror("Khong tim thay file du lieu phieu.txt\n");
		return;
	}

	fprintf(fptr, "id:%s|maDocGia:%s|ngayMuon:%d|ngayTraDuKien:%d|ngayTraThucTe:%d|soSach:%d|ISBN:%s|tienPhat:%.0f\n",
		phieu_id[phieu_count],
		phieu_maDocGia[phieu_count],
		phieu_ngayMuon[phieu_count],
		phieu_ngayTraDuKien[phieu_count],
		phieu_ngayTraThucTe[phieu_count],
		phieu_soSach[phieu_count],
		phieu_ISBN[phieu_count],
		phieu_tienPhat[phieu_count]);

	fclose(fptr);

	phieu_count++;


	// Cap nhat format de in ra man hinh
	char muon_str[20], traDK_str[20];		// ngay muon, ngay tra du kien, ngay tra thuc te
	format_date(phieu_ngayMuon[phieu_count - 1], muon_str);
	format_date(phieu_ngayTraDuKien[phieu_count - 1], traDK_str);


	printf("\nLap phieu muon thanh cong!\n");
	printf("Ma phieu: %s\n", phieu_id[phieu_count - 1]);
	printf("Ngay muon: %s | Ngay tra du kien: %s\n",
		muon_str,
		traDK_str);
	return;
}

// lapPhieuTra() la ham lap phieu tra
void lapPhieuTra() {
	FILE* fptrSach = fopen("sach.txt", "r");
	if (fptrSach == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}
	fscanf(fptrSach, "%d\n", &sach_count);
	for (int i = 0; i < sach_count; i++) {
		fscanf(fptrSach, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptrSach);

	FILE* fptrDocGia = fopen("docgia.txt", "r");
	if (fptrDocGia == NULL) {
		printf("Khong tim thay file du lieu docgia.txt\n");
		return;
	}

	fscanf(fptrDocGia, "%d\n", &docgia_count);
	for (int i = 0; i < docgia_count; i++) {
		fscanf(fptrDocGia,
			"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
			docgia_id[i],
			docgia_ten[i],
			docgia_CCCD[i],
			docgia_gioiTinh[i],
			docgia_email[i],
			docgia_diachi[i],
			&docgia_birth[i],
			&docgia_create_date[i],
			&docgia_expire_date[i]);
	}

	fclose(fptrDocGia);

	FILE* fptr = fopen("phieu.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu phieu.txt\n");
		return;
	}

	phieu_count = 0;
	while (fscanf(fptr, "id:%[^|]|maDocGia:%[^|]|ngayMuon:%d|ngayTraDuKien:%d|ngayTraThucTe:%d|soSach:%d|ISBN:%[^|]|tienPhat:%lf\n",
		phieu_id[phieu_count],
		phieu_maDocGia[phieu_count],
		&phieu_ngayMuon[phieu_count],
		&phieu_ngayTraDuKien[phieu_count],
		&phieu_ngayTraThucTe[phieu_count],
		&phieu_soSach[phieu_count],
		phieu_ISBN[phieu_count],
		&phieu_tienPhat[phieu_count]) == 8)
	{
		phieu_count++;
	}
	fclose(fptr);

	if (phieu_count == 0) {
		printf("Khong co phieu muon nao trong he thong!\n");
		return;
	}

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                       LAP PHIEU TRA SACH                     |\n");
	printf("|______________________________________________________________|\n\n");

	// Nhap ma phieu can tra
	char maPhieuCanTra[20];
	printf("Nhap ma phieu muon can tra: ");
	scanf("%s", maPhieuCanTra);

	int timThay = -1;
	for (int i = 0; i < phieu_count; i++) {
		if (strcmp(phieu_id[i], maPhieuCanTra) == 0) {
			timThay = i;
			break;
		}
	}

	if (timThay == -1) {
		printf("Khong tim thay ma phieu '%s'!\n", maPhieuCanTra);
		return;
	}

	// Nhap ngay tra thuc te
	char  traTT_[20];
	printf("Nhap ngay tra thuc te (DD/MM/YYYY): ");
	scanf("%s", traTT_);
	phieu_ngayTraThucTe[timThay] = change_date(traTT_);

	if (phieu_ngayTraThucTe[timThay] == -1) {
		printf("Ngay tra khong hop le!\n");
		return;
	}

	// Tinh tien phat neu nop tre
	int treNgay = between_days(phieu_ngayTraDuKien[timThay], phieu_ngayTraThucTe[timThay]);
	if (treNgay < 0) {
		treNgay = 0;
	}
	double tienPhatTre = 0;
	if (treNgay > 0) {
		tienPhatTre = treNgay * 5000;			// Phat 5000 VND/ngay
	}

	// Neu mat sach
	char matSach;
	printf("Co sach nao bi mat khong (y/n)? ");
	scanf(" %c", &matSach);

	char sachMatList[100][20];
	int soSachMat = 0;
	double tongTienPhatMat = 0;
	if (matSach == 'y' || matSach == 'Y') {

		int soSachMatNhap;
		printf("Nhap so luong sach bi mat: ");
		scanf("%d", &soSachMatNhap);

		for (int soSach = 0; soSach < soSachMatNhap; soSach++) {
			char isbnSachMat[20];
			printf("Nhap ISBN cua sach bi mat thu %d: ", soSach + 1);
			scanf("%s", sachMatList[soSachMat]);
			soSachMat++;

			int timThayISBN = 0;

			for (int i = 0; i < sach_count; i++) {
				if (strcmp(sach_ISBN[i], sachMatList[soSachMat - 1]) == 0) {
					double tienPhatSach = sach_giaTien[i] * 2;
					tongTienPhatMat += tienPhatSach;

					char tienPhat_str[50];
					format_vnd(tienPhatSach, tienPhat_str);
					printf("Sach '%s' bi mat. Phat: %s\n", sach_ISBN[i], tienPhat_str);

					timThayISBN = 1;
					break;
				}
			}
			if (!timThayISBN) {
				printf("ISBN '%s' khong ton tai trong he thong!\n", sachMatList[soSachMat - 1]);
			}
		}
	}

	char isbnList[200];
	strcpy(isbnList, phieu_ISBN[timThay]);

	int batDau = 0;
	int doDai = strlen(isbnList);
	for (int i = 0; i <= doDai; i++) {
		if (isbnList[i] == ',' || isbnList[i] == '\0') {
			char isbn[20];
			int j = 0;
			for (int k = batDau; k < i; k++) {
				isbn[j++] = isbnList[k];
			}
			isbn[j] = '\0';
			batDau = i + 1;

			int biMat = 0;
			for (int m = 0; m < soSachMat; m++) {
				if (strcmp(sachMatList[m], isbn) == 0) {
					biMat = 1;
					break;
				}
			}
			if (!biMat) {
				for (int x = 0; x < sach_count; x++) {
					if (strcmp(sach_ISBN[x], isbn) == 0) {
						sach_soLuong[x]++; // tra sach -> cong lai
						break;
					}
				}
			}
		}
	}

	phieu_tienPhat[timThay] = tienPhatTre + tongTienPhatMat;

	// Cap nhat lai file phieu
	fptr = fopen("phieu.txt", "w");
	if (fptr == NULL) {
		perror("Khong tim thay file du lieu phieu.txt\n");
		return;
	}

	for (int i = 0; i < phieu_count; i++) {
		fprintf(fptr, "id:%s|maDocGia:%s|ngayMuon:%d|ngayTraDuKien:%d|ngayTraThucTe:%d|soSach:%d|ISBN:%s|tienPhat:%.0f\n",
			phieu_id[i],
			phieu_maDocGia[i],
			phieu_ngayMuon[i],
			phieu_ngayTraDuKien[i],
			phieu_ngayTraThucTe[i],
			phieu_soSach[i],
			phieu_ISBN[i],
			phieu_tienPhat[i]);
	}
	fclose(fptr);

	// Cap nhat lai du lieu sach
	FILE* fptrUpdate = fopen("sach.txt", "w");
	if (fptrUpdate == NULL) {
		perror("Khong the mo file sach.txt de cap nhat!\n");
		return;
	}
		
	fprintf(fptrUpdate, "%d\n", sach_count);
		
	for (int i = 0; i < sach_count; i++) {
		fprintf(fptrUpdate, "%s|%s|%s|%s|%d|%s|%.6f|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			sach_namXB[i],
			sach_theLoai[i],
			sach_giaTien[i],
			sach_soLuong[i]);
	}

	fclose(fptrUpdate);
	
	char muon_str[20], tra_str[20], tienPhat_str[50];
	format_date(phieu_ngayMuon[timThay], muon_str);
	format_date(phieu_ngayTraThucTe[timThay], tra_str);
	format_vnd(phieu_tienPhat[timThay], tienPhat_str);

	printf("Ma phieu: %s\n", phieu_id[timThay]);
	printf("Ma doc gia: %s\n", phieu_maDocGia[timThay]);
	printf("Ngay muon: %s | Ngay tra: %s\n", muon_str, tra_str);
	printf("Tien phat: %s\n", tienPhat_str);

	return;
}


