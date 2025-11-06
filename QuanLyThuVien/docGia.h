#pragma once

#ifndef DOCGIA_H
#define DOCGIA_H

#include "constants.h"

// Khai bao cac bien dung chung
extern int docgia_count;						 
extern char docgia_id[MAX_DOCGIA][20];			// ID cua doc gia
extern char docgia_ten[MAX_DOCGIA][100];		// ho ten doc gia
extern char docgia_CCCD[MAX_DOCGIA][20];		// CCCD cua doc gia
extern char docgia_gioiTinh[MAX_DOCGIA][10];	// gioi tinh cua doc gia
extern char docgia_email[MAX_DOCGIA][100];		// email cua doc gia
extern char docgia_diachi[MAX_DOCGIA][150];		// dia chi cua doc gia
extern int docgia_birth[MAX_DOCGIA];			// ngay sinh cua doc gia
extern int docgia_create_date[MAX_DOCGIA];		// ngay lap the
extern int docgia_expire_date[MAX_DOCGIA];		// ngay het han (48 thang sau)

// Cac ham xu ly
void danhSachDocGia();		// Ham danhSachDocGia() dung de xem danh sach doc gia trong thu vien
void themDocGia();			// Ham themDocGia() dung de them doc gia		
void xoaDocGia();			// Ham xoaDocGia() dung de xoa thong tin doc gia
void capNhatDocGia();		// Ham capNhatDocGia() dung de chinh sua thong tin doc gia
void timDocGiaCCCD();			// Ham timDocGiaCCCD() dung de tim kiem doc gia theo CCCD
#endif // DOCGIA_H
