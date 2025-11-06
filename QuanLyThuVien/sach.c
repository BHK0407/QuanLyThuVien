#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "sach.h"
#include "currency_vnd.h"
#include <ctype.h>

int sach_count = 0;
char sach_ISBN[MAX_SACH][20];			// Ma sach ISBN
char sach_ten[MAX_SACH][100];			// Ten sach
char sach_tacGia[MAX_SACH][50];			// Tac gia
char sach_NXB[MAX_SACH][50];			// Nha xuat ban
int sach_namXB[MAX_SACH];				// Nam xuat ban
char sach_theLoai[MAX_SACH][50];		// The loai
double sach_giaTien[MAX_SACH];			// Gia tien cua sach
int sach_soLuong[MAX_SACH];				// So luong sach

// Ham danhSachSach() dung de xem danh sach Sach
void danhSachSach() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr != NULL) {
		fscanf(fptr, "%d\n", &sach_count);
		for (int i = 0; i < sach_count; i++) {
			fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
				sach_ISBN[i],
				sach_ten[i],
				sach_tacGia[i],
				sach_NXB[i],
				&sach_namXB[i],
				sach_theLoai[i],
				&sach_giaTien[i],
				&sach_soLuong[i]);
		}
	}

	if (sach_count == 0) {
		printf("Chua co sach nao tren he thong.\n");
		return;
	}
	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                        DANH SACH SACH                        |\n");
	printf("|______________________________________________________________|\n\n");
	
	char giaTien_str[50];

	for (int i = 0; i < sach_count; i++) {
		format_vnd(sach_giaTien[i], giaTien_str);

		// ISBN + Ten Sach
		printf("ISBN: %-15s | %-30s\n",
			sach_ISBN[i],
			sach_ten[i]
		);

		// Tac gia
		printf("Tac gia: %-20s\n",
			sach_tacGia[i]
		);

		// NXB + Nam Xuat Ban
		printf("NXB: %-20s | Nam XB: %-6d\n",
			sach_NXB[i],
			sach_namXB[i]
		);

		// The Loai
		printf("The loai: %-15s\n",
			sach_theLoai[i]
		);

		// Gia Tien + So Luong
		printf("Gia tien: %s | So luong: %-6d\n",
			giaTien_str,
			sach_soLuong[i]
		);

		printf("--------------------------------------------------------------------------\n");
	}
}

// Ham themSach() dung de them Sach
void themSach() {
	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                        THEM SACH                             |\n");
	printf("|______________________________________________________________|\n\n");

	// Nhap ma sach ISBN
	printf("Nhap ma sach - ISBN: ");
	scanf("%s", sach_ISBN[sach_count]);

	// Nhap ten sach
	printf("Nhap ten sach: ");
	getchar();
	fgets(sach_ten[sach_count], 100, stdin);
	sach_ten[sach_count][strcspn(sach_ten[sach_count], "\n")] = 0;

	// Nhap ten tac gia
	printf("Nhap ten tac gia: ");
	fgets(sach_tacGia[sach_count], 50, stdin);
	sach_tacGia[sach_count][strcspn(sach_tacGia[sach_count], "\n")] = 0;

	// Nhap NXB
	printf("Nhap NXB: ");
	fgets(sach_NXB[sach_count], 50, stdin);
	sach_NXB[sach_count][strcspn(sach_NXB[sach_count], "\n")] = 0;

	// Nhap nam xuat ban
	printf("Nhap nam xuat ban: ");
	scanf("%d", &sach_namXB[sach_count]);

	// Nhap the loai
	printf("Nhap the loai sach: ");
	getchar();
	fgets(sach_theLoai[sach_count], 50, stdin);
	sach_theLoai[sach_count][strcspn(sach_theLoai[sach_count], "\n")] = 0;

	// Nhap gia sach

	printf("Nhap gia tien cua sach: ");
	scanf("%lf", &sach_giaTien[sach_count]);
	char giaTien_str[50];
	format_vnd(sach_giaTien[sach_count], giaTien_str);


	// Nhap so luong quyen sach
	printf("Nhap so luong quyen sach: ");
	scanf("%d", &sach_soLuong[sach_count]);

	sach_count++;

	FILE* fptr = fopen("sach.txt", "w");
	if (fptr == NULL) {
		perror("Khong mo duoc file de lua sach!\n");
		return;
	}

	fprintf(fptr, "%d\n", sach_count);
	for (int i = 0; i < sach_count; i++) {
		fprintf(fptr,"%s|%s|%s|%s|%d|%s|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			sach_namXB[i],
			sach_theLoai[i],
			sach_giaTien[i],
			sach_soLuong[i]);
	}

	fclose(fptr);
	printf("Them sach thanh cong!\n");
}

