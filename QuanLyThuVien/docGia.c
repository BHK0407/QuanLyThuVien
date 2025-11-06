#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "docGia.h"
#include "time_helpers.h"


int docgia_count;
char docgia_id[MAX_DOCGIA][20];			// ID cua doc gia
char docgia_ten[MAX_DOCGIA][100];		// ho ten doc gia
char docgia_CCCD[MAX_DOCGIA][20];		// CCCD cua doc gia
char docgia_gioiTinh[MAX_DOCGIA][10];	// gioi tinh cua doc gia
char docgia_email[MAX_DOCGIA][100];		// email cua doc gia
char docgia_diachi[MAX_DOCGIA][150];	// dia chi cua doc gia
int docgia_birth[MAX_DOCGIA];			// ngay sinh cua doc gia
int docgia_create_date[MAX_DOCGIA];		// ngay lap the
int docgia_expire_date[MAX_DOCGIA];		// ngay het han (48 thang sau)


// Ham danhSachDocGia() dung de xem danh sach doc gia trong thu vien
void danhSachDocGia() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr != NULL) {
		fscanf(fptr, "%d\n", &docgia_count);
		for (int i = 0; i < docgia_count; i++) {
			fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
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
	}

	if (docgia_count == 0) {
		printf("Chua co thong tin doc gia nao tren he thong.\n");
		return;
	}
	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                        DANH SACH DOC GIA                     |\n");
	printf("|______________________________________________________________|\n\n");

	char ngaySinh_str[20], ngayLap_str[20], ngayHetHan_str[20];

	for (int i = 0; i < docgia_count; i++) {
		format_date(docgia_birth[i], ngaySinh_str);
		format_date(docgia_create_date[i], ngayLap_str);
		format_date(docgia_expire_date[i], ngayHetHan_str);

		// Ma doc gia + Ho ten
		printf("%-10s | %-25s\n",
			docgia_id[i],
			docgia_ten[i]
		);

		// CCCD + Ngay Sinh
		printf("CCCD: %-12s | Ngay Sinh: %-10s\n",
			docgia_CCCD[i],
			ngaySinh_str
		);

		// Gioi tinh + email
		printf("Gioi Tinh: %-7s | Email: %-25s\n",
			docgia_gioiTinh[i],
			docgia_email[i]
		);

		// Dia chi
		printf("Dia chi: %-50s\n",
			docgia_diachi[i]
		);

		// Ngay lap the + Ngay Het han
		printf("Ngay Lap: %-10s | Het Han: %-10s\n",
			ngayLap_str,
			ngayHetHan_str
		);
		printf("--------------------------------------------------------------------------\n");
	}
}

