/*	Renegade Scripts.dll
	Definitions and code related to functions in bhs.dll that are shared with bhs.dll
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
enum TextMessageEnum
{
	PublicMessage,
	TeamMessage,
	PrivateMessage,
	TMSGCommand, //special extra value for the TMSG console command
};
typedef void (*ChatHook) (int PlayerID,TextMessageEnum Type,const wchar_t *Message);
typedef void (*HostHook) (int PlayerID,TextMessageEnum Type,const char *Message);
typedef void (*ObjectCreateHook) (void *data,GameObject *obj);
typedef void (*PlayerJoin) (int PlayerID,const char *PlayerName);
typedef void (*PlayerLeave) (int PlayerID);
typedef void (*LoadLevelHook) ();
typedef void (*ConsoleOutputHook) (const char *output);
typedef void (*BHSVersion) (int PlayerID,float Version);
typedef void (*CRCHook) (unsigned int CRC,int PlayerID);
typedef void (*DataHook) (int PlayerID,unsigned int count, unsigned int *data);
typedef int (*PurchaseHook) (BaseControllerClass *base,GameObject *purchaser,unsigned int cost,unsigned int preset,const char *data);
typedef void (*PurchaseMonHook) (BaseControllerClass *base,GameObject *purchaser,unsigned int cost,unsigned int preset,unsigned int purchaseret,const char *data);

struct ObjectCreateHookStruct {
	ObjectCreateHook hook;
	void *data;
};

typedef void (*KeyHook) (void *data);
struct KeyHookStruct {
	KeyHook hook;
	const char *key;
	int PlayerID;
	void *data;
};

typedef void (*ShaderNotify) (void *data, int notify);
struct ShaderNotifyStruct {
	ShaderNotify hook;
	int ID;
	int PlayerID;
	void *data;
};

//values for Set_Fog_Mode and Set_Fog_Mode_Player
#define FOG_EXP 1 //Set_Fog_Density applies to this mode
#define FOG_EXP2 2 //Set_Fog_Density applies to this mode
#define FOG_LINEAR 3 //This is the default if you are using fog
