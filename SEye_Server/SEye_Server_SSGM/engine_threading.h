/*	Renegade Scripts.dll
	Threading related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifdef WIN32
struct THREADNAME_INFO
{
	DWORD dwType; // must be 0x1000
	LPCSTR szName; // pointer to name (in user addr space)
	DWORD dwThreadID; // thread ID (-1=caller thread)
	DWORD dwFlags; // reserved for future use, must be zero
};

class CriticalSectionClass {
	unsigned int x;
public:
	void Lock();
	void Unlock()
	{
		x = 0;
	}
};

#else
class CriticalSectionClass {
	unsigned int x;
	unsigned int y;
public:
	void Lock()
	{
	}
	void Unlock()
	{
	}
};
#endif

void InitEngineThreading(unsigned int exe);
#ifdef WIN32
void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName);
#endif