// Ham themDocGia() dung de them doc gia
void themDocGia() {
	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                        THEM DOC GIA                          |\n");
	printf("|______________________________________________________________|\n\n");

	// Nhap ma doc gia
	printf("Nhap ma doc gia: ");
	scanf("%s", docgia_id[docgia_count]);

	// Nhap ho ten doc gia
	printf("Nhap ho ten doc gia: ");
	getchar();
	fgets(docgia_ten[docgia_count], 100, stdin);
	docgia_ten[docgia_count][strcspn(docgia_ten[docgia_count], "\n")] = 0;

	// Nhap CCCD
	printf("Nhap CCCD: ");
	scanf("%s", docgia_CCCD[docgia_count]);

	// Nhap gioi tinh
	printf("Nhap gioi tinh: ");
	scanf("%s", docgia_gioiTinh[docgia_count]);

	// Nhap email
	printf("Nhap email: ");
	scanf("%s", docgia_email[docgia_count]);

	// Nhap dia chi
	printf("Nhap dia chi: ");
	getchar();
	fgets(docgia_diachi[docgia_count], 150, stdin);
	docgia_diachi[docgia_count][strcspn(docgia_diachi[docgia_count], "\n")] = 0;

	// Nhap ngay sinh
	char strNgaySinh[20];
	printf("Nhap ngay sinh (DD/MM/YYYY): ");
	scanf("%s", strNgaySinh);

	docgia_birth[docgia_count] = change_date(strNgaySinh);
	if (docgia_birth[docgia_count] == -1) {
		printf("Loi: Ngay sinh khong hop le!\n");
		return;
	}

	// Nhap ngay lap the
	char strNgayLap[20];
	printf("Nhap ngay lap the (DD/MM/YYYY): ");
	scanf("%s", strNgayLap);

	docgia_create_date[docgia_count] = change_date(strNgayLap);
	if (docgia_create_date[docgia_count] == -1) {
		printf("Loi: Ngay khong hop le!\n");
		return;
	}

	docgia_expire_date[docgia_count] = add_months(docgia_create_date[docgia_count], 48);

	char ngayLap_str[20], ngayHetHan_str[20];
	format_date(docgia_create_date[docgia_count], ngayLap_str);
	format_date(docgia_expire_date[docgia_count], ngayHetHan_str);

	printf("\nThem doc gia thanh cong!\n");
	printf("Ma doc gia: %s\n", docgia_id[docgia_count]);
	printf("Ngay lap the: %s\n", ngayLap_str);
	printf("Ngay het han: %s\n", ngayHetHan_str);

	docgia_count++;

	FILE* fptr = fopen("docgia.txt", "w");
	if (fptr == NULL) {
		perror("Khong mo duoc file de luu danh sach doc gia!\n");
		return;
	}

	fprintf(fptr, "%d\n", docgia_count); // Luu so luong doc gia
	for (int i = 0; i < docgia_count; i++) {
		fprintf(fptr,"%s|%s|%s|%s|%s|%s|%d|%d|%d\n",
			docgia_id[i],
			docgia_ten[i],
			docgia_CCCD[i],
			docgia_gioiTinh[i],
			docgia_email[i],
			docgia_diachi[i],
			docgia_birth[i],
			docgia_create_date[i],
			docgia_expire_date[i]);
	}

	fclose(fptr);
	printf("Da luu danh sach doc gia moi nhat!\n");
}

