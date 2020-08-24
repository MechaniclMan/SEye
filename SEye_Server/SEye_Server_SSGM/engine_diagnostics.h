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
#define DEBUGMESSAGE_LEVEL DEBUGLEVEL_INFO // All messages
enum DebugLevel
{
	DEBUGLEVEL_INFO = 0,
	DEBUGLEVEL_WARN = 1,
	DEBUGLEVEL_ERROR = 2
};
class DebugOutputClass
{
protected:
	char *OutputFile;
public:
	DebugOutputClass(const char *outputfile);
	~DebugOutputClass();
	void Error(DebugLevel level, const char *message,...);
	void ErrorW(DebugLevel level, const wchar_t *message,...);
	void Trace(DebugLevel level, const char *message,...);
	void TraceW(DebugLevel level, const wchar_t *message,...);
	void Assert(bool condition, const char *message,...);
	void AssertW(bool condition, const wchar_t *message,...);
};
void DebugOutputString(const char *message,...);
