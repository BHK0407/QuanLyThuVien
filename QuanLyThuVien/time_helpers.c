#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "docGia.h"
#include "time_helpers.h"

/*
	Trong thu vien "time_helpers.h" co cac ham chinh
	- int change_date(const char *str);						// Chuyen chuoi "DD/MM/YYYY sang YYYYMMDD
	- void format_date(int yyyymmdd, char* out);			// Chuyen chuoi "YYYYMMDD sang DD/MM/YYYY"
	- int between_days(int first_date, int last_date);		// So ngay trong khoang tu first_date den last_date (last_date - first_date)
	- int add_months(int yyyymmdd, int months);				// Cong them N thang vao ngay
	- int add_days(int yyyymmdd, int days);					// Cong them N ngay
	Co cac ham phu tro
	- check_leapYear(int year);								// Dung de kiem tra nam nhuan
	- long long total_days(int year, int month, int day);	// Ham phu tro chuyen 1 ngay sang tong so ngay
*/

// Ham phu tro kiem tra nam nhuan
int check_leapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Ham phu tro chuyen 1 ngay sang tong so ngay
long long total_days(int year, int month, int day) {
	int array_dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	long long total = 0;

	//  Cong so ngay cua cac nam 
	for (int i = 1; i < year; i++) {
		total += check_leapYear(i) ? 366 : 365;
	}

	// Cong so ngay cua cac thang truoc trong nam
	for (int i = 1; i < month; i++) {
		total += array_dayInMonth[i - 1];
		if (i == 2 && check_leapYear(year)) {
			total += 1;
		}
	}
	// Cong cac ngay
	total += day;
	return total;
}

int change_date(const char* str) {
	int day, month, year;

	// Tao ban sao và loai bo '\n' 
	char clean[20];
	strcpy(clean, str);
	clean[strcspn(clean, "\n")] = 0;

	// Doc chuoi DD/MM/YYYY
	if (sscanf(clean, "%d/%d/%d", &day, &month, &year) != 3) {
		return -1;  // Khong du 3 truong thong tin
	}

	// Kiem tra hop le
	if (year < 1000 || month < 1 || month > 12 || day < 1 || day > 31) {
		return -1;
	}

	int array_dayInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		array_dayInMonth[1] = 29; // Nam nhuan
	}
	if (day > array_dayInMonth[month - 1]) {
		return -1;
	}

	return year * 10000 + month * 100 + day;
}

void format_date(int yyyymmdd, char* out) {
	int year = yyyymmdd / 10000;
	int month = (yyyymmdd / 100) % 100;
	int day = yyyymmdd % 100;

	// Kiem tra ngay
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
		strcpy(out, "Ngay nhap vao khong hop le!");
		return;
	}

	sprintf(out, "%02d/%02d/%04d", day, month, year);
}

int between_days(int first_date, int last_date) {
	int year1 = first_date / 10000, month1 = (first_date / 100) % 100, day1 = first_date % 100;
	int year2 = last_date / 10000, month2 = (last_date / 100) % 100, day2 = last_date % 100;

	long long days1 = total_days(year1, month1, day1);
	long long days2 = total_days(year2, month2, day2);

	return (int)(days2 - days1);
}

int add_months(int yyyymmdd, int months) {
	int year = yyyymmdd / 10000;
	int month = (yyyymmdd / 100) % 100;
	int day = yyyymmdd % 100;

	month += months; // Cong them so thang

	// Neu vuot qua 12 thang, dieu chinh lai nam cho hop ly
	year += (month - 1) / 12;
	month = ((month - 1) % 12) + 1;

	int array_dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Kiem tra nam nhuan
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		array_dayInMonth[1] = 29;
	}

	// Neu so ngay vuot qua so ngay cua thang moi, dieu chinh
	if (day > array_dayInMonth[month - 1]) {
		day = array_dayInMonth[month - 1];
	}

	return year * 10000 + month * 100 + day;
}

int add_days(int yyyymmdd, int days) {
	int year = yyyymmdd / 10000;
	int month = (yyyymmdd / 100) % 100;
	int day = yyyymmdd % 100;

	int array_dayInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	while (days > 0) {
		// Kiem tra nam nhuan
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			array_dayInMonth[1] = 29; // Nam nhuan
		}
		else{
			array_dayInMonth[1] = 28; // Nam khong nhuan
		}

		if (day < array_dayInMonth[month - 1]) {
			day++;
		}
		else{
			day = 1;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
		days--;
	}
	return year * 10000 + month * 100 + day;
}