/*	Renegade Scripts.dll
	Global ingame classes and engine calls
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
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_io.h"
#include "engine_net.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_game.h"

#ifdef WIN32
typedef void (*cbc) (void);
#else
typedef void (*cbc) (GameObject *obj);
#endif
typedef void *(*GameModeFind) (const char *mode);

void *FindBase;
void *GetHarvester;
void *PowerBase;
void *SetCanGenerateSoldiers;
void *SetCanGenerateVehicles;
void *DestroyBase;
void *SetBeaconDestroyedBase;
void *EnableRadar;
void *FindBuilding;
void *Skirmish_Game;
void *Cnc_Game;
void *Single_Player_Game;
bool *IsMapVTOL;
cbc Collect_Building_Components;
GameModeFind Game_Mode_Find;
bool *IsListed;
int *GameType;
float *GDIHouseColor;
float *NodHouseColor;
float *PrivateMessageColor;
float *PublicMessageColor;
unsigned int *GameMode;
void *Game;

cGameData THUNK *The_Game()
IMPLEMENT_THUNK_RETURN(Game)
BaseControllerClass THUNK *BaseControllerClass::Find_Base(int Team)
IMPLEMENT_THUNK_RETURN(FindBase)
GameObject THUNK *BaseControllerClass::Get_Harvester_Vehicle()
IMPLEMENT_THUNK_RETURN(GetHarvester)
void THUNK BaseControllerClass::Power_Base(bool Power)
IMPLEMENT_THUNK(PowerBase)
void THUNK BaseControllerClass::Set_Can_Generate_Soldiers(bool CanGenerate)
IMPLEMENT_THUNK(SetCanGenerateSoldiers)
void THUNK BaseControllerClass::Set_Can_Generate_Vehicles(bool CanGenerate)
IMPLEMENT_THUNK(SetCanGenerateVehicles)
void THUNK BaseControllerClass::Destroy_Base()
IMPLEMENT_THUNK(DestroyBase)
void THUNK BaseControllerClass::Enable_Radar(bool Enable)
IMPLEMENT_THUNK(EnableRadar)
void THUNK BaseControllerClass::Set_Beacon_Destroyed_Base(bool BeaconDestroyed)
IMPLEMENT_THUNK(SetBeaconDestroyedBase)
GameObject THUNK *BaseControllerClass::Find_Building(unsigned int Type)
IMPLEMENT_THUNK_RETURN(FindBuilding)
cGameDataSkirmish THUNK *The_Skirmish_Game()
IMPLEMENT_THUNK_RETURN(Skirmish_Game)
cGameDataCnc THUNK *The_Cnc_Game()
IMPLEMENT_THUNK_RETURN(Cnc_Game)
cGameDataSinglePlayer THUNK *The_Single_Player_Game()
IMPLEMENT_THUNK_RETURN(Single_Player_Game)

void InitEngineGame(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Game = (void *)0x00477CA0;
			FindBase = (void *)0x006EF790;
			GetHarvester = (void *)0x006EFD60;
			PowerBase = (void *)0x006EF310;
			SetCanGenerateSoldiers = (void *)0x006EF420;
			SetCanGenerateVehicles = (void *)0x006EF440;
			DestroyBase = (void *)0x006EF840;
			SetBeaconDestroyedBase = (void *)0x006EF8D0;
			EnableRadar = (void *)0x006EFD00;
			FindBuilding = (void *)0x006EF6D0;
			Skirmish_Game = (void *)0x00477CC0;
			Cnc_Game = (void *)0x00477CD0;
			Single_Player_Game = (void *)0x00477CB0;
			IsMapVTOL = (bool *)0x0085E31C;
			Collect_Building_Components = (cbc)0x006843E0;
			GameMode = (unsigned int *)0x0081F5F0;
			PrivateMessageColor = (float *)0x0082FC20;
			PublicMessageColor = (float *)0x0082FBA0;
			GDIHouseColor = (float *)0x0085CAA8;
			NodHouseColor = (float *)0x0085CA98;
			GameType = (int *)0x00856518;
			IsListed = (bool *)0x0082FD94;
			Game_Mode_Find = (GameModeFind)0x004372B0;
			break;
		case 1: //server.dat
			Game = (void *)0x00477370;
			FindBase = (void *)0x006EED50;
			GetHarvester = (void *)0x006EF320;
			PowerBase = (void *)0x006EE8D0;
			SetCanGenerateSoldiers = (void *)0x006EE9E0;
			SetCanGenerateVehicles = (void *)0x006EEA00;
			DestroyBase = (void *)0x006EEE00;
			SetBeaconDestroyedBase = (void *)0x006EEE90;
			EnableRadar = (void *)0x006EF2C0;
			FindBuilding = (void *)0x006EEC90;
			Skirmish_Game = (void *)0x00477390;
			Cnc_Game = (void *)0x004773A0;
			Single_Player_Game = (void *)0x00477380;
			IsMapVTOL = (bool *)0x0085D4F4;
			Collect_Building_Components = (cbc)0x00683C80;
			GameMode = (unsigned int *)0x0081E7D8;
			PrivateMessageColor = (float *)0x0082EE08;
			PublicMessageColor = (float *)0x0082ED88;
			GDIHouseColor = (float *)0x0085BC90;
			NodHouseColor = (float *)0x0085BC80;
			GameType = (int *)0x00855700;
			IsListed = (bool *)0x0082EF7C;
			Game_Mode_Find = (GameModeFind)0x00437350;
			break;
		case 2: //RH73
			Game = (void *)0x0807CCD0;
			FindBase = (void *)0x080ED660;
			GetHarvester = (void *)0x080EDB54;
			PowerBase = (void *)0x080ED15C;
			SetCanGenerateSoldiers = (void *)0x080ED28C;
			SetCanGenerateVehicles = (void *)0x080ED2B0;
			DestroyBase = (void *)0x080ED720;
			SetBeaconDestroyedBase = (void *)0x080ED7B8;
			EnableRadar = (void *)0x080EDABC;
			FindBuilding = (void *)0x080ED548;
			Skirmish_Game = (void *)0x0807CCF0;
			Cnc_Game = (void *)0x0807CD08;
			Single_Player_Game = (void *)0x0807CCD8;
			IsMapVTOL = (bool *)0x086C9D94;
			Collect_Building_Components = (cbc)0x080F55C4;
			GameMode = (unsigned int *)0x086C4A30;
			PrivateMessageColor = (float *)0x08B9B18C;
			PublicMessageColor = (float *)0x08B9B180;
			GDIHouseColor = (float *)0x08B9FA40;
			NodHouseColor = (float *)0x08B9FA34;
			GameType = (int *)0x086C8F78;
			IsListed = (bool *)0x086C2BA8;
			Game_Mode_Find = (GameModeFind)0x0807FC90;
			break;
		case 3: //RH8
			Game = (void *)0x0807C7A8;
			FindBase = (void *)0x080E2D3A;
			GetHarvester = (void *)0x080E322C;
			PowerBase = (void *)0x080E28C8;
			SetCanGenerateSoldiers = (void *)0x080E29EE;
			SetCanGenerateVehicles = (void *)0x080E2A0E;
			DestroyBase = (void *)0x080E2DEA;
			SetBeaconDestroyedBase = (void *)0x080E2E78;
			EnableRadar = (void *)0x080E319A;
			FindBuilding = (void *)0x080E2C52;
			Skirmish_Game = (void *)0x0807C7C2;
			Cnc_Game = (void *)0x0807C7D6;
			Single_Player_Game = (void *)0x0807C7AE;
			IsMapVTOL = (bool *)0x085F1554;
			Collect_Building_Components = (cbc)0x080EA1F2;
			GameMode = (unsigned int *)0x085EBB70;
			PrivateMessageColor = (float *)0x089A36F4;
			PublicMessageColor = (float *)0x089A36E8;
			GDIHouseColor = (float *)0x089A8398;
			NodHouseColor = (float *)0x089A838C;
			GameType = (int *)0x085F0670;
			IsListed = (bool *)0x085E9AB8;
			Game_Mode_Find = (GameModeFind)0x0807F36A;
			break;
		default:
			Game = (void *)0;
			FindBase = (void *)0;
			GetHarvester = (void *)0;
			PowerBase = (void *)0;
			SetCanGenerateSoldiers = (void *)0;
			SetCanGenerateVehicles = (void *)0;
			DestroyBase = (void *)0;
			SetBeaconDestroyedBase = (void *)0;
			EnableRadar = (void *)0;
			FindBuilding = (void *)0;
			Skirmish_Game = (void *)0;
			Cnc_Game = (void *)0;
			Single_Player_Game = (void *)0;
			IsMapVTOL = (bool *)0;
			Collect_Building_Components = (cbc)0;
			GameMode = (unsigned int *)0;
			PrivateMessageColor = (float *)0;
			PublicMessageColor = (float *)0;
			GDIHouseColor = (float *)0;
			NodHouseColor = (float *)0;
			GameType = (int *)0;
			IsListed = (bool *)0;
			Game_Mode_Find = (GameModeFind)0;
			break;
	}
}

void Power_Base(int team,bool powered)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Power_Base(powered);
	}
}

void Set_Can_Generate_Soldiers(int team,bool cangenerate)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Can_Generate_Soldiers(cangenerate);
	}
}

void Set_Can_Generate_Vehicles(int team,bool cangenerate)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Can_Generate_Vehicles(cangenerate);
	}
}

void Destroy_Base(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Destroy_Base();
	}
}

void Beacon_Destroyed_Base(int team, bool destroyed)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Beacon_Destroyed_Base(destroyed);
	}
}

void Enable_Base_Radar(int team, bool enable)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Enable_Radar(enable);
	}
}

bool Is_Harvester(GameObject *obj)
{
	if (!As_VehicleGameObj(obj))
	{
		return false;
	}
	int ID = Commands->Get_ID(obj);
	if (Commands->Get_ID(Find_Harvester(0)) == ID || Commands->Get_ID(Find_Harvester(1)) == ID)
	{
		return true;
	}
	return false;
}

bool Is_Radar_Enabled(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->RadarEnabled;
	}
	return false;
}

int Building_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_BuildingGameObj(obj);
	if (!o)
	{
		return 0;
	}
	DefinitionClass *d = Get_Definition(obj);
	char *c = (char *)d;
	c += 0x8C;
	return *(int *)c;
}

bool Is_Building_Dead(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_BuildingGameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x778;
	return *(bool *)c;
}

GameObject *Find_Building(int team,int type)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->Find_Building(type);
	}
	return 0;
}

GameObject *Find_Base_Defense(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->Find_Building(BASE_DEFENSE);
	}
	return 0;
}

bool Is_Map_Flying()
{
	return *IsMapVTOL;
}

GameObject *Create_Building(const char *preset,const Vector3 & Position)
{
	DefinitionClass *d = Find_Named_Definition(preset);
	GameObject *obj = (GameObject *)d->Create();
	if (As_BuildingGameObj(obj))
	{
		char *c = (char *)obj;
		c += 0x77C;
		Vector3 *pos1 = (Vector3 *)c;
		c = (char *)obj;
		c += 0x7A4;
		Vector3 *pos2 = (Vector3 *)c;
		pos1->X = Position.X;
		pos1->Y = Position.Y;
		pos1->Z = Position.Z;
		pos2->X = Position.X;
		pos2->Y = Position.Y;
		pos2->Z = Position.Z;
#ifdef WIN32
		_asm {
			mov ecx,obj
			mov ebx,Collect_Building_Components
			call ebx
			mov ecx,obj
		}
#else
		Collect_Building_Components(obj);
#endif
		((ScriptableGameObj *)obj)->Start_Observers();
		return obj;
	}
	return 0;
}

GameObject *Find_Harvester(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	GameObject *o = 0;
	if (c)
	{
		o = c->Get_Harvester_Vehicle();
	}
	return o;
}

bool Is_Base_Powered(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->IsPowered;
	}
	return false;
}

bool Can_Generate_Vehicles(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->CanGenerateVehicles;
	}
	return false;
}

bool Can_Generate_Soliders(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->CanGenerateSoldiers;
	}
	return false;
}

bool Is_A_Building(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (((ScriptableGameObj *)obj)->As_BuildingGameObj())
	{
		return true;
	}
	return false;
}

int Get_Building_Count_Team(int Team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	int Count = 0;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o && Commands->Get_Health(o) > 0 && (Get_Object_Type(o) == Team || Team == 2))
		{
			Count++;
		}
		x = x->NodeNext;
	}
	return Count;
}

GameObject *Find_Building_By_Class_ID(int Team,unsigned long Class_ID)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == Class_ID)
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

GameObject *Find_Power_Plant(int Team)
{
	return Find_Building(Team,POWER_PLANT);
}

GameObject *Find_Refinery(int Team)
{
	return Find_Building(Team,REFINERY);
}

GameObject *Find_Repair_Bay(int Team)
{
	return Find_Building(Team,REPAIR_BAY);
}

GameObject *Find_Soldier_Factory(int Team)
{
	return Find_Building(Team,SOLDIER_FACTORY);
}

GameObject *Find_Airstrip(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD006);
}

GameObject *Find_War_Factory(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD007);
}

GameObject *Find_Vehicle_Factory(int Team)
{
	return Find_Building(Team,VEHICLE_FACTORY);
}

GameObject *Find_Com_Center(int Team)
{
	return Find_Building(Team,COM_CENTER);
}

GameObject *Find_Building_By_Team(int Team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
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

GameObject *Find_Building_By_Name(int Team,const char *Preset_Name)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
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

bool Is_Gameplay_Permitted()
{
	return The_Game()->Is_Gameplay_Permitted();
}

bool Is_Dedicated()
{
	return Exe;
}

bool Is_Linux()
{
	if ((Exe == 2) || (Exe == 3))
	{
		return true;
	}
	return false;
}

unsigned int Get_Current_Game_Mode()
{
	if (*GameType == 1)
	{
		return 1;
	}
	if (*GameType == 2)
	{
		return 2;
	}
	if (*GameType == 3)
	{
		if (*GameMode == 1)
		{
			return 5;
		}
		if (*GameMode == 2)
		{
			return 3;
		}
		if (*GameMode == 3)
		{
			return 4;
		}
		if (Game_Mode_Find("WOL"))
		{
			return 3;
		}
		if (Game_Mode_Find("LAN"))
		{
			if (*IsListed)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
	}
	return 0;
}

void Get_Private_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue)
{
	*red = (unsigned int)(PrivateMessageColor[0]*255);
	*green = (unsigned int)(PrivateMessageColor[1]*255);
	*blue = (unsigned int)(PrivateMessageColor[2]*255);
}

void Get_Public_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue)
{
	*red = (unsigned int)(PublicMessageColor[0]*255);
	*green = (unsigned int)(PublicMessageColor[1]*255);
	*blue = (unsigned int)(PublicMessageColor[2]*255);
}

int Get_Harvester_Preset_ID(int Team)
{
	BaseGameObj *Ref = (BaseGameObj*)Find_Refinery(Team);
	if (!Ref)
	{
		return 0;
	}
	char *Def = (char*)Ref->definition;
	Def += 0xAC;
	return *(int*)Def;
}

bool Is_Harvester_Preset(GameObject *obj)
{
	int ID = Commands->Get_Preset_ID(obj);
	if (Get_Harvester_Preset_ID(0) == ID || Get_Harvester_Preset_ID(1) == ID)
	{
		return true;
	}
	return false;
}