// Ham capNhatSach() dung de chinh sua thong tin Sach
void capNhatSach() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	// He thong se doc so luong sach o dau file
	if (fscanf(fptr, "%d\n", &sach_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		sach_count = 0;
		return;
	}

	for (int i = 0; i < sach_count; i++) {
		fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptr);

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                      CAP NHAT THONG TIN SACH                 |\n");
	printf("|______________________________________________________________|\n\n");

	if (sach_count == 0) {
		printf("Chua co thong tin Sach nao tren he thong");
		return;
	}

	char isbnCapNhat[50];
	printf("Nhap ISBN cua Sach can cap nhat: ");
	scanf("%s", isbnCapNhat);

	int timThay = -1;	// Chua tim thay

	for (int i = 0; i < sach_count; i++) {
		if (strcmp(sach_ISBN[i], isbnCapNhat) == 0) {
			printf("Da tim thay Sach voi ma ISBN '%s'\n", sach_ISBN[i]);
			timThay = i;
			break;
		}
	}

	if (timThay == -1) {
		printf("Khong tim thay ISBN!\n");
		return;
	}

	int luaChonCapNhat;
	do{
		printf("Thong tin Sach muon chinh sua?\n");
		printf("1. Ten Sach\n");
		printf("2. Tac gia\n");
		printf("3. NXB\n");
		printf("4. Nam XB\n");
		printf("5. The loai\n");
		printf("6. Gia tien\n");
		printf("7. So luong\n");
		printf("0. Hoan tat cap nhat\n");

		printf("Lua chon cap nhat: ");
		scanf("%d", &luaChonCapNhat);

		switch (luaChonCapNhat) {
		case 1:
			printf("Nhap ten Sach moi: ");
			fgets(sach_ten[timThay], 100, stdin);
			sach_ten[timThay][strcspn(sach_ten[timThay], "\n")] = 0;
			break;
		case 2:
			printf("Nhap ten Tac gia moi: ");
			getchar();
			fgets(sach_tacGia[timThay], 50, stdin);
			sach_tacGia[timThay][strcspn(sach_tacGia[timThay], "\n")] = 0;
			break;
		case 3:
			printf("Nhap NXB moi: ");
			getchar();
			fgets(sach_NXB[timThay], 50, stdin);
			sach_NXB[timThay][strcspn(sach_NXB[timThay], "\n")] = 0;
			break;
		case 4:
			printf("Nhap nam XB moi: ");
			scanf("%d", &sach_namXB[timThay]);
			break;
		case 5:
			printf("Nhap The loai moi: ");
			getchar();
			fgets(sach_theLoai[timThay], 50, stdin);
			sach_theLoai[timThay][strcspn(sach_theLoai[timThay], "\n")] = 0;
			break;
		case 6: {
			char giaTien_str[50];
			printf("Nhap gia tien moi cho sach: ");
			scanf("%lf", giaTien_str);

			format_vnd(sach_giaTien[timThay], giaTien_str);
			break;
		}
		case 7:
			printf("Nhap so luong moi cho sach: ");
			scanf("%d", &sach_soLuong[timThay]);
			break;
		case 0:
			printf("Hoan tat cap nhat thong tin Sach!\n");
			break;
		default:
			printf("Lua chon khong hop le!\n");
		}
	} while (luaChonCapNhat != 0);

	fptr = fopen("sach.txt", "w");
	if (fptr == NULL) {
		perror("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	fprintf(fptr, "%d\n", sach_count);		// Luu so luong Sach
	for (int i = 0; i < sach_count; i++) {
		fprintf(fptr, "%s|%s|%s|%s|%d|%s|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			sach_namXB[i],
			sach_theLoai[i],
			sach_giaTien[i],
			sach_soLuong[i]);
	}

	fclose(fptr);

	printf("Da cap nhat thong Sach thanh cong!\n");
}

// Ham xoaSach() dung de xoa Sach khoi he thong
void xoaSach() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	// He thong se doc so luong sach o dau file
	if (fscanf(fptr, "%d\n", &sach_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		sach_count = 0;
		return;
	}

	for (int i = 0; i < sach_count; i++) {
		fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptr);

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                    XOA SACH KHOI HE THONG                    |\n");
	printf("|______________________________________________________________|\n\n");

	if (sach_count == 0) {
		printf("Chua co du lieu sach tren he thong!\n");
		return;
	}

	// De xoa sach khoi he thong can base dua tren tim sach theo ISBN
	// Nen se nhap ISBN de tim sach can xoa
	char isbnCanXoa[50];
	printf("Nhap ISBN cua Sach can xoa: ");
	scanf("%s", isbnCanXoa);

	int timThay = -1;	// Chua tim thay

	for (int i = 0; i < sach_count; i++) {
		if (strcmp(sach_ISBN[i], isbnCanXoa) == 0) {
			printf("Da tim thay Sach voi ma ISBN '%s'\n", sach_ISBN[i]);
			timThay = i;
			break;
		}
	}

	if (timThay == -1) {
		printf("Khong tim thay ISBN!\n");
		return;
	}

	// Xac nhan co muon xoa khong
	char xacNhan;
	printf("Ban co chac muon xoa Sach voi ma '%s' (y/n)? ", sach_ten[timThay]);
	scanf(" %c", &xacNhan);

	if (xacNhan != 'y' && xacNhan != 'Y') {
		printf("Huy bo xoa Sach.\n");
		return;
	}

	for (int i = timThay; i < sach_count - 1; i++) {
		strcpy(sach_ISBN[i], sach_ISBN[i + 1]);
		strcpy(sach_ten[i], sach_ten[i + 1]);
		strcpy(sach_tacGia[i], sach_tacGia[i + 1]);
		strcpy(sach_NXB[i], sach_NXB[i + 1]);
		sach_namXB[i] = sach_namXB[i + 1];;
		strcpy(sach_theLoai[i], sach_theLoai[i + 1]);
		sach_giaTien[i] = sach_giaTien[i + 1];
		sach_soLuong[i] = sach_soLuong[i + 1];
	}

	sach_count--;

	fptr = fopen("sach.txt", "w");
	if (fptr == NULL) {
		perror("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	fprintf(fptr, "%d\n", sach_count);		// Luu so luong Sach
	for (int i = 0; i < sach_count; i++) {
		fprintf(fptr, "%s|%s|%s|%s|%d|%s|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			sach_namXB[i],
			sach_theLoai[i],
			sach_giaTien[i],
			sach_soLuong[i]);
	}

	fclose(fptr);

	printf("Da xoa doc gia thanh cong!\n");

	return;
}

// Ham timSachTheoISBN() dung de tim Sach theo ISBN
void timSachTheoISBN() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	// He thong se doc so luong sach o dau file
	if (fscanf(fptr, "%d\n", &sach_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		sach_count = 0;
		return;
	}

	for (int i = 0; i < sach_count; i++) {
		fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptr);

	if (sach_count == 0) {
		printf("Chua co thong tin Sach nao tren he thong");
		return;
	}

	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                      TIM KIEM SACH (ISBN)                    |\n");
	printf("|______________________________________________________________|\n\n");

	char isbnCanTim[20];			// gia tri de nhap tim ISBN
	printf("Nhap ISBN cua Sach can tim: ");
	scanf("%s", isbnCanTim);

	int timThay = 0;

	for (int i = 0; i < sach_count; i++) {
		if (strcmp(sach_ISBN[i], isbnCanTim) == 0) {
			timThay = 1;

			char giaTien_str[50];
			format_vnd(sach_giaTien[i], giaTien_str);

			printf("\n---THONG TIN SACH TIM DUOC---\n");

			// ISBN + Ten Sach
			printf("ISBN: %-15s | %-30s\n",
				sach_ISBN[i],
				sach_ten[i]
			);

			// Tac gia
			printf("Tac gia: %-20s\n",
				sach_tacGia[i]
			);

			// NXB + Nam Xuat Ban
			printf("NXB: %-20s | Nam XB: %-6d\n",
				sach_NXB[i],
				sach_namXB[i]
			);

			// The Loai
			printf("The loai: %-15s\n",
				sach_theLoai[i]
			);

			// Gia Tien + So Luong
			printf("Gia tien: %s | So luong: %-6d\n",
				giaTien_str,
				sach_soLuong[i]
			);

			printf("====================================================================\n");
			break;
		}
	}
	if (!timThay) {
		printf("Khong tim thay Sach co ISBN: %s\n", isbnCanTim);
	}
	return;
}

// Ham timSachTheoTen() dung de tim Sach theo Ten
void timSachTheoTen() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		printf("Khong tim thay file du lieu sach.txt\n");
		return;
	}

	// He thong se doc so luong sach o dau file
	if (fscanf(fptr, "%d\n", &sach_count) != 1) {
		printf("File khong hop le hoac bi trong!\n");
		fclose(fptr);
		sach_count = 0;
		return;
	}

	for (int i = 0; i < sach_count; i++) {
		fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%lf|%d\n",
			sach_ISBN[i],
			sach_ten[i],
			sach_tacGia[i],
			sach_NXB[i],
			&sach_namXB[i],
			sach_theLoai[i],
			&sach_giaTien[i],
			&sach_soLuong[i]);
	}

	fclose(fptr);

	if (sach_count == 0) {
		printf("Chua co thong tin Sach nao tren he thong");
		return;
	}
	printf(" ______________________________________________________________\n");
	printf("|                                                              |\n");
	printf("|                     TIM KIEM SACH (THEO TEN)                 |\n");
	printf("|______________________________________________________________|\n\n");

	char tuKhoa[100];			// Tu khoa can tim Sach
	printf("Nhap ten Sach can tim: ");
	getchar();
	fgets(tuKhoa, sizeof(tuKhoa), stdin);
	tuKhoa[strcspn(tuKhoa, "\n")] = 0;

	if (strlen(tuKhoa) == 0) {
		printf("Khong duoc de trong, vui long nhap tu khoa!\n");
		return;
	}

	int timThay = 0;
	printf("\nKet qua tim kiem cho tu khoa: '%s'\n", tuKhoa);
	printf("--------------------------------------------------------------------------\n");

	char tuKhoaCoBan[100];			// tu khoa co ban dung de ghi nhan cac tu khoa thanh chu khong in hoa de tim kiem
	strcpy(tuKhoaCoBan, tuKhoa);

	for (int i = 0; tuKhoaCoBan[i]; i++) {
		tuKhoaCoBan[i] = tolower(tuKhoaCoBan[i]);
	}

	for (int j = 0; j < sach_count; j++) {
		int trungKhop = 0;

		if (strcmp(sach_ten[j], tuKhoa) == 0) {				// Kiem tra tu khoa trung khop voi ten sach
			trungKhop = 1;
		}
		else if (strstr(sach_ten[j], tuKhoa) != NULL) {		// Kiem tra tu khoa gan dung voi ten sach
			trungKhop = 1;
		}
		else
		{
			char tenSach_khongInHoa[100];
			strcpy(tenSach_khongInHoa, sach_ten[j]);
			for (int i = 0; tenSach_khongInHoa[i]; i++) {
				tenSach_khongInHoa[i] = tolower(tenSach_khongInHoa[i]);
			}
			if (strstr(tenSach_khongInHoa, tuKhoaCoBan) != NULL)
				trungKhop = 1;
		}

		// Neu tim thay bat ki ket qua nao thi in ket qua
		if (trungKhop) {				
			timThay = 1;

			char giaTien_str[50];
			format_vnd(sach_giaTien[j], giaTien_str);

			printf("\n---THONG TIN SACH TIM DUOC---\n");

			// ISBN + Ten Sach
			printf("ISBN: %-15s | %-30s\n",
				sach_ISBN[j],
				sach_ten[j]
			);

			// Tac gia
			printf("Tac gia: %-20s\n",
				sach_tacGia[j]
			);

			// NXB + Nam Xuat Ban
			printf("NXB: %-20s | Nam XB: %-6d\n",
				sach_NXB[j],
				sach_namXB[j]
			);

			// The Loai
			printf("The loai: %-15s\n",
				sach_theLoai[j]
			);

			// Gia Tien + So Luong
			printf("Gia tien: %s | So luong: %-6d\n",
				giaTien_str,
				sach_soLuong[j]
			);

			printf("====================================================================\n");
		}
	}
	if (!timThay) {
		printf("Khong tim thay Sach nao phu hop voi tu khoa '%s'.\n", tuKhoa);
	}
	return;
}