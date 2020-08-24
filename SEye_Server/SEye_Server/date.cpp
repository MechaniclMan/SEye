/*	Renegade Scripts.dll
	Date functions
	Copyright 2007 Jonathan Wilson, Vloktboky

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mmgr.h"
#include "date.h"

char date::format;
char date::out_string[25];
char date::last_date[25];

date::date(void)
{
	time_t time_date;
	struct tm *current_date;
	time_date = time(NULL);
	current_date = localtime(&time_date);
	month = current_date->tm_mon + 1;
	day = current_date->tm_mday;
	year = current_date->tm_year + 1900;
	format = 3;
}

void date::refreshdate()
{
	time_t time_date;
	struct tm *current_date;
	time_date = time(NULL);
	current_date = localtime(&time_date);
	month = current_date->tm_mon + 1;
	day = current_date->tm_mday;
	year = current_date->tm_year + 1900;
	format = 3;
}

int date::set_date(int in_month, int in_day, int in_year)
{
	int temp = 0;
	int max_days;
	if (in_year < 1500)
	{
		year = 1500;
		temp = 1;
	}
	else if (in_year > 2200)
	{
		year = 2200;
		temp = 1;
	}
	else
		year = in_year;
	if (in_month < 1)
	{
		month = temp = 1;
	}
	else if (in_month > 12)
	{
		month = 12;
		temp = 1;
	}
	else
		month = in_month;
	max_days = days_this_month();
	if (in_day < 1)
	{
		day = temp = 1;
	}
	else if (in_day > max_days)
	{
		day = max_days;
		temp = 1;
	}
	else
		day = in_day;
	return temp;
}

static char *month_string[13] = {" ", "Jan", "Feb", "Mar", "Apr",
"May", "Jun", "Jul", "Aug",
"Sep", "Oct", "Nov", "Dec"};

char *date::get_month_string(void)
{
	return month_string[month];
}

char *date::get_date_string(void)
{
	switch (format)
	{
	case 2:
		sprintf(out_string, "%02d/%02d/%02d", month, day, year - 1900);
		break;
	case 3: 
#ifdef WIN32
		if (day < 10) 
		{
			sprintf(out_string, "%d-%d-%04d", month, day, year);
		}
		else
		{
			sprintf(out_string, "%d-%02d-%04d", month, day, year);
		}
		strcpy(last_date,out_string);
#else
		if (day < 10)
			sprintf(out_string, "%d-%d-%d", month-1, day, year-1900);
		else
			sprintf(out_string, "%d-%02d-%d", month-1, day, year-1900);
#endif
		break;
	case 4:
		sprintf(out_string, "%d %s %04d", day, month_string[month], year);
		break;
	case 1:
	default:
		sprintf(out_string, "%d-%02d-%04d", month, day, year);
		break;
	}
	return out_string;
}

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int date::days_this_month(void)
{
	if (month != 2)
		return days[month];
	if (year % 4)
		return 28;
	if (year % 100)
		return 29;
	if (year % 400)
		return 28;
	return 29;
}
