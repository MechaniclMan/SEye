/*	Renegade Scripts.dll
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
class StringClass {
	char* m_Buffer;
public:
	static unsigned int *ReservedMask;
	static char *m_TempStrings;
	static char **m_EmptyString;
	static char *m_NullChar;
	static CriticalSectionClass *m_Mutex;
	struct _HEADER {
		int allocated_length;
		int length;
	};
	StringClass()
	{
		m_Buffer = *m_EmptyString;
	}
	StringClass(StringClass& string,bool hint_temporary);
	StringClass(int initial_len,bool hint_temporary);
	~StringClass();
	StringClass& operator=(const char* string);
	StringClass& operator=(StringClass& string);
	StringClass& operator+=(const char* string);
	StringClass& operator+=(StringClass& string);
	int Get_Length();
	int cdeclx Format(char* format,...);
	int cdeclx Format_Args(char* format,va_list& arg_list);
	void Release_Resources();
	void Get_String(int length,bool is_temp);
	void Resize(int new_len);
	void Uninitialised_Grow(int new_len);
	void Free_String();
	void Store_Length(int length);
	bool Copy_Wide(const wchar_t *str);
	_HEADER *Get_Header()
	{
		return (_HEADER*)(m_Buffer-8);
	}
	char& operator[](int index)
	{
		if (index >= 0 && index < Get_Length())
		{
			return m_Buffer[index];
		}
		return *m_NullChar;
	}
	operator const char*()
	{
		return m_Buffer;
	}
	bool Is_Empty()
	{
		if (m_Buffer == *m_EmptyString)
		{
			return true;
		}
		return false;
	}
	void Set_Buffer_And_Allocated_Length(char *buffer, int length)
	{
		m_Buffer = buffer;
		Store_Allocated_Length(length);
		Store_Length(0);
	}
	void Store_Allocated_Length(int length)
	{
		if (!Is_Empty())
		{
			Get_Header()->allocated_length = length;
		}
	}
	char* Get_Buffer(int index)
	{
		return &m_Buffer[index];
	}
	char *Peek_Buffer()
	{
		return m_Buffer;
	}
	int Get_Allocated_Length()
	{
		if (!Is_Empty())
		{
			return Get_Header()->allocated_length;
		}
		return 0;
	}
	char* Allocate_Buffer(int len)
	{
		char *x = new char[len+8];
		_HEADER *h = (_HEADER *)x;
		h->allocated_length = len;
		h->length = 0;
		x += 8;
		return x;
	}
	void Erase(int start, int count)
	{
		int x = Get_Length();
		if (start < x)
		{
			if ((start + count) > x)
			{
				count = x - start;
			}
			memmove(m_Buffer+start,m_Buffer+start+count,(x - (start + count)) + 1);
			Store_Length(x-count);
		}
	}
	int Compare(char* compare)
	{
		return strcmp(m_Buffer,compare);
	}
	int Compare_No_Case(char* compare)
	{
		return _stricmp(m_Buffer,compare);
	}
};

class WideStringClass {
	wchar_t* m_Buffer;
public:
	static wchar_t **m_FreeTempPtr;
	static wchar_t **m_ResTempPtr;
	static wchar_t **m_EmptyString;
	static wchar_t *m_NullChar;
	static int *m_UsedTempStringCount;
	static CriticalSectionClass *m_TempMutex;
	static void Release_Resources();
	struct _HEADER {
		int allocated_length;
		int length;
	};
	WideStringClass()
	{
		m_Buffer = *m_EmptyString;
	}
	WideStringClass(WideStringClass& string,bool hint_temporary);
	WideStringClass(int initial_len,bool hint_temporary);
	~WideStringClass();
	WideStringClass& operator=(const wchar_t* string);
	WideStringClass& operator=(WideStringClass& string);
	WideStringClass& operator+=(const wchar_t* string);
	WideStringClass& operator+=(WideStringClass& string);
	int Get_Length();
	int cdeclx Format(wchar_t* format,...);
	int cdeclx Format_Args(wchar_t* format,va_list& arg_list);
	void Get_String(int length,bool is_temp);
	void Resize(int new_len);
	void Uninitialised_Grow(int new_len);
	void Free_String();
	void Store_Length(int length);
	bool Convert_From(const char *str);
	bool Is_ANSI();
	_HEADER *Get_Header()
	{
		return (_HEADER*)(m_Buffer - 8 / sizeof(wchar_t));
	}
	wchar_t& operator[](int index)
	{
		if (index >= 0 && index < Get_Length())
		{
			return m_Buffer[index];
		}
		return *m_NullChar;
	}
	operator const wchar_t*()
	{
		return m_Buffer;
	}
	bool Is_Empty()
	{
		if (m_Buffer == *m_EmptyString)
		{
			return true;
		}
		return false;
	}
	void Set_Buffer_And_Allocated_Length(wchar_t *buffer, int length)
	{
		m_Buffer = buffer;
		Store_Allocated_Length(length);
		Store_Length(0);
	}
	void Store_Allocated_Length(int length)
	{
		if (!Is_Empty())
		{
			Get_Header()->allocated_length = length;
		}
	}
	wchar_t* Get_Buffer(int index)
	{
		return &m_Buffer[index];
	}
	wchar_t *Peek_Buffer()
	{
		return m_Buffer;
	}
	int Get_Allocated_Length()
	{
		if (!Is_Empty())
		{
			return Get_Header()->allocated_length;
		}
		return 0;
	}
	wchar_t* Allocate_Buffer(int len)
	{
		wchar_t *x = new wchar_t[len+(8 / sizeof(wchar_t))];
		_HEADER *h = (_HEADER *)x;
		h->allocated_length = len;
		h->length = 0;
		x += (8 / sizeof(wchar_t));
		return x;
	}
	void Erase(int start, int count)
	{
		int x = Get_Length();
		if (start < x)
		{
			if ((start + count) > x)
			{
				count = x - start;
			}
			memmove(m_Buffer+start,m_Buffer+start+count,((x - (start + count)) + 1)*sizeof(wchar_t));
			Store_Length(x-count);
		}
	}
	int Compare(wchar_t* compare)
	{
		return wcscmp(m_Buffer,compare);
	}
	int Compare_No_Case(wchar_t* compare)
	{
		return _wcsicmp(m_Buffer,compare);
	}
};

void InitEngineString(unsigned int exe);
const wchar_t *CharToWideChar(const char *str); //convert a char to a wide char
const char *WideCharToChar(const wchar_t *wcs); //convert a wide char to a char
#ifdef DEBUG
#define newstr(str) cpystr(str,new char[strlen(str)+1])
#define newwcs(str) cpywcs(str,new wchar_t[wcslen(str)+2])
char *cpystr(const char* src,char* dst); //UNSAFE copies a char to another char and returns the char, no size checking
wchar_t *cpywcs(const wchar_t* src,wchar_t* dst); //UNSAFE copies a wchar_t to another wchar_t and returns the char, no size checking
#else
char *newstr(const char *str); //duplicate a character string
wchar_t *newwcs(const wchar_t *str);  //duplicate a wide character string
#endif
