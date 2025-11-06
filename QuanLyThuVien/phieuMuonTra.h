#pragma once
#ifndef PHIEUMUONTRA_H

#define MAX_PHIEU 1000
#define MAX_SACH_MUON 5

extern int phieu_count;

// Khai bao cac bien dung chung
extern char phieu_id[MAX_PHIEU][20];					// Ma phieu
extern char phieu_maDocGia[MAX_PHIEU][20];				// Ma doc gia ghi tren phieu
extern int phieu_ngayMuon[MAX_PHIEU];					// Ngay muon
extern int phieu_ngayTraDuKien[MAX_PHIEU];				// Ngay du kien tra
extern int phieu_ngayTraThucTe[MAX_PHIEU];				// Ngay thuc te tra
extern int phieu_soSach[MAX_PHIEU];						// So sach muon
extern char phieu_ISBN[MAX_PHIEU][200];					// ISBN duoc note
extern double phieu_tienPhat[MAX_PHIEU];				// so tien phat

// Cac ham xu ly
void lapPhieuMuon();		// Ham lap phieu muon
void lapPhieuTra();			// Ham lap phieu tra

#endif // PHIEUMUONTRA_H
