/*	Renegade Scripts.dll
	Example Plugin Code
	Copyright 2007 Whitedragon(MDB), Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

/*  This is designed to serve as both an example on how to make a plugin and to give users the basic framework of a plugin.
    The plugin is simple: it creates an object creation hook and attaches the script "Plugin_Example_Script" to all objects.
	The script prints out a message whenever an object is created or destroyed.
	There are also examples of the new format for bhs.dll hooks.
*/

#include "scripts.h"
#include <stdarg.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include "Winsock2.h"
#include <windows.h>
#endif
#include "engine.h"
#include "gmmain.h"
#include "plugin.h"
#include "Seye_Server.h"



void ObjectHookCall(void *, GameObject *o)
{
	SEye_Server::ObjectHook(o);
}


void Plugin_Load() 
{
	ObjectCreateHookStruct *ObjectHookStruct = new ObjectCreateHookStruct;
	ObjectHookStruct->hook = ObjectHookCall;
	ObjectHookStruct->data = 0;
	AddObjectCreateHook(ObjectHookStruct);

	WSADATA wsaData;
	if(WSAStartup(0x202, &wsaData))
	{
		MessageBox(0, "Error: Could not open Winsock", "Error", MB_OK);
		exit(0);
	}

	SEye_Server::Load();
	
}


void Plugin_Unload() 
{
	SEye_Server::Unload();
}


extern "C" 
{
DLLEXPORT void SSGM_Chat_Hook(int ID, int Type, const wchar_t *Msg) 
{
	SEye_Server::ChatHook(ID, Type, Msg);
}

DLLEXPORT void SSGM_Level_Loaded_Hook() 
{
	SEye_Server::Level_Loaded();
}

}
