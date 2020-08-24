/*	Renegade Scripts.dll
	Classes and engine calls that deal with strings.tdb
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
#include "engine_vector.h"
#include "engine_string.h"
#include "engine_io.h"
#include "engine_def.h"
#include "engine_tdb.h"
#include "engine_net.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_weap.h"

#ifdef WIN32
typedef wchar_t *(*GetVehicleName) ();
#else
typedef wchar_t *(*GetVehicleName) (GameObject *obj);
#endif

typedef TDBObjClass *(*GetTDBObject) (unsigned long ID);

GetTDBObject Get_TDB_Object;
GetVehicleName Get_VehicleName;

void InitEngineTDB(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Get_TDB_Object = (GetTDBObject)0x0076C5B0;
			Get_VehicleName = (GetVehicleName)0x0067C740;
			break;
		case 1: //server.dat
			Get_TDB_Object = (GetTDBObject)0x0076BE50;
			Get_VehicleName = (GetVehicleName)0x0067BFE0;
			break;
		case 2: //RH73
			Get_TDB_Object = (GetTDBObject)0x08346D80;
			Get_VehicleName = (GetVehicleName)0x08188FD0;
			break;
		case 3: //RH8
			Get_TDB_Object = (GetTDBObject)0x082FBF90;
			Get_VehicleName = (GetVehicleName)0x08172B74;
			break;
		default:
			Get_TDB_Object = (GetTDBObject)0;
			Get_VehicleName = (GetVehicleName)0;
			break;
	}
}

const char *Get_Translated_String(unsigned long ID)
{
	if (ID < 1000)
	{
		return newstr("No String");
	}
	return WideCharToChar(*Get_TDB_Object(ID-1000)->Get_String());
}

const wchar_t *Get_Wide_Translated_String(unsigned long ID)
{
	if (ID < 1000)
	{
		return L"No String";
	}
	return *Get_TDB_Object(ID-1000)->Get_String();
}

const char *Get_Translated_Preset_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "";
	}
	GameObject *o = As_DamageableGameObj(obj);
	if (!o)
	{
		return "";
	}
	DamageableGameObjDef *d = (DamageableGameObjDef *)Get_Definition(obj);
	return Get_Translated_String(d->TranslatedNameID);
}

const wchar_t *Get_Current_Wide_Translated_Weapon(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = ((ArmedGameObj *)o)->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return Get_Wide_Translated_String(w->Vector[w->current]->WeaponDef->IconNameID);
	}
	return 0;
}

const char *Get_Current_Translated_Weapon(GameObject *obj)
{
	return WideCharToChar(Get_Current_Wide_Translated_Weapon(obj));
}

const char *Get_Translated_Weapon(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = ((ArmedGameObj *)o)->WeaponBag;
	if (w->Vector[position])
	{
		return Get_Translated_String(w->Vector[position]->WeaponDef->IconNameID);
	}
	return 0;
}

const char *Get_Team_Name(int Team)
{
	if (!Team)
	{
		return Get_Translated_String(7198);
	}
	else if (Team == 1)
	{
		return Get_Translated_String(7199);
	}
	return newstr("Neutral");
}

const wchar_t *Get_Wide_Vehicle_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return L"Vehicle";
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		return L"Vehicle";
	}
#ifdef WIN32
	_asm {
		mov ecx, o
		mov ebx, Get_VehicleName
		call ebx
	}
#else
	return Get_VehicleName(o);
#endif
}

const char *Get_Vehicle_Name(GameObject *obj)
{
	return WideCharToChar(Get_Wide_Vehicle_Name(obj));
}

const char *Get_Translated_Definition_Name(const char *preset)
{
	DamageableGameObjDef *d = (DamageableGameObjDef *)Find_Named_Definition(preset);
	if (!d)
	{
		return "";
	}
	return Get_Translated_String(d->TranslatedNameID);
}
