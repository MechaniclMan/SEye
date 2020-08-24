/*	Renegade Scripts.dll
	Engine call common definitions
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
#ifdef WIN32
#ifdef SHADERS_EXPORTS
#include "shadereng.h"
#else
#include "engine.h"
#ifdef BHS_EXPORTS
#include "engine_d3d.h"
#include "engine_3dre.h"
#endif
#endif
#else
#include "engine.h"
#endif
int Exe = 6;
typedef void *(*rennew) (unsigned long size);
typedef void (*rendelete) (void *ptr);
typedef void (*ConsoleInput)(const char *);

#undef	new
#undef	delete

rennew RenNew = 0;
rennew RenVecNew = 0;
rendelete RenDelete;
rendelete RenVecDelete;
ConsoleInput Parse_Console_Input;
void *Output_To_Console;
bool *HasSSE;
bool *Has3DNow;

void InitEngineCommon(unsigned int exe)
{
	switch (Exe)
	{
	case 0: //game.exe
		{
			RenNew = (rennew)0x00672B70;
			RenVecNew = (rennew)0x00672B70;
			RenDelete = (rendelete)0x00672C80;
			RenVecDelete = (rendelete)0x00672C80;
			Parse_Console_Input = (ConsoleInput)0x004287E0;
			Output_To_Console = (void *)0x00428B50;
			HasSSE = (bool *)0x0084F702;
			Has3DNow = (bool *)0x0084F706;
		}
		break;
	case 1: //server.dat
		{
			RenNew = (rennew)0x00672410;
			RenVecNew = (rennew)0x00672410;
			RenDelete = (rendelete)0x00672520;
			RenVecDelete = (rendelete)0x00672520;
			Parse_Console_Input = (ConsoleInput)0x00428960;
			Output_To_Console = (void *)0x00428CD0;
			HasSSE = (bool *)0x0084E8EA;
			Has3DNow = (bool *)0x0084E8EE;
		}
		break;
	case 2: //RH73
		{
			RenNew = (rennew)0x0804AA48;
			RenVecNew = (rennew)0x0804A7B8;
			RenDelete = (rendelete)0x0804A8F8;
			RenVecDelete = (rendelete)0x0804AA08;
			Parse_Console_Input = (ConsoleInput)0x0805BBB8;
			Output_To_Console = (void *)0x0805BF40;
			HasSSE = (bool *)0x086E5302;
			Has3DNow = (bool *)0x086E5306;
		}
		break;
	case 3: //RH8
		{
			RenNew = (rennew)0x08053B04;
			RenVecNew = (rennew)0x08053A14;
			RenDelete = (rendelete)0x08053434;
			RenVecDelete = (rendelete)0x08053A54;
			Parse_Console_Input = (ConsoleInput)0x08063F56;
			Output_To_Console = (void *)0x080642B2;
			HasSSE = (bool *)0x0860DDA2;
			Has3DNow = (bool *)0x0860DDA6;
		}
		break;
	case 4: //leveledit, if this isnt here, things will break bigtime
		{
			RenNew = (rennew)0x007A783D;
			RenVecNew = (rennew)0x007A783D;
			RenDelete = (rendelete)0x007A7866;
			RenVecDelete = (rendelete)0x007A7866;
			Parse_Console_Input = (ConsoleInput)0;
			Output_To_Console = (void *)0;
			HasSSE = (bool *)0;
			Has3DNow = (bool *)0;
		}
		break;
	default:
		{
			RenNew = (rennew)0x0;
			RenVecNew = (rennew)0x0;
			RenDelete = (rendelete)0x0;
			RenVecDelete = (rendelete)0x0;
			Parse_Console_Input = (ConsoleInput)0;
			Output_To_Console = (void *)0;
			HasSSE = (bool *)0;
			Has3DNow = (bool *)0;
		}
		break;
	}
}

void Console_Input(const char *Input)
{
	if (strlen(Input) > 255)
	{
		return;
	}
	Parse_Console_Input(Input);
}

void THUNK Console_Output(const char *Output,...)
IMPLEMENT_THUNK(Output_To_Console)

#ifdef WIN32
#ifndef DEBUG
void* operator new (size_t nbytes)
{
	if (!RenNew)
	{
		InitEngine();
	}
	void *x = RenNew((unsigned long)nbytes);
	return x;
}

void* operator new[](size_t nbytes)
{
	if (!RenVecNew)
	{
		InitEngine();
	}
	void *x = RenVecNew((unsigned long)nbytes);
	return x;
}

void operator delete(void *ptr)
{
	RenDelete(ptr);
}

void operator delete[](void *ptr)
{
	RenVecDelete(ptr);
}
#endif
void* AllocMemory(size_t reportedSize)
{
 	if (!RenVecNew)
	{
		InitEngine();
	}
	void *x = RenVecNew((unsigned long)reportedSize);
	return x;
}

void DeallocMemory(void *reportedAddress)
{
	RenDelete(reportedAddress);
}
#endif

const unsigned char Code[19] = {0x6A,0x40,0xFF,0x74,0x24,0x0C,0xFF,0x74,0x24,0x0C,0xE8,0xC0,0xFF,0xFF,0xFF,0x83,0xC4,0x0C,0xC3};

#if (_MSC_VER == 1400)
#pragma comment(lib, "except.lib")
#pragma comment(linker, "/include:?__CxxSetUnhandledExceptionFilter@@YAHXZ")
void AppInvalidParameterHandler(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int line,	uintptr_t pReserved )
{
	DebugBreak();
}
#endif

void InitEngine()
{
#ifdef WIN32
#if (_MSC_VER == 1400)
	_set_invalid_parameter_handler(AppInvalidParameterHandler);
#endif
	if (!memcmp((void *)0x0078CE49,(void *)Code,19))
	{
		Exe = 0;
	}
	if (!memcmp((void *)0x0078C6E9,(void *)Code,19))
	{
		Exe = 1;
	}
	if (!memcmp((void *)0x0078790C,(void *)Code,19))
	{
		Exe = 4;
	}
#endif
	InitEngineCommon(Exe);
	InitEngineString(Exe);
	InitEngineThreading(Exe);
#ifdef SHADERS_EXPORTS
	InitEngineMath();
	InitEngineNet(Exe);
	InitEngineDef(Exe);
	InitEngineGame(Exe);
	InitEngineWeap(Exe);
	InitEngineObj(Exe);
	InitEngineObj2(Exe);
	InitEngineTDB(Exe);
	InitEngineIO(Exe);
	InitEngine3DRE(Exe);
	InitEngine3D(Exe);
#else
#ifndef PROXYDLL_EXPORTS
	InitEngineMath();
	InitEngineNet(Exe);
	InitEngineDef(Exe);
	InitEnginePlayer(Exe);
	InitEngineGame(Exe);
	InitEngineWeap(Exe);
	InitEnginePT(Exe);
	InitEngineObj(Exe);
	InitEngineObj2(Exe);
	InitEngineTDB(Exe);
	InitEngineDmg(Exe);
	InitEnginePhys(Exe);
	InitEngineIO(Exe);
#endif
#ifdef BHS_EXPORTS
#ifdef WIN32
	InitEngine3DRE(Exe);
#endif
#endif
#endif
}
