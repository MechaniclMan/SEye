/*	Renegade Scripts.dll
	Diagnostic routines
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
#include "engine_vector.h"
#include "engine_io.h"
#include "engine_diagnostics.h"
#include "engine_threading.h"
#include "engine_string.h"

DebugOutputClass::DebugOutputClass(const char *outputfile)
{
	OutputFile = newstr(outputfile);
}
DebugOutputClass::~DebugOutputClass()
{
	delete[] OutputFile;
}
void DebugOutputClass::Error(DebugLevel level, const char *message,...)
{
	if (level < DEBUGMESSAGE_LEVEL) 
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
}
void DebugOutputClass::ErrorW(DebugLevel level, const wchar_t *message,...)
{
	if (level < DEBUGMESSAGE_LEVEL) 
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfwprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
}
void DebugOutputClass::Trace(DebugLevel level, const char *message,...)
{
#ifdef DEBUG
	if (level < DEBUGMESSAGE_LEVEL) 
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
#endif
}
void DebugOutputClass::TraceW(DebugLevel level, const wchar_t *message,...)
{
#ifdef DEBUG
	if (level < DEBUGMESSAGE_LEVEL) 
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfwprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
#endif
}
void DebugOutputClass::Assert(bool condition, const char *message,...)
{
	if (condition)
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
}
void DebugOutputClass::AssertW(bool condition, const wchar_t *message,...)
{
	if (condition)
	{
		return;
	}
	va_list args;
	va_start(args,message);
	FILE *f = fopen(OutputFile,"at");
	if (f)
	{
		vfwprintf(f,message,args);
		fclose(f);
	}
	va_end(args);
}
void DebugOutputString(const char *message,...)
{
#ifdef DEBUG
	va_list args;
	char buffer[256];
	
	va_start(args,message);
	vsprintf(buffer,message,args);
	va_end(args);

	#ifdef WIN32
	OutputDebugString(buffer);
	#else
	Console_Output(buffer);
	#endif
#endif
}
