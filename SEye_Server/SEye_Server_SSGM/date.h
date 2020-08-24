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
#ifndef DATE_H
#define DATE_H

class date {
protected:
	int month;
	int day;
	int year;
	static char out_string[25];
	static char last_date[25];
	static char format;
	int days_this_month(void);
public:
	date(void);
	void refreshdate();
	int set_date(int in_month, int in_day, int in_year);
	int get_month(void) { return month; };
	int get_day(void) { return day; };
	int get_year(void) { return year; };
	void set_date_format(int format_in) { format = (char)format_in; };
	char *get_date_string(void);
	char *get_month_string(void);
};

#endif
