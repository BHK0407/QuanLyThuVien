#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "docGia.h"
#include "sach.h"
#include "phieuMuonTra.h"
#include "time_helpers.h"
#include "currency_vnd.h"
#include "thongKe.h"

// thongKeTongSach() la ham thong ke so luong sach trong thu vien
void thongKeTongSach() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach Sach!\n");
		return;
	}

	int demSach;
	fscanf(fptr, "%d\n", &demSach);
	fclose;

	printf("Tong so luong sach trong thu vien: %d\n", demSach);
	return;
}

// thongKeSachTheoTheLoai() la ham thong ke so luong sach theo the loai
void thongKeSachTheoTheLoai() {
	FILE* fptr = fopen("sach.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach Sach!\n");
		return;
	}

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

	fclose(fptr);

	char theLoai[100][50];
	int soLuong[100] = { 0 };
	int theLoaiCount = 0;

	for (int i = 0; i < sach_count; i++) {
		int timThay = 0;
		for (int j = 0; j < theLoaiCount; j++) {
			if (strcmp(theLoai[j], sach_theLoai[i]) == 0) {
				soLuong[j]++;
				timThay = 1;
				break;
			}
		}
		if (!timThay) {
			strcpy(theLoai[theLoaiCount], sach_theLoai[i]);
			soLuong[theLoaiCount++] = 1;
		}
	}
	printf("\n---Thong ke sach theo the loai---\n");
	for (int i = 0; i < theLoaiCount; i++) {
		printf("%-20s: %d quyen\n", theLoai[i], soLuong[i]);
	}
	return;
}

// thongKeTongDocGia() la ham thong ke so luong doc gia
void thongKeTongDocGia() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach doc gia!\n");
		return;
	}
	fscanf(fptr, "%d\n", &docgia_count);
	fclose(fptr);

	printf("Tong so luong doc gia: %d\n", docgia_count);
	return;
}

// thongKeDocGiaTheoGioiTinh() la ham thong ke so luong doc gia theo gioi tinh
void thongKeDocGiaTheoGioiTinh() {
	FILE* fptr = fopen("docgia.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach doc gia!\n");
		return;
	}
	fscanf(fptr, "%d\n", &docgia_count);

	int nam = 0, nu = 0;

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

		if (strcmp(docgia_gioiTinh[i], "Nam") == 0) {
			nam++;
		}
		else {
			nu++;
		}
	}
	fclose(fptr);

	printf("So luong do gia Nam: %d\n", nam);
	printf("So luong do gia Nu: %d\n", nu);
	return;
}

// thongKeSachDangMuon() la ham thong ke so sach dang muon
void thongKeSachDangMuon() {
	FILE* fptr = fopen("phieu.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach phieu Muon!\n");
		return;
	}

	phieu_count = 0;
	int tongSachDangMuon = 0;

	// lua tam ISBN va so luong muon cua tung sach
	char ISBN_muon[MAX_SACH][20];
	int soLuongMuon[MAX_SACH] = { 0 };
	int isbn_count = 0;

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
		if (phieu_ngayTraThucTe[phieu_count] == 0) {
			char isbnCopy[200];
			strcpy(isbnCopy, phieu_ISBN[phieu_count]);

			int start = 0;
			int length = strlen(isbnCopy);

			// Tach rieng danh sach ISBN ra de dem
			for (int i = 0; i <= length; i++) {
				if (isbnCopy[i] == ',' || isbnCopy[i] == '\0') {
					char isbnItem[20];
					int j = 0;
					for (int k = start; k < i; k++) {
						isbnItem[j++] = isbnCopy[k];
					}
					isbnItem[j] = '\0';
					start = i + 1;

					int trungKhop = 0;
					for (int x = 0; x < isbn_count; x++) {
						if (strcmp(ISBN_muon[x], isbnItem) == 0) {
							soLuongMuon[x]++;
							trungKhop = 1;
							break;
						}
					}

					if (!trungKhop && isbn_count < MAX_SACH) {
						strcpy(ISBN_muon[isbn_count], isbnItem);
						soLuongMuon[isbn_count] = 1;
						isbn_count++;
					}

					tongSachDangMuon++;

				}
			}
		}
		phieu_count++;
	}

	fclose(fptr);

	printf("\n=========== THONG KE SACH DANG DUOC MUON ===========\n");
	printf("Tong so sach dang duoc muon: %d\n", tongSachDangMuon);
	printf("-----------------------------------------------------\n");

	for (int i = 0; i < isbn_count; i++) {
		// Tim ten sach tuong ung trong danh muc sach
		char tenSach[50] = "Khong tim thay";
		for (int j = 0; j < sach_count; j++) {
			if (strcmp(sach_ISBN[j], ISBN_muon[i]) == 0) {
				strcpy(tenSach, sach_ten[j]);
				break;
			}
		}

		printf("%-15s | %-30s | %2d cuon dang muon\n",
			ISBN_muon[i], tenSach, soLuongMuon[i]);
	}

	printf("=====================================================\n");

	return;
}

// thongKeDocGiaTreHan() la ham thong ke danh sach doc gia tre han
void thongKeDocGiaTreHan() {
	FILE* fptr = fopen("phieu.txt", "r");
	if (fptr == NULL) {
		perror("Khong co du lieu ve danh sach phieu Muon!\n");
		return;
	}

	phieu_count = 0;
	int coTreHan = 0;

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
		int treNgay = between_days(phieu_ngayTraDuKien[phieu_count], phieu_ngayTraThucTe[phieu_count]);
		if (treNgay > 0) {
			printf("Phieu %s - Ma DG: %s - Tre %d ngay\n", phieu_id[phieu_count], phieu_maDocGia[phieu_count], treNgay);
			coTreHan = 1;
		}
		phieu_count++;
	}
	fclose(fptr);

	if (!coTreHan) {
		printf("Khong co doc gia nao tra tre han!\n");
	}
	return;
}

