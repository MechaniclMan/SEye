/* Renegade Scripts.dll
	String related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#include "scripts.h"
#include "engine_common.h"
#include "engine_threading.h"
#include "engine_string.h"

CriticalSectionClass *StringClass::m_Mutex;
unsigned int *StringClass::ReservedMask;
char *StringClass::m_TempStrings;
char **StringClass::m_EmptyString;
char *StringClass::m_NullChar;

CriticalSectionClass *WideStringClass::m_TempMutex;
wchar_t **WideStringClass::m_FreeTempPtr;
wchar_t **WideStringClass::m_ResTempPtr;
wchar_t **WideStringClass::m_EmptyString;
wchar_t *WideStringClass::m_NullChar;
int *WideStringClass::m_UsedTempStringCount;

void InitEngineString(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			StringClass::m_Mutex =						(CriticalSectionClass *)0x0083DC08;
			StringClass::ReservedMask =					(unsigned int *)0x0083EC10;
			StringClass::m_TempStrings =				(char *)0x0083DC0C;
			StringClass::m_EmptyString =				(char **)0x00809D38;
			StringClass::m_NullChar =					(char *)0x0083EC0C;
			WideStringClass::m_FreeTempPtr =			(wchar_t **)0x00809D40;
			WideStringClass::m_ResTempPtr =				(wchar_t **)0x0083F440;
			WideStringClass::m_EmptyString =			(wchar_t **)0x00809D3C;
			WideStringClass::m_NullChar =				(wchar_t *)0x0083F43C;
			WideStringClass::m_UsedTempStringCount =	(int *)0x0083F438;
			WideStringClass::m_TempMutex =				(CriticalSectionClass *)0x0083F024;
			break;
		case 1: //server.dat
			StringClass::m_Mutex =						(CriticalSectionClass *)0x0083CDF0;
			StringClass::ReservedMask =					(unsigned int *)0x0083DDF8;
			StringClass::m_TempStrings =				(char *)0x0083CDF4;
			StringClass::m_EmptyString =				(char **)0x00808F10;
			StringClass::m_NullChar =					(char *)0x0083DDF4;
			WideStringClass::m_FreeTempPtr =			(wchar_t **)0x00808F18;
			WideStringClass::m_ResTempPtr =				(wchar_t **)0x0083E628;
			WideStringClass::m_EmptyString =			(wchar_t **)0x00808F14;
			WideStringClass::m_NullChar =				(wchar_t *)0x0083E624;
			WideStringClass::m_UsedTempStringCount =	(int *)0x0083E620;
			WideStringClass::m_TempMutex =				(CriticalSectionClass *)0x0083E20C;
			break;
		case 2: //RH73
			StringClass::m_Mutex =						(CriticalSectionClass *)0x08BB5FDC;
			StringClass::ReservedMask =					(unsigned int *)0x086E8410;
			StringClass::m_TempStrings =				(char *)0x08BE8CE0;
			StringClass::m_EmptyString =				(char **)0x086E840C;
			StringClass::m_NullChar =					(char *)0x086E8408;
			WideStringClass::m_FreeTempPtr =			(wchar_t **)0x086E83E4;
			WideStringClass::m_ResTempPtr =				(wchar_t **)0x086E83F4;
			WideStringClass::m_EmptyString =			(wchar_t **)0x086E83E0;
			WideStringClass::m_NullChar =				(wchar_t *)0x086E83DC;
			WideStringClass::m_UsedTempStringCount =	(int *)0x086E83D8;
			WideStringClass::m_TempMutex =				(CriticalSectionClass *)0x08BB5FD4;
			break;
		case 3: //RH8
			StringClass::m_Mutex =						(CriticalSectionClass *)0x089D0CC0;
			StringClass::ReservedMask =					(unsigned int *)0x08610F84;
			StringClass::m_TempStrings =				(char *)0x089D0CE0;
			StringClass::m_EmptyString =				(char **)0x08610F80;
			StringClass::m_NullChar =					(char *)0x08610F7C;
			WideStringClass::m_FreeTempPtr =			(wchar_t **)0x08610F58;
			WideStringClass::m_ResTempPtr =				(wchar_t **)0x08610F68;
			WideStringClass::m_EmptyString =			(wchar_t **)0x08610F54;
			WideStringClass::m_NullChar =				(wchar_t *)0x08610F50;
			WideStringClass::m_UsedTempStringCount =	(int *)0x08610F4C;
			WideStringClass::m_TempMutex =				(CriticalSectionClass *)0x089CFC20;
			break;
		default:
			StringClass::m_Mutex =						(CriticalSectionClass *)0;
			StringClass::ReservedMask =					(unsigned int *)0;
			StringClass::m_TempStrings =				(char *)0;
			StringClass::m_EmptyString =				(char **)0;
			StringClass::m_NullChar =					(char *)0;
			WideStringClass::m_FreeTempPtr =			(wchar_t **)0;
			WideStringClass::m_ResTempPtr =				(wchar_t **)0;
			WideStringClass::m_EmptyString =			(wchar_t **)0;
			WideStringClass::m_NullChar =				(wchar_t *)0;
			WideStringClass::m_UsedTempStringCount =	(int *)0;
			WideStringClass::m_TempMutex =				(CriticalSectionClass *)0;
			break;
	}
}

StringClass::StringClass(StringClass& string,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	if (hint_temporary || string.Get_Length())
	{
		Get_String(string.Get_Length()+1,hint_temporary);
	}
	*this = string;
}

StringClass::StringClass(int initial_len,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	Get_String(initial_len,hint_temporary);
	m_Buffer[0] = *m_NullChar;
}

StringClass::~StringClass()
{
	Free_String();
}

StringClass& StringClass::operator=(const char* string)
{
	if (string)
	{
		int x = strlen(string);
		Uninitialised_Grow(x+1);
		Store_Length(x);
		memcpy(m_Buffer,string,x+1);
	}
	return *this;
}

StringClass& StringClass::operator=(StringClass& string)
{
	int x = string.Get_Length();
	Uninitialised_Grow(x+1);
	Store_Length(x);
	memcpy(m_Buffer,string.m_Buffer,x+1);
	return *this;
}

StringClass& StringClass::operator+=(const char* string)
{
	int len = Get_Length();
	int len2 = strlen(string);
	Resize(len+len2+1);
	Store_Length(len+len2);
	memcpy(Get_Buffer(len),string,len2);
	return *this;
}

StringClass& StringClass::operator+=(StringClass& string)
{
	int len = string.Get_Length();
	if (len)
	{
		int len2 = Get_Length();
		Resize(len+len2+1);
		Store_Length(len+len2);
		memcpy(Get_Buffer(len2),string,len+1);
	}
	return *this;
}

int StringClass::Get_Length()
{
	if (!Is_Empty())
	{
		if (!Get_Header()->length)
		{
			Get_Header()->length = strlen(m_Buffer);
		}
		return Get_Header()->length;
	}
	return 0;
}

int cdeclx StringClass::Format(char* format,...)
{
	va_list arg_list;
	va_start(arg_list,format);
	return Format_Args(format,arg_list);
}

int cdeclx StringClass::Format_Args(char* format,va_list& arg_list)
{
	char temp_buffer[512];
	int x = vsnprintf(temp_buffer,512,format,arg_list);
	*this = (const char *)temp_buffer;
	return x;
}

void StringClass::Get_String(int length,bool is_temp)
{
	if (!is_temp && !length)
	{
		m_Buffer = *m_EmptyString;
		return;
	}
	if (is_temp && (length <= 0xF8) && (*ReservedMask != 0xFF))
	{
		char *c = 0;
		m_Mutex->Lock();
		unsigned int i;
		for (i = 0;i < 8;i++)
		{
			if (!(*ReservedMask & (1 << i)))
			{
				break;
			}
		}
		if (i < 8)
		{
			*ReservedMask |= (1 << i);
			unsigned int x = (unsigned int)&m_TempStrings[0x800];
			x &= -0x800;
			c = (char *)x + (i << 8) + 8;
			Free_String();
			Set_Buffer_And_Allocated_Length(c,0xF8);
		}
		m_Mutex->Unlock();
		if (c)
		{
			return;
		}
	}
	if (length > 0)
	{
		char *x = Allocate_Buffer(length);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,length);
	}
	else
	{
		Free_String();
	}
}

void StringClass::Resize(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		char *x = Allocate_Buffer(new_len);
		strcpy(x,m_Buffer);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void StringClass::Uninitialised_Grow(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		char *x = Allocate_Buffer(new_len);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void StringClass::Free_String()
{
	if (!Is_Empty())
	{
		int x = (int)Get_Header();
		int y = (int)&m_TempStrings[0x800];
		int z = x ^ y;
		if ((z > 0) && (z < 0x800))
		{
			m_Buffer[0] = 0;
			m_Mutex->Lock();
			x = ((int)Get_Header()) >> 8;
			char c = (char)(x & 7);
			y = -(1 << c);
			*ReservedMask &= y;
			m_Mutex->Unlock();
			m_Buffer = *m_EmptyString;
		}
		else
		{
			delete[] Get_Header();
			m_Buffer = *m_EmptyString;
		}
	}
}

void StringClass::Store_Length(int length)
{
	if (!Is_Empty())
	{
		Get_Header()->length = length;
	}
}

void StringClass::Release_Resources()
{
	Free_String();
}

bool StringClass::Copy_Wide(const wchar_t *str)
{
	if (!str)
	{
		return false;
	}
	mbstate_t ps;
	memset(&ps,0,sizeof(ps));
	int len = wcsrtombs(0,&str,0,&ps);
	if (len > 0)
	{
		Uninitialised_Grow(len+1);
		wcsrtombs(m_Buffer,&str,len,&ps);
		m_Buffer[len] = 0;
		return true;
	}
	return false;
}

WideStringClass::WideStringClass(WideStringClass& string,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	if (hint_temporary || string.Get_Length())
	{
		Get_String(string.Get_Length()+1,hint_temporary);
	}
	*this = string;
}

WideStringClass::WideStringClass(int initial_len,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	Get_String(initial_len,hint_temporary);
	m_Buffer[0] = *m_NullChar;
}

WideStringClass::~WideStringClass()
{
	Free_String();
}

WideStringClass& WideStringClass::operator=(const wchar_t* string)
{
	if (string)
	{
		int x = wcslen(string);
		Uninitialised_Grow(x+1);
		Store_Length(x);
		memcpy(m_Buffer,string,(x+1)*sizeof(wchar_t));
	}
	return *this;
}

WideStringClass& WideStringClass::operator=(WideStringClass& string)
{
	int x = string.Get_Length();
	Uninitialised_Grow(x+1);
	Store_Length(x);
	memcpy(m_Buffer,string.m_Buffer,(x+1)*sizeof(wchar_t));
	return *this;
}

WideStringClass& WideStringClass::operator+=(const wchar_t* string)
{
	int len = Get_Length();
	int len2 = wcslen(string);
	Resize(len+len2+1);
	Store_Length(len+len2);
	memcpy(Get_Buffer(len),string,len2*sizeof(wchar_t));
	return *this;
}

WideStringClass& WideStringClass::operator+=(WideStringClass& string)
{
	int len = string.Get_Length();
	if (len)
	{
		int len2 = Get_Length();
		Resize(len+len2+1);
		Store_Length(len+len2);
		memcpy(Get_Buffer(len2),string,(len+1)*sizeof(wchar_t));
	}
	return *this;
}

int WideStringClass::Get_Length()
{
	if (!Is_Empty())
	{
		if (!Get_Header()->length)
		{
			Get_Header()->length = wcslen(m_Buffer);
		}
		return Get_Header()->length;
	}
	return 0;
}

int cdeclx WideStringClass::Format(wchar_t* format,...)
{
	va_list arg_list;
	va_start(arg_list,format);
	return Format_Args(format,arg_list);
}

int cdeclx WideStringClass::Format_Args(wchar_t* format,va_list& arg_list)
{
	wchar_t temp_buffer[512];
	int x = vswprintf(temp_buffer,512,format,arg_list);
	*this = (const wchar_t *)temp_buffer;
	return x;
}

void WideStringClass::Get_String(int length,bool is_temp)
{
	if (!is_temp && !length)
	{
		m_Buffer = *m_EmptyString;
		return;
	}
	if (is_temp && (length <= 0xFF) && (*m_UsedTempStringCount <= 3))
	{
		m_TempMutex->Lock();
		for (unsigned int i = 0;i < 3;i++)
		{
			if (m_FreeTempPtr[i])
			{
				m_ResTempPtr[i] = m_FreeTempPtr[i];
				m_FreeTempPtr[i] = 0;
				Free_String();
				Set_Buffer_And_Allocated_Length(m_ResTempPtr[i],0x100);
				m_UsedTempStringCount++;
			}
		}
		m_TempMutex->Unlock();
	}
	else
	{
		wchar_t *x = Allocate_Buffer(length);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,length);
	}
}

void WideStringClass::Resize(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		wchar_t *x = Allocate_Buffer(new_len);
		wcscpy(x,m_Buffer);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void WideStringClass::Uninitialised_Grow(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		wchar_t *x = Allocate_Buffer(new_len);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void WideStringClass::Free_String()
{
	if (!Is_Empty())
	{
		bool temp = false;
		for (int i = 0;i < 3;i++)
		{
			if (m_Buffer == m_ResTempPtr[i])
			{
				m_TempMutex->Lock();
				m_Buffer[0] = 0;
				m_FreeTempPtr[i] = m_Buffer;
				m_ResTempPtr[i] = 0;
				(*m_UsedTempStringCount)--;
				temp = true;
				m_TempMutex->Unlock();
				break;
			}
		}
		if (!temp)
		{
			delete[] Get_Header();
		}
		m_Buffer = *m_EmptyString;
	}
}

void WideStringClass::Store_Length(int length)
{
	if (!Is_Empty())
	{
		Get_Header()->length = length;
	}
}

void WideStringClass::Release_Resources()
{
}

bool WideStringClass::Convert_From(const char *str)
{
	if (!str)
	{
		return false;
	}
	mbstate_t ps;
	memset(&ps,0,sizeof(ps));
	int len = mbsrtowcs(0,&str,0,&ps);
	if (len > 0)
	{
		Uninitialised_Grow(len+1);
		mbsrtowcs(m_Buffer,&str,len,&ps);
		m_Buffer[len] = 0;
		return true;
	}
	return false;
}

bool WideStringClass::Is_ANSI()
{
	if (m_Buffer)
	{
		if (m_Buffer[0])
		{
			wchar_t *temp = m_Buffer;
			do
			{
				if (*temp > 0xFF)
				{
					return false;
				}
			} while (*temp);
		}
	}
	return true;
}

const wchar_t *CharToWideChar(const char *str)
{
	int length = strlen(str);
	wchar_t *text = new wchar_t[length+1];
	mbstowcs(text,str,length+1);
	return text;
}

const char *WideCharToChar(const wchar_t *wcs)
{
	if (!wcs)
	{
		char *c = new char[2];
		c[0] = 0;
		c[1] = 0;
		return c;
	}
	int length = wcslen(wcs);
	char *text = new char[length+1];
	wcstombs(text,wcs,length+1);
	return text;
}

char *cpystr(const char* src,char* dst)
{
	memcpy(dst,src,strlen(src)+1);
	return dst;
};

wchar_t *cpywcs(const wchar_t* src,wchar_t* dst)
{
	memcpy(dst,src,wcslen(src)+2);
	return dst;
};
#ifndef DEBUG
char *newstr(const char *str)
{
	unsigned long len = strlen(str)+1;
	char *s = new char[len];
	memcpy(s,str,len);
	return s;	
};
wchar_t *newwcs(const wchar_t *str)
{
	unsigned long len = wcslen(str)+2;
	wchar_t *s = new wchar_t[len];
	memcpy(s,str,len*2);
	return s;
};
#endif
