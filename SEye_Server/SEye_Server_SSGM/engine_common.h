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
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#include <windows.h>
#endif
#define BHS_VERSION 3.4

#ifdef WIN32
#define cdeclx __cdecl
#define stdcallx _stdcall
#else
#define cdeclx
#define stdcallx
#endif

#ifdef WIN32
#define IMPLEMENT_THUNK(address) { \
	_asm { \
		mov eax, address \
	} \
	_asm { \
		jmp eax \
	} \
}
#define IMPLEMENT_THUNK_C(address) { \
	_asm { \
		mov eax, address \
	} \
	_asm { \
		jmp eax \
	} \
}
#define IMPLEMENT_THUNK_RETURN(address) { \
	_asm { \
		mov eax, address \
	} \
	_asm { \
		jmp eax \
	} \
}
#define IMPLEMENT_THUNK_RETURN_X(address) { \
	_asm { \
		mov eax, address \
	} \
	_asm { \
		jmp eax \
	} \
}
#define IMPLEMENT_THUNK_RETURN_V(address) { \
	_asm { \
		mov eax, address \
	} \
	_asm { \
		jmp eax \
	} \
}
#define THUNK __declspec(naked)
#else
#define THUNK
#ifdef BHS
#define IMPLEMENT_THUNK(address) { \
	__asm__ ( \
			"jmp *" #address "\n\t" \
		); \
}
#ifdef RH8
#define IMPLEMENT_THUNK_C(address) { \
	__asm__ ( \
			".byte 0x5B;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
}
#else
#define IMPLEMENT_THUNK_C(address) { \
	__asm__ ( \
			"addl $8,%esp			\n\t" \
			".byte 0x5B;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
}
#endif
#define IMPLEMENT_THUNK_RETURN(address) { \
	__asm__ ( \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_X(address) { \
	__asm__ ( \
			".byte 0x5B;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_V(address) { \
	__asm__ ( \
			".byte 0x5B;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return Vector3(0,0,0); \
}
#else
#ifdef RH8
#define IMPLEMENT_THUNK(address) { \
	__asm__ ( \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
}
#define IMPLEMENT_THUNK_C(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
}
#define IMPLEMENT_THUNK_RETURN(address) { \
	__asm__ ( \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_X(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_V(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return Vector3(0,0,0); \
}
#else
#define IMPLEMENT_THUNK(address) { \
	__asm__ ( \
			".byte 0x5D;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
}
#define IMPLEMENT_THUNK_C(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN(address) { \
	__asm__ ( \
			".byte 0x5D;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_X(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return 0; \
}
#define IMPLEMENT_THUNK_RETURN_V(address) { \
	__asm__ ( \
			".byte 0x8B;	\n\t" \
			".byte 0x1C;	\n\t" \
			".byte 0x24;	\n\t" \
			".byte 0xC9;	\n\t" \
			"jmp *" #address "\n\t" \
		); \
	return Vector3(0,0,0); \
}
#endif
#endif
#endif

#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);		(p)=NULL; } }
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#define SAFE_RELEASE(P)			{ if(P) { (P)->Release();	(P)=NULL; } }

#ifdef WIN32
void* AllocMemory(size_t reportedSize);
void DeallocMemory(void *reportedAddress);
#endif

void InitEngineCommon(unsigned int exe);
extern int Exe; //0 = game.exe,1 = server.dat,2 = RH73 LFDS,3 = RH8 LFDS,4 = leveledit,6 = invalid
void InitEngine(); //initalize pointers to engine functions
void Console_Input(const char *Input); //triggers console input (i.e. passes the string in as though it was typed into the console)
void Console_Output(const char *Output,...); //prints stuff to the console, works like printf
extern bool *HasSSE; //Is support for SSE available
extern bool *Has3DNow; //Is suppot for 3DNow available
