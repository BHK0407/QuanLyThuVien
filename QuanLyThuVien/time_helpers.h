#pragma once
#ifndef TIMEHELPERS_H
#define TIMEHELPERS_H

// Cac ham xu ly thoi gian
int check_leapYear(int year);							// Dung de kiem tra nam nhuan
long long total_days(int year, int month, int day);		// Ham phu tro chuyen 1 ngay sang tong so ngay
int change_date(const char *str);						// Chuyen chuoi "DD/MM/YYYY sang YYYYMMDD"
void format_date(int yyyymmdd, char* out);				// Chuyen chuoi "YYYYMMDD sang DD/MM/YYYY"
int between_days(int first_date, int last_date);		// So ngay trong khoang tu first_date den last_date (last_date - first_date)
int add_months(int yyyymmdd, int months);				// Cong them N thang vao ngay
int add_days(int yyyymmdd, int days);				// Cong them N ngay

#endif // TIMEHELPERS_H
