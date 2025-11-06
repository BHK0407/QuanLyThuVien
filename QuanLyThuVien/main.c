// Chuong Trinh QuanLyThuVien
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "docGia.h"
#include "time_helpers.h"
#include "sach.h"
#include "phieuMuonTra.h"
#include "thongKe.h"


// Tac cac Function tuong ung cho tung chuc nang cua chuong trinh quan ly thu vien
void menu_DocGia();
void menu_Sach();
void menu_Muon();
void menu_Tra();
void menu_ThongKe();

int main() {
	int luaChon;
	do {
		printf(" ______________________________________________________________\n");
		printf("|                                                              |\n");
		printf("|                DANH MUC QUAN LY THUC VIEN HCMUS              |\n");
		printf("|______________________________________________________________|\n");
		printf("|                                                              |\n");
		printf("|  1. Quan Ly Doc Gia                                          |\n");
		printf("|                                                              |\n");
		printf("|  2. Quan Ly Sach                                             |\n");
		printf("|                                                              |\n");
		printf("|  3. Lap Phieu Muon Sach                                      |\n");
		printf("|                                                              |\n");
		printf("|  4. Lap Phieu Tra Sach                                       |\n");
		printf("|                                                              |\n");
		printf("|  5. Cac Thong Ke Co Ban                                      |\n");
		printf("|                                                              |\n");
		printf("|  0. Thoat                                                    |\n");
		printf("|                                                              |\n");
		printf("|______________________________________________________________|\n\n");

		printf("Vui long chon danh muc da liet ke: ");
		scanf_s("%d", &luaChon);

		switch (luaChon) {
		case 1:
			menu_DocGia();
			break;
		case 2:
			menu_Sach();
			break;
		case 3:
			menu_Muon();
			break;
		case 4:
			menu_Tra();
			break;
		case 5:
			menu_ThongKe();
			break;
		case 0:
			printf("Tam biet!\n");
			break;
		default:
			printf("Xin loi, lua chon khong hop le. Vui long chon lai danh muc!\n");
		}
	} while (luaChon != 0);

	return 0;
}

// Tinh nang cua tung chuc nang trong QuanLyThuVien

void menu_DocGia() {
	int luaChon;
	do {
		printf(" ______________________________________________________________\n");
		printf("|                                                              |\n");
		printf("|                        QUAN LY DOC GIA                       |\n");
		printf("|______________________________________________________________|\n");
		printf("|                                                              |\n");
		printf("|  1. Xem danh sach doc gia trong thu vien                     |\n");
		printf("|                                                              |\n");
		printf("|  2. Them doc gia moi                                         |\n");
		printf("|                                                              |\n");
		printf("|  3. Chinh sua thong tin mot doc gia                          |\n");
		printf("|                                                              |\n");
		printf("|  4. Xoa thong tin doc gia                                    |\n");
		printf("|                                                              |\n");
		printf("|  5. Tim kiem doc gia theo CCCD                               |\n");
		printf("|                                                              |\n");
		printf("|  6. Tim kiem sach theo ho ten                                |\n");
		printf("|                                                              |\n");
		printf("|  0. Quay lai Menu Chinh                                      |\n");
		printf("|                                                              |\n");
		printf("|______________________________________________________________|\n\n");
		
		printf("Lua chon: ");
		scanf_s("%d", &luaChon);

		switch (luaChon) {
		case 1:
			danhSachDocGia();
			break;
		case 2:
			themDocGia();
			break;
        case 3:
			capNhatDocGia();
            break;
        case 4:
			xoaDocGia();
            break;
        case 5:
			timDocGiaCCCD();
            break;
        case 6:
            printf("Chuc nang tim theo ho ten dang duoc phat trien...\n");
            break;
        case 0:
            break;
        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
	} while (luaChon != 0);
}

void menu_Sach() {
	int luaChon;
	do {
		printf(" ______________________________________________________________\n");
		printf("|                                                              |\n");
		printf("|                        QUAN LY SACH                          |\n");
		printf("|______________________________________________________________|\n");
		printf("|                                                              |\n");
		printf("|  1. Xem danh sach cac sach trong thu vien                    |\n");
		printf("|                                                              |\n");
		printf("|  2. Them sach                                                |\n");
		printf("|                                                              |\n");
		printf("|  3. Chinh sua thong tin mot quyen sach                       |\n");
		printf("|                                                              |\n");
		printf("|  4. Xoa thong tin sach                                       |\n");
		printf("|                                                              |\n");
		printf("|  5. Tim kiem sach theo ISBN                                  |\n");
		printf("|                                                              |\n");
		printf("|  6. Tim kiem sach theo ten sach                              |\n");
		printf("|                                                              |\n");
		printf("|  0. Quay lai menu chinh                                      |\n");
		printf("|                                                              |\n");
		printf("|______________________________________________________________|\n\n");
		printf("Lua chon: ");
		scanf_s("%d", &luaChon);

		switch (luaChon) {
		case 1:
			danhSachSach();
			break;
		case 2:
			themSach();
			break;
		case 3:
			capNhatSach();
			break;
		case 4:
			xoaSach();
			break;
		case 5:
			timSachTheoISBN();
			break;
		case 6:
			timSachTheoTen();
			break;
		case 0:
			// Quay lai menu chinh
			break;
		default:
			printf("Lua chon khong hop le! Vui long chon lai: ");
		}
	} while (luaChon != 0);

}

void menu_Muon() {
	lapPhieuMuon();
}

void menu_Tra() {
	lapPhieuTra();
}
void menu_ThongKe() {
	int luaChon;
	do {
		printf(" ______________________________________________________________\n");
		printf("|                                                              |\n");
		printf("|                       THONG KE CO BAN                        |\n");
		printf("|______________________________________________________________|\n");
		printf("|                                                              |\n");
		printf("|  1. Thong ke so luong sach trong thu vien                    |\n");
		printf("|                                                              |\n");
		printf("|  2. Thong ke so luong sach theo the loai                     |\n");
		printf("|                                                              |\n");
		printf("|  3. Thong ke so luong doc gia                                |\n");
		printf("|                                                              |\n");
		printf("|  4. Thong ke so luong doc gia theo gioi tinh                 |\n");
		printf("|                                                              |\n");
		printf("|  5. Thong ke so sach dang duoc muon                          |\n");
		printf("|                                                              |\n");
		printf("|  6. Thong ke danh sach doc gia bi tre han                    |\n");
		printf("|                                                              |\n");
		printf("|  0. Quay tro lai menu chinh                                  |\n");
		printf("|                                                              |\n");
		printf("|______________________________________________________________|\n\n");

		printf("Lua chon: ");
		scanf_s("%d", &luaChon);

		switch (luaChon) {
		case 1:
			thongKeTongSach();
			break;
		case 2:
			thongKeSachTheoTheLoai();
			break;
		case 3:
			thongKeTongDocGia();
			break;
		case 4:
			thongKeDocGiaTheoGioiTinh();
			break;
		case 5:
			thongKeSachDangMuon();
			break;
		case 6:
			thongKeDocGiaTreHan();
			break;
		case 0:
			// Quay lai menu chinh
			break;
		default:
			printf("Lua chon khong hop le! Vui long chon lai: ");
		}
	} while (luaChon != 0);
}