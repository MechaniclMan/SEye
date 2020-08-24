/*	Renegade Scripts.dll
	Threading related Engine Calls
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

void *CriticalLock;

void InitEngineThreading(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
		case 1: //server.dat
			CriticalLock =	(void *)0x00402AA0;
			break;
		default: //RH7/RH8/LevelEdit
			CriticalLock = (void *)0;
			break;
	}
}

#ifdef WIN32
void THUNK CriticalSectionClass::Lock()
IMPLEMENT_THUNK(CriticalLock)

void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
{
dwThreadID; 
szThreadName;
#ifdef DEBUG
	THREADNAME_INFO info;
	{
		info.dwType = 0x1000;
		info.szName = szThreadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;
	}
	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
#endif
}

#endif
