/*	Renegade Scripts.dll
	GameObject classes and related engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu, WhiteDragon(MDB)

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
#include <float.h>

typedef GameObject *(*ago) (GameObject *obj);

SList<GameObject> *BuildingGameObjList;
SList<GameObject> *SmartGameObjList;
SList<GameObject> *BaseGameObjList;
void *Get_Obj_Color;
void *SetMaxHealth;
void *SetMaxShieldStrength;
void *MarkOwnerDirty;
void *StartObservers;
void *Powerup_Grant;

void THUNK PowerupGameObjDef::Grant(GameObject *obj,int powerup,bool showonhud)
IMPLEMENT_THUNK(Powerup_Grant)
void THUNK DefenseObjectClass::Set_Max_Health(float health)
IMPLEMENT_THUNK(SetMaxHealth)
void THUNK DefenseObjectClass::Set_Max_Shield_Strength(float shieldstrength)
IMPLEMENT_THUNK(SetMaxShieldStrength)
void THUNK DefenseObjectClass::Mark_Owner_Dirty()
IMPLEMENT_THUNK(MarkOwnerDirty)
void THUNK ScriptableGameObj::Start_Observers()
IMPLEMENT_THUNK(StartObservers)
Vector3 THUNK DamageableGameObj::Get_Team_Color()
IMPLEMENT_THUNK_RETURN_V(Get_Obj_Color)

void InitEngineObj(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			BuildingGameObjList = (SList<GameObject> *)0x00856FE8;
			SmartGameObjList = (SList<GameObject> *)0x00856FD8;
			BaseGameObjList = (SList<GameObject> *)0x00856FF8;
			Get_Obj_Color = (void *)0x006D97B0;
			SetMaxHealth = (void *)0x00691820;
			SetMaxShieldStrength = (void *)0x006930E0;
			MarkOwnerDirty = (void *)0x00693740;
			StartObservers = (void *)0x006B6C40;
			Powerup_Grant = (void *)0x006F09F0;
			break;
		case 1: //server.dat
			BuildingGameObjList = (SList<GameObject> *)0x008561D0;
			SmartGameObjList = (SList<GameObject> *)0x008561C0;
			BaseGameObjList = (SList<GameObject> *)0x008561E0;
			Get_Obj_Color = (void *)0x006D9050;
			SetMaxHealth = (void *)0x006910C0;
			SetMaxShieldStrength = (void *)0x00692980;
			MarkOwnerDirty = (void *)0x00692FE0;
			StartObservers = (void *)0x006B64E0;
			Powerup_Grant = (void *)0x006EFFB0;
			break;
		case 2: //RH73
			BuildingGameObjList = (SList<GameObject> *)0x08BA05FC;
			SmartGameObjList = (SList<GameObject> *)0x08BA05E4;
			BaseGameObjList = (SList<GameObject> *)0x08BA05D8;
			Get_Obj_Color = (void *)0x0810E304;
			SetMaxHealth = (void *)0x08111B88;
			SetMaxShieldStrength = (void *)0x08111C9C;
			MarkOwnerDirty = (void *)0x08111D84;
			StartObservers = (void *)0x08152F78;
			Powerup_Grant = (void *)0x08144268;
			break;
		case 3: //RH8
			BuildingGameObjList = (SList<GameObject> *)0x089A9090;
			SmartGameObjList = (SList<GameObject> *)0x089A9078;
			BaseGameObjList = (SList<GameObject> *)0x089A906C;
			Get_Obj_Color = (void *)0x081006FC;
			SetMaxHealth = (void *)0x08103C18;
			SetMaxShieldStrength = (void *)0x08103D2E;
			MarkOwnerDirty = (void *)0x08103E20;
			StartObservers = (void *)0x081410B2;
			Powerup_Grant = (void *)0x081332C6;
			break;
		default:
			BuildingGameObjList = (SList<GameObject> *)0;
			SmartGameObjList = (SList<GameObject> *)0;
			BaseGameObjList = (SList<GameObject> *)0;
			Get_Obj_Color = (void *)0;
			SetMaxHealth = (void *)0;
			SetMaxShieldStrength = (void *)0;
			MarkOwnerDirty = (void *)0;
			StartObservers = (void *)0;
			Powerup_Grant = (void *)0;
			break;
	}
}

int Get_Object_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return 0;
	}
	return o->PlayerType;
}

void Set_Object_Type(GameObject *obj,int type)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->PlayerType = type;
}

GameObject *As_PowerupGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_PowerupGameObj();
}

GameObject *As_C4GameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_C4GameObj();
}

GameObject *As_BeaconGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_BeaconGameObj();
}

GameObject *As_ArmedGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_ArmedGameObj();
}

GameObject *As_SimpleGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_SimpleGameObj();
}

GameObject *As_PowerPlantGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x70]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x94;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x78;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_SoldierFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x74]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x98;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x7C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_VehicleFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x78]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x9C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x80;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_AirstripGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x7C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x84;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_WarFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x80]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA4;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x88;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_RefineryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x84]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA8;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x8C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_ComCenterGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x88]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xAC;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x90;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_RepairBayGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x8C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xB0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x94;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_ScriptableGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_ScriptableGameObj();
}

GameObject *As_PhysicalGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_PhysicalGameObj();
}

GameObject *As_CinematicGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	return (GameObject *)o2->As_CinematicGameObj();
}

GameObject *As_VehicleGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_VehicleGameObj();
}

GameObject *As_SmartGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_SmartGameObj();
}

GameObject *As_DamageableGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_DamageableGameObj();
}

GameObject *As_SoldierGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_SoldierGameObj();
}

GameObject *As_ScriptZoneGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
}

GameObject *As_BuildingGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_BuildingGameObj();
}

bool Is_Building(GameObject *obj)
{
	if (As_BuildingGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Soldier(GameObject *obj)
{
	if (As_SoldierGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Vehicle(GameObject *obj)
{
	if (As_VehicleGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Cinematic(GameObject *obj)
{
	if (As_CinematicGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_ScriptZone(GameObject *obj)
{
	if (As_ScriptZoneGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Powerup(GameObject *obj)
{
	if (As_PowerupGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_C4(GameObject *obj)
{
	if (As_C4GameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Scriptable(GameObject *obj)
{
	if (As_ScriptableGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Beacon(GameObject *obj)
{
	if (As_BeaconGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Armed(GameObject *obj)
{
	if (As_ArmedGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Simple(GameObject *obj)
{
	if (As_SimpleGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_PowerPlant(GameObject *obj)
{
	if (As_PowerPlantGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_SoldierFactory(GameObject *obj)
{
	if (As_SoldierFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_VehicleFactory(GameObject *obj)
{
	if (As_VehicleFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Airstrip(GameObject *obj)
{
	if (As_AirstripGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_WarFactory(GameObject *obj)
{
	if (As_WarFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Refinery(GameObject *obj)
{
	if (As_RefineryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_ComCenter(GameObject *obj)
{
	if (As_ComCenterGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_RepairBay(GameObject *obj)
{
	if (As_RepairBayGameObj(obj))
	{
		return true;
	}
	return false;
}

const char *Get_Building_Type(GameObject *obj)
{
	if (Is_PowerPlant(obj))
	{
		return "Is_PowerPlant";
	}
	else if (Is_SoldierFactory(obj))
	{
		return "Is_SoldierFactory";
	}
	else if (Is_VehicleFactory(obj))
	{
		if (Is_Airstrip(obj))
		{
			return "Is_Airstrip";
		}
		else if (Is_WarFactory(obj))
		{
			return "Is_WarFactory";
		}
	}
	else if (Is_Refinery(obj))
	{
		return "Is_Refinery";
	}
	else if (Is_ComCenter(obj))
	{
		return "Is_ComCenter";
	}
	else if (Is_RepairBay(obj))
	{
		return "Is_RepairBay";
	}
	else
	{
		return "(null)";
	}
	return "(null)";
}

void Get_Object_Color(GameObject *obj, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = (DamageableGameObj *)As_DamageableGameObj(obj);
	if (!o)
	{
		return;
	}
	Vector3 v = o->Get_Team_Color();
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

GameObject *Find_Smart_Object_By_Team(int Team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Object_By_Team(int Team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if (Get_Object_Type(o) == Team)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Non_Player_Object_By_Team(int Team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) && (!Commands->Is_A_Star(o)))
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Object_By_Preset(int Team,const char *Preset_Name)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),Preset_Name))
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Closest_Non_Building_Object_By_Team(int Team,Vector3 position)
{
	float closestdist = FLT_MAX;
	GameObject *closest = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if ((Get_Object_Type(o) == Team) && !Is_A_Building(o))
			{
				Vector3 pos = Commands->Get_Position(o);
				float dist = Commands->Get_Distance(pos,position);
				if (dist < closestdist)
				{
					closestdist = dist;
					closest = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return closest;
}

GameObject *Find_Closest_Preset_By_Team(int Team,const Vector3 &pos,const char *Preset)
{
	float closestdist = 9999.0f;
	GameObject *closest = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				float dist = Commands->Get_Distance(Commands->Get_Position(o),pos);
				if (dist < closestdist)
				{
					closestdist = dist;
					closest = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return closest;
}

GameObject *Find_Random_Preset_By_Team(int Team,const char *Preset)
{
	SimpleDynVecClass<GameObject*> ObjList(0);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				ObjList.Add(o);
			}
		}
		x = x->NodeNext;
	}
	int len = ObjList.Count();
	if (len > 1)
	{
		return ObjList[Commands->Get_Random_Int(0,len)];
	}
	else if (!len)
	{
		return 0;
	}
	return ObjList[0];
}

int Get_Object_Count(int Team,const char *Preset)
{
	int count = 0;
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				count++;
			}
		}
		x = x->NodeNext;
	}
	return count;
}

SimpleDynVecClass<GameObject*> Get_All_Objects_By_Preset(int Team,const char *Preset)
{
	SimpleDynVecClass<GameObject*> ObjList(0);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				ObjList.Add(o);
			}
		}
		x = x->NodeNext;
	}
	return ObjList;
}

GameObject *Find_Nearest_Preset(Vector3 position, const char *preset)
{
	GameObject *object = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if (!_stricmp(Commands->Get_Preset_Name(o),preset))
			{
				if (object)
				{
					Vector3 obj_pos = Commands->Get_Position(object);
					Vector3 o_pos = Commands->Get_Position(o);
					if (Commands->Get_Distance(position, o_pos) < Commands->Get_Distance(position, obj_pos))
					{
						object = o;
					}
				}
				else
				{
					object = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return object;
}

GameObject *Find_Random_Preset(const char* preset, int min, int max)
{
	int count = Commands->Get_Random_Int(min, max);
	GameObject *object = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (count > 0)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if (!_stricmp(Commands->Get_Preset_Name(o),preset))
			{
				object = o;
				count--;
			}
		}
		x = x->NodeNext;
		if (!x)
		{
			if (object)
			{
				x = BaseGameObjList->HeadNode;
			}
			else
			{
				return object;
			}
		}
	}
	return object;
}

void Send_Custom_To_Team_Buildings(int Team,GameObject *sender,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				int ReceiverID = Commands->Get_ID(o);
				int SenderID = Commands->Get_ID(sender);
				if (SenderID != ReceiverID)
				{
					Commands->Send_Custom_Event(sender,o,message,param,delay);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_To_Team_Preset(int Team,const char *PresetName,GameObject *sender,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if (Get_Object_Type(o) == Team)
			{
				if (!_stricmp(Commands->Get_Preset_Name(o),PresetName))
				{
					Commands->Send_Custom_Event(sender,o,message,param,delay);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_All_Objects_Area(int message,const Vector3 &Position,float Distance,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj))
		{
			Vector3 ObjPosition = Commands->Get_Position(obj);
			Vector3 TestPosition = Position;
			ObjPosition.Z = 0;
			TestPosition.Z = 0;
			if ((Commands->Get_Distance(ObjPosition,TestPosition) <= Distance))
			{
				if ((Get_Object_Type(obj) == team) || (team == 2))
				{
					Commands->Send_Custom_Event(sender,obj,message,0,0);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_All_Objects(int message,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj))
		{
			if ((Get_Object_Type(obj) == team) || (team == 2))
			{
				Commands->Send_Custom_Event(sender,obj,message,0,0);
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_Event_To_Object(GameObject *sender,const char *Preset,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),Preset))
			{
				Commands->Send_Custom_Event(sender,o,message,param,delay);
			}
		}
		x = x->NodeNext;
	}
}

bool Is_Unit_In_Range(const char *preset,float range,Vector3 location,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Get_Object_Type(o) == team) && (!_stricmp(Commands->Get_Preset_Name(o),preset)))
			{
				Vector3 pos = Commands->Get_Position(o);
				pos.Z = 0;
				location.Z = 0;
				if (Commands->Get_Distance(pos,location) <= range)
				{
					return true;
				}
			}
		}
		x = x->NodeNext;
	}
	return false;
}

bool Get_Is_Powerup_Persistant(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return 0;
	}
	return ((PowerupGameObjDef *)o3->definition)->Persistant;
}

void Set_Is_Powerup_Persistant(GameObject *obj,bool Persist)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return;
	}
	((PowerupGameObjDef *)o3->definition)->Persistant = Persist;
}

bool Get_Powerup_Always_Allow_Grant(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return 0;
	}
	return ((PowerupGameObjDef *)o3->definition)->AlwaysAllowGrant;
}

void Set_Powerup_Always_Allow_Grant(GameObject *obj,bool Grant)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return;
	}
	((PowerupGameObjDef *)o3->definition)->AlwaysAllowGrant = Grant;
}

int Get_Powerup_Grant_Sound(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return 0;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return 0;
	}
	return ((PowerupGameObjDef *)o3->definition)->GrantSoundID;
}

void Set_Powerup_Grant_Sound(GameObject *obj,int SoundID)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o2)
	{
		return;
	}
	PowerupGameObj *o3 = o2->As_PowerupGameObj();
	if (!o3)
	{
		return;
	}
	((PowerupGameObjDef *)o3->definition)->GrantSoundID = SoundID;
}

void Grant_Powerup(GameObject *obj,const char *Preset_Name)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SmartGameObj(obj);
	if (o)
	{
		PowerupGameObjDef *def = (PowerupGameObjDef *)Find_Named_Definition(Preset_Name);
		def->Grant(o,0,true);
	}
}
