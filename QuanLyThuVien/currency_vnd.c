#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "currency_vnd.h"

// Ham format_vnd() dinh dang so tien thanh don vi VND
void format_vnd(double amount, char* thanhTien) {
	char soNhapVao[50];
	// In ra so khong co thap phan
	sprintf(soNhapVao, "%.0f", amount);

	int length = strlen(soNhapVao);
	int commaCount = (length - 1) / 3;
	int newLength = length + commaCount;

	thanhTien[0] = '\0'; // khoang trong truoc " VND"
	int j = newLength - 1;
	int count = 0;

	// Kiem tra nguoc de them dau phay ',' voi moi 3 so
	for (int i = length - 1; i >= 0; i--) {
		thanhTien[j--] = soNhapVao[i];
		count++;
		if (count == 3 && i != 0) {
			thanhTien[j--] = ',';
			count = 0;
		}
	}
	thanhTien[newLength] = '\0';

	// Them " VND"
	strcat(thanhTien, " VND");
}