// Ham xoaDocGia() dung de xoa thong tin doc gia
void xoaDocGia() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu docgia.txt\n");
		return;
	}

	// He thong se doc so luong doc gia o dau file
	if (fscanf(fptr, "%d\n", &docgia_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		docgia_count = 0;
		return;
	}

	for (int i = 0; i < docgia_count; i++) {
		fscanf(fptr,
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

	fclose(fptr);

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                        XOA DOC GIA                           |\n");
	printf("|______________________________________________________________|\n\n");

	if (docgia_count == 0) {
		printf("Chua co du lieu doc gia tren he thong!\n");
		return;
	}
	
	// Co the nhap ma doc gia hoac CCCD de xoa
	char thongTinNhap[50];
	printf("Nhap thong tin doc gia can xoa (Ma ID hoac CCCD): ");
	scanf("%s", thongTinNhap);

	int timThay = -1; // Chua tim thay

	for (int i = 0; i < docgia_count; i++) {
		if (strcmp(docgia_id[i], thongTinNhap) == 0 || strcmp(docgia_CCCD[i], thongTinNhap) == 0) {
			printf("Da tim thay doc gia: %s\n", docgia_ten[i]);
			timThay = i;
			break;
		}
	}

	if (timThay == -1) {
		printf("Khong tim thay doc gia!\n");
		return;
	}

	// Xac nhan co muon xoa khong
	char xacNhan;
	printf("Ban co chac muon xoa doc gia '%s' (y/n)? ", docgia_ten[timThay]);
	scanf(" %c", &xacNhan);
	
	if (xacNhan != 'y' && xacNhan != 'Y') {
		printf("Huy bo xoa doc gia.\n");
		return;
	}

	// Xoa doc gia tai timThay roi dich len
	for (int i = timThay; i < docgia_count - 1; i++) {
		strcpy(docgia_id[i], docgia_id[i + 1]);
		strcpy(docgia_ten[i], docgia_ten[i + 1]);
		strcpy(docgia_CCCD[i], docgia_CCCD[i + 1]);
		strcpy(docgia_gioiTinh[i], docgia_gioiTinh[i + 1]);
		strcpy(docgia_email[i], docgia_email[i + 1]);
		strcpy(docgia_diachi[i], docgia_diachi[i + 1]);
		docgia_birth[i] = docgia_birth[i + 1];
		docgia_create_date[i] = docgia_create_date[i + 1];
		docgia_expire_date[i] = docgia_expire_date[i + 1];
	}

	docgia_count--;

	fptr = fopen("docgia.txt", "w");
	if (fptr == NULL) {
		perror("Khong mo duoc file de luu danh sach doc gia!\n");
		return;
	}

	fprintf(fptr, "%d\n", docgia_count); // Luu so luong doc gia
	for (int i = 0; i < docgia_count; i++) {
		fprintf(fptr, "%s|%s|%s|%s|%s|%s|%d|%d|%d\n",
			docgia_id[i],
			docgia_ten[i],
			docgia_CCCD[i],
			docgia_gioiTinh[i],
			docgia_email[i],
			docgia_diachi[i],
			docgia_birth[i],
			docgia_create_date[i],
			docgia_expire_date[i]);
	}

	fclose(fptr);

	printf("Da xoa doc gia thanh cong!\n");


	return;
}

// Ham capNhatDocGia() dung de chinh sua thong tin doc gia
void capNhatDocGia() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu docgia.txt\n");
		return;
	}

	// Doc so luong doc gia o dau file
	if (fscanf(fptr, "%d\n", &docgia_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		docgia_count = 0;
		return;
	}

	for (int i = 0; i < docgia_count; i++) {
		fscanf(fptr,
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

	fclose(fptr);

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                       CAP NHAT DOC GIA                       |\n");
	printf("|______________________________________________________________|\n\n");

	if (docgia_count == 0) {
		printf("Chua co thong tin doc gia nao tren he thong");
		return;
	}

	char thongTinNhap[50];
	printf("Nhap thong tin doc gia can cap nhat (Ma ID hoac CCCD): ");
	scanf("%s", thongTinNhap);

	int timThay = -1;
	for (int i = 0; i < docgia_count; i++) {
		if (strcmp(docgia_id[i], thongTinNhap) == 0 || strcmp(docgia_CCCD[i], thongTinNhap) == 0) {
			timThay = i;
			break;
		}
	}

	if (timThay == -1) {
		printf("Khong tim thay doc gia!\n");
		return;
	}

	printf("\nDa tim thay doc gia: %s\n", docgia_ten[timThay]);

	// Hien thi lua chon de cap nhat

	int luaChonCapNhat;
	do{
		printf("Thong tin doc gia muon chinh sua?\n");
		printf("1. Ho ten\n");
		printf("2. Gioi tinh\n");
		printf("3. Email\n");
		printf("4. Dia chi\n");
		printf("5. Ngay sinh\n");
		printf("0. Hoan tat cap nhat\n");

		printf("Lua chon cap nhat: ");
		scanf("%d", &luaChonCapNhat);

		switch (luaChonCapNhat) {
			case 1:
				printf("Nhap Ho Ten moi: ");
				fgets(docgia_ten[timThay], 100, stdin);
				docgia_ten[timThay][strcspn(docgia_ten[timThay], "\n")] = 0;
				break;
			case 2:
				printf("Nhap gioi tinh moi: ");
				scanf("%s", docgia_gioiTinh[timThay]);
				break;
			case 3:
				printf("Nhap email moi: ");
				scanf("%s", docgia_email[timThay]);
				break;
			case 4:
				printf("Nhap dia chi moi: ");
				getchar();
				fgets(docgia_diachi[timThay], 150, stdin);
				docgia_diachi[timThay][strcspn(docgia_diachi[timThay], "\n")] = 0;
				break;
			case 5: {
				char strNgaySinh[20];
				printf("Nhap ngay sinh moi (DD/MM/YYYY): ");
				scanf("%s", strNgaySinh);
				int ngayMoi = change_date(strNgaySinh);
				if (ngayMoi == -1) {
					printf("Loi: Ngay sinh khong hop le.\n");
				}
				else
				{
				docgia_birth[timThay] = ngayMoi;
				}
				break;
			}
			case 0:
				printf("Hoan tat cap nhat thong tin doc gia!\n");
				break;
			default:
			printf("Lua chon khong hop le!\n");
		}
	} while (luaChonCapNhat != 0);

	fptr = fopen("docgia.txt", "w");
	if (fptr == NULL) {
		perror("Khong mo duoc file de luu danh sach doc gia!\n");
		return;
	}

	fprintf(fptr, "%d\n", docgia_count); // Luu so luong doc gia
	for (int i = 0; i < docgia_count; i++) {
		fprintf(fptr, "%s|%s|%s|%s|%s|%s|%d|%d|%d\n",
			docgia_id[i],
			docgia_ten[i],
			docgia_CCCD[i],
			docgia_gioiTinh[i],
			docgia_email[i],
			docgia_diachi[i],
			docgia_birth[i],
			docgia_create_date[i],
			docgia_expire_date[i]);
	}

	fclose(fptr);

	printf("Da cap nhat thong tin doc gia thanh cong!\n");

	return;
}

// Ham timDocGiaCCCD() dung de tim kiem doc gia theo CCCD
void timDocGiaCCCD() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu docgia.txt\n");
		return;
	}

	// He thong se doc so luong doc gia o dau file
	if (fscanf(fptr, "%d\n", &docgia_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		docgia_count = 0;
		return;
	}

	for (int i = 0; i < docgia_count; i++) {
		fscanf(fptr,
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

	fclose(fptr);

	if (docgia_count == 0) {
		printf("Chua co thong tin doc gia nao tren he thong");
		return;
	}

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                      TIM KIEM DOC GIA (CCCD)                 |\n");
	printf("|______________________________________________________________|\n\n");

	char cccdCanTim[20];		// gia tri de nhap tim CCCD
	printf("Nhap CCCD cua doc gia can tim: ");
	scanf("%s", cccdCanTim);

	int timThay = 0;

	for (int i = 0; i < docgia_count; i++) {
		if (strcmp(docgia_CCCD[i], cccdCanTim) == 0) {
			timThay = 1;

			char ngaySinh_str[20], ngayLap_str[20], ngayHetHan_str[20];
			format_date(docgia_birth[i], ngaySinh_str);
			format_date(docgia_create_date[i], ngayLap_str);
			format_date(docgia_expire_date[i], ngayHetHan_str);

			printf("---THONG TIN DOC GIA TIM DUOC---\n");
			
			// Ma doc gia + Ho ten
			printf("Ma doc gia: %-10s | Ho ten: %-25s\n",
				docgia_id[i],
				docgia_ten[i]
			);

			// CCCD + Ngay sinh
			printf("CCCD: %-12s | Ngay sinh: %-10s\n",
				docgia_CCCD[i],
				ngaySinh_str
			);

			// Gioi tinh + email
			printf("Gioi tinh: %-7s | Email: %-25s\n",
				docgia_gioiTinh[i],
				docgia_email[i]
			);

			// Dia chi
			printf("Dia chi: %-50s\n",
				docgia_diachi[i]
			);

			// Ngay lap the + Ngay Het han
			printf("Ngay Lap: %-10s | Het han: %-10s\n",
				ngayLap_str,
				ngayHetHan_str
			);
			
			printf("====================================================================\n");
			break;
		}
	}
	if (!timThay) {
		printf("Khong tim thay doc gia co CCCD: %s\n", cccdCanTim);
	}
	return;
}
