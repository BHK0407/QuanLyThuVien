#pragma once
#ifndef SACH_H
#define SACH_H

#define MAX_SACH 1000

#include "constants.h"

// Khai bao cac bien dung chung
extern int sach_count;
extern char sach_ISBN[MAX_SACH][20];			// Ma sach ISBN
extern char sach_ten[MAX_SACH][100];			// Ten sach
extern char sach_tacGia[MAX_SACH][50];			// Tac gia
extern char sach_NXB[MAX_SACH][50];				// Nha xuat ban
extern int sach_namXB[MAX_SACH];				// Nam xuat ban
extern char sach_theLoai[MAX_SACH][50];			// The loai
extern double sach_giaTien[MAX_SACH];			// Gia tien cua sach
extern int sach_soLuong[MAX_SACH];				// So luong sach

// Cac ham xu ly
void danhSachSach();							// Xem danh sach Sach
void themSach();								// Them Sach
void capNhatSach();								// Chinh sua thong tin Sach
void xoaSach();									// Xoa Sach
void timSachTheoISBN();							// Tim Sach theo ISBN 
void timSachTheoTen();							// Tim Sach theo ten

#endif // SACH_H
