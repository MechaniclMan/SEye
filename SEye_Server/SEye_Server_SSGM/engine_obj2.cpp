/*	Renegade Scripts.dll
	Soldier, Vehicle and Script Zone related engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu, Joshua "NeoSaber" Kraft

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
#include "engine_string.h"
#include "engine_vector.h"
#include "engine_io.h"
#include "engine_net.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_game.h"
#include "engine_obj2.h"

#ifdef WIN32
typedef void (*ReInit) (DefinitionClass *def);
typedef bool (*IsAvailable) (void);
typedef bool (*RequestVehicle) (int Preset,float Delay,GameObject *Owner);
typedef void (*ToggleFlyMode) (void);
typedef unsigned int (*GetCount) ();
#else
typedef void (*ReInit) (GameObject *obj,DefinitionClass *def);
typedef bool (*IsAvailable) (GameObject *obj);
typedef bool (*RequestVehicle) (GameObject *obj,int Preset,float Delay,GameObject *Owner);
typedef void (*ToggleFlyMode) (GameObject *obj);
typedef unsigned int (*GetCount) (GameObject *obj);
#endif
typedef GameObject *(*CreateLibraryObject) (const char *preset);

void *Grant_Supplies;
void *FindClosestZone;
void *InsideMe;
CreateLibraryObject Create_Library_Object;
void *overlap;
ReInit SoldierReInit;
IsAvailable Is_Available_For_Purchase;
RequestVehicle Request_Vehicle;
ToggleFlyMode ToggleFly;
void *CheckTransitions;
GetCount GetVehicleCount;
char *SpawnCharNod;
char *SpawnCharGDI;

GameObject THUNK *Find_Closest_Zone(Vector3 &Location,unsigned int Type)
IMPLEMENT_THUNK_RETURN(FindClosestZone)
unsigned int THUNK Overlap_Test(const OBBoxClass &box,const Vector3 &v)
IMPLEMENT_THUNK_RETURN(overlap)
bool THUNK ScriptZoneGameObj::Inside_Me(SmartGameObj *obj)
IMPLEMENT_THUNK_RETURN(InsideMe)
void THUNK GrantSupplies(GameObject *obj)
IMPLEMENT_THUNK(Grant_Supplies);
bool THUNK Check_Transitions(GameObject *obj,bool unk)
IMPLEMENT_THUNK_RETURN(CheckTransitions);

void InitEngineObj2(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			overlap = (void *)0x00616B90;
			Create_Library_Object = (CreateLibraryObject)0x006C6420;
			FindClosestZone = (void *)0x00722B90;
			InsideMe = (void *)0x00722B40;
			Grant_Supplies = (void *)0x00470AC0;
			SoldierReInit = (ReInit)0x006C7410;
			Is_Available_For_Purchase = (IsAvailable)0x006EE010;
			Request_Vehicle = (RequestVehicle)0x006EE1A0;
			ToggleFly = (ToggleFlyMode)0x006CFC80;
			CheckTransitions = (void *)0x006D55C0;
			GetVehicleCount = (GetCount)0x006EE060;
			SpawnCharGDI = (char *)0x007F5428;
			SpawnCharNod = (char *)0x007F5440;
			break;
		case 1: //server.dat
			overlap = (void *)0x00616430;
			Create_Library_Object = (CreateLibraryObject)0x006C5CC0;
			FindClosestZone = (void *)0x00722150;
			InsideMe = (void *)0x00722100;
			Grant_Supplies = (void *)0x00470230;
			SoldierReInit = (ReInit)0x006C6CB0;
			Is_Available_For_Purchase = (IsAvailable)0x006ED5D0;
			Request_Vehicle = (RequestVehicle)0x006ED760;
			ToggleFly = (ToggleFlyMode)0x006CF520;
			CheckTransitions = (void *)0x006D4E60;
			GetVehicleCount = (GetCount)0x006ED620;
			SpawnCharGDI = (char *)0x007F442C;
			SpawnCharNod = (char *)0x007F4444;
			break;
		case 2: //RH73
			overlap = (void *)0x083257A0;
			Create_Library_Object = (CreateLibraryObject)0x0813868C;
			FindClosestZone = (void *)0x08156204;
			InsideMe = (void *)0x081561B0;
			Grant_Supplies = (void *)0x080C472C;
			SoldierReInit = (ReInit)0x0815C23C;
			Is_Available_For_Purchase = (IsAvailable)0x0818C8C4;
			Request_Vehicle = (RequestVehicle)0x0818CAF0;
			ToggleFly = (ToggleFlyMode)0x08168740;
			CheckTransitions = (void *)0x0817EDAC;
			GetVehicleCount = (GetCount)0x0818C900;
			SpawnCharGDI = (char *)0x086151D5;
			SpawnCharNod = (char *)0x086151C0;
			break;
		case 3: //RH8
			overlap = (void *)0x082E22F0;
			Create_Library_Object = (CreateLibraryObject)0x081287B6;
			FindClosestZone = (void *)0x08143F90;
			InsideMe = (void *)0x08143F44;
			Grant_Supplies = (void *)0x080BC8D8;
			SoldierReInit = (ReInit)0x0814A676;
			Is_Available_For_Purchase = (IsAvailable)0x008175F7A;
			Request_Vehicle = (RequestVehicle)0x08176184;
			ToggleFly = (ToggleFlyMode)0x08155762;
			CheckTransitions = (void *)0x08169ADC;
			GetVehicleCount = (GetCount)0x08175FBE;
			SpawnCharGDI = (char *)0x084FB353;
			SpawnCharNod = (char *)0x084FB33E;
			break;
		default:
			overlap = (void *)0;
			Create_Library_Object = (CreateLibraryObject)0;
			FindClosestZone = (void *)0;
			InsideMe = (void *)0;
			Grant_Supplies = (void *)0;
			SoldierReInit = (ReInit)0;
			Is_Available_For_Purchase = (IsAvailable)0;
			Request_Vehicle = (RequestVehicle)0;
			ToggleFly = (ToggleFlyMode)0;
			CheckTransitions = (void *)0;
			GetVehicleCount = (GetCount)0;
			SpawnCharGDI = (char *)0;
			SpawnCharNod = (char *)0;
			break;
	}
}

GameObject *Get_Vehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		char *c = (char *)o;
		c += 0x98C;
		unsigned long *l = (unsigned long *)c;
		GameObject *vehicle = (GameObject *)*l;
		if (vehicle)
		{
			GameObject *v = As_VehicleGameObj(vehicle);
			return v;
		}
		return 0;
	}
	return 0;
}

void Grant_Refill(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		GrantSupplies(obj);
	}
}

void Soldier_Re_Init(GameObject *obj,DefinitionClass *def)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,obj
		mov eax,def
		mov ebx,SoldierReInit
		push eax
		call ebx
	}
#else
	SoldierReInit(obj,def);
#endif
}

bool Change_Character(GameObject *obj,const char *Preset_Name)
{
	if (!Commands->Get_ID(obj) || !obj || Get_Vehicle(obj))
	{
		return false;
	}
	DefinitionClass *def = Find_Named_Definition(Preset_Name);
	if (!def)
	{
		return false;
	}
	if (def->Get_Class_ID() != 0x3001)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return false;
	}
	Soldier_Re_Init(o,def);
	((ScriptableGameObj *)obj)->Post_Re_Init();
	return true;
}

bool IsAvailableForPurchase(GameObject *factory)
{
#ifdef WIN32
	_asm {
		mov ecx,factory
		mov ebx,Is_Available_For_Purchase
		call ebx
	}
#else
	return Is_Available_For_Purchase(factory);
#endif
}

void Create_Vehicle(const char *Preset_Name,float Delay,GameObject *Owner,int Team)
{
	GameObject *o = 0;
	if (Owner)
	{
		o = As_SoldierGameObj(Owner);
	}
	DefinitionClass *def = Find_Named_Definition(Preset_Name);
	if (def)
	{
		if (!Get_Vehicle(o))
		{
			GameObject *factory = Find_Vehicle_Factory(Team);
			if (factory)
			{
				if (IsAvailableForPurchase(factory))
				{
					unsigned int ID = def->Get_ID();
#ifdef WIN32
					_asm {
						mov ecx,factory
						mov ebx,Request_Vehicle
						mov eax,o
						push eax
						mov eax,Delay
						push eax
						mov eax,ID
						push eax
						call ebx
					}
#else
					Request_Vehicle(factory,ID,Delay,o);
#endif
				}
			}
		}
	}
}

void Toggle_Fly_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
#ifdef WIN32
		_asm {
			mov ecx,o
			mov ebx,ToggleFly
			call ebx
		}
#else
		ToggleFly(o);
#endif
		Commands->Enable_Collisions(o);
	}
}

int Get_Vehicle_Occupant_Count(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int count = 0;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			count++;
		}
	}
	return count;
}

GameObject *Get_Vehicle_Occupant(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (seat >= occupants.Length())
	{
		return 0;
	}
	return occupants[seat];
}

GameObject *Get_Vehicle_Driver(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (occupants.Length() <= 0)
	{
		return 0;
	}
	return occupants[0];
}

GameObject *Get_Vehicle_Gunner_Pos(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (occupants.Length() <= 1)
	{
		return 0;
	}
	return occupants[1];
}

GameObject *Get_Vehicle_Gunner(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	GameObject *o = Get_Vehicle_Gunner_Pos(obj);
	if ((!o) || (*(bool *)(obj+0x994)))
	{
		o = Get_Vehicle_Driver(obj);
	}
	return o;
}

void Force_Occupant_Exit(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (seat >= occupants.Length())
	{
		return;
	}
	if (occupants[seat])
	{
		Check_Transitions(occupants[seat],true);
	}
}

void Force_Occupants_Exit(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			Check_Transitions(occupants[i],true);
		}
	}
}

GameObject *Get_Vehicle_Return(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return obj;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		char *c = (char *)o;
		c += 0x98C;
		unsigned long *l = (unsigned long *)c;
		GameObject *vehicle = (GameObject *)*l;
		if (vehicle)
		{
			GameObject *v = As_VehicleGameObj(vehicle);
			return v;
		}
		return obj;
	}
	return obj;
}

bool Get_Fly_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return false;
	}
	char *c = (char *)obj;
	c += 0xD24;
	return *(bool *)c;
}

bool Is_Stealth(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SmartGameObj(obj);
	if (!o)
	{
		return false;
	}
	char *c = (char *)obj;
	c += 0x83D;
	return *(bool *)c;
}

int Get_Vehicle_Seat_Count(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	return occupants.Length();
}

char *Get_Spawn_Char(int Team)
{
	if (!Team)
	{
		return SpawnCharNod;
	}
	else if (Team == 1)
	{
		return SpawnCharGDI;
	}
	return "None";
}

void Change_Spawn_Char(int Team,const char *Name)
{
	if (strlen(Name) > 24)
	{
		return;
	}
	else if (!Team)
	{
		memcpy((void*)SpawnCharNod,(void*)Name,24);
	}
	else if (Team == 1)
	{
		memcpy((void*)SpawnCharGDI,(void*)Name,24);
	}
}

void Soldier_Transition_Vehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_SoldierGameObj(obj))
	{
		return;
	}
	Check_Transitions(obj,true);
}

unsigned int Get_Vehicle_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		if (!Get_Vehicle(obj))
		{
			return 0;
		}
		else 
		{
			obj = Get_Vehicle(obj);
		}
	}
	DefinitionClass *d = Get_Definition(obj);
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

int Get_Team_Vehicle_Count(int team)
{
	GameObject *o = Find_Vehicle_Factory(team);
	if (!o)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx, o
		mov ebx, GetVehicleCount
		call ebx
	}
#else
	return GetVehicleCount(o);
#endif
}

GameObject *Get_Vehicle_Owner(GameObject *obj)
{	
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x9E0;
	ReferenceableClass<ScriptableGameObj> *r = *(ReferenceableClass<ScriptableGameObj> **)c;
	if (r)
	{
		return (GameObject *)r->obj;
	}
	return 0;
}

void Force_Occupants_Exit_Team(GameObject *obj,int team)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if ((occupants[i]) && (Commands->Get_Player_Type(occupants[i]) != team))
		{
			Check_Transitions(occupants[i],true);
		}
	}
}

unsigned int Get_Vehicle_Definition_Mode(const char *preset)
{
	DefinitionClass *d = Find_Named_Definition(preset);
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

bool IsInsideZone(GameObject *zone,GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (!Commands->Get_ID(zone) || !zone)
	{
		return false;
	}
	GameObject *o = As_SmartGameObj(obj);
	GameObject *o2 = As_ScriptZoneGameObj(zone);
	if ((o) && (o2))
	{
		Vector3 v;
		((PhysicalGameObj *)o)->Get_Position(&v);
		return PointInZone(o2,v);
	}
	return false;
}

unsigned int Get_Vehicle_Definition_Mode_By_ID(unsigned long ID)
{
	DefinitionClass *d = Find_Definition(ID);
	if (!d) return 5;
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

unsigned int Get_Zone_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ScriptZoneGameObj(obj);
	if (!o)
	{
		return 0;
	}
	ScriptZoneGameObjDef *d = (ScriptZoneGameObjDef *)Get_Definition(obj);
	return d->ZoneType;
}

OBBoxClass *Get_Zone_Box(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	ScriptZoneGameObj *o = ((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
	if (!o)
	{
		return 0;
	}
	return &o->BoundingBox;
}

void Set_Zone_Box(GameObject *obj,const OBBoxClass &box)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	ScriptZoneGameObj *o = ((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
	if (!o)
	{
		return;
	}
	memcpy(&o->BoundingBox,&box,sizeof(OBBoxClass));
}

GameObject *Create_Zone(const char *preset,const OBBoxClass &box)
{
	GameObject *obj = Create_Library_Object(preset);
	Set_Zone_Box(obj,box);
	((ScriptableGameObj *)obj)->Start_Observers();
	return obj;
}

bool PointInZone(GameObject *obj,const Vector3 &v)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_ScriptZoneGameObj(obj);
	if (!o)
	{
		return false;
	}
	unsigned int x = Overlap_Test(*Get_Zone_Box(o),v);
	if (x == 2)
	{
		return true;
	}
	return false;
}

void Set_Vehicle_Is_Visible(GameObject *obj,bool visible)
{
	bool *b = (bool *)obj;
	b += 0x995;
	*b = visible;
}

void Set_Vehicle_Gunner(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (occupants.Length() <= 1)
	{
		return;
	}
	if ((seat > 1) && (seat < occupants.Length()))
	{
		GameObject *obj = occupants[1];
		occupants[1] = occupants[seat];
		occupants[seat] = obj;
	}
}
