/*	Renegade Scripts.dll
	Weapon related classes and engine calls
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
#include "engine_vector.h"
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_io.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_net.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_weap.h"

char *Mine_Limit;
void *C4Defuse;
void *GetBeaconOwner;

GameObject THUNK *BeaconGameObj::Get_Beacon_Owner()
IMPLEMENT_THUNK_RETURN(GetBeaconOwner)
void THUNK C4GameObj::Defuse()
IMPLEMENT_THUNK(C4Defuse)

void InitEngineWeap(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Mine_Limit = (char *)0x0070DD95;
			C4Defuse = (void *)0x0070D610;
			GetBeaconOwner = (void *)0x0070AA50;
			break;
		case 1: //server.dat
			Mine_Limit = (char *)0x0070D355;
			C4Defuse = (void *)0x0070CBD0;
			GetBeaconOwner = (void *)0x0070A010;
			break;
		case 2: //RH73
			Mine_Limit = (char *)0x080FABCE;
			C4Defuse = (void *)0x080FA990;
			GetBeaconOwner = (void *)0x080F05D8;
			break;
		case 3: //RH8
			Mine_Limit = (char *)0x080EE422;
			C4Defuse = (void *)0x080EE1EA;
			GetBeaconOwner = (void *)0x080E5D98;
			break;
		default:
			Mine_Limit = (char *)0;
			C4Defuse = (void *)0;
			GetBeaconOwner = (void *)0;
			break;
	}
}

int Get_Current_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->LoadedBullets.Get();
	}
	return 0;
}

int Get_Current_Clip_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->InventoryBullets.Get();
	}
	return 0;
}

int Get_Current_Total_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		int bullets = wc->LoadedBullets.Get();
		int clipbullets = wc->InventoryBullets.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Position_Bullets(GameObject *obj,int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->LoadedBullets.Get();
	}
	return 0;
}

int Get_Position_Clip_Bullets(GameObject *obj,int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->InventoryBullets.Get();
	}
	return 0;
}

int Get_Position_Total_Bullets(GameObject *obj, int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		int bullets = wc->LoadedBullets.Get();
		int clipbullets = wc->InventoryBullets.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->LoadedBullets.Get();
			}
		}
	}
	return 0;
}

int Get_Clip_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->InventoryBullets.Get();
			}
		}
	}
	return 0;
}

int Get_Total_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				int bullets = wc->LoadedBullets.Get();
				int clipbullets = wc->InventoryBullets.Get();
				if (clipbullets < 0)
				{
					return -1;
				}
				return bullets+clipbullets;
			}
		}
	}
	return 0;
}

int Get_Current_Max_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->ClipSize.Get();
	}
	return 0;
}

int Get_Current_Clip_Max_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->MaxInventoryRounds.Get();
	}
	return 0;
}

int Get_Current_Total_Max_Bullets(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		int bullets = wc->WeaponDef->ClipSize.Get();
		int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Position_Max_Bullets(GameObject *obj, int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->ClipSize.Get();
	}
	return 0;
}

int Get_Position_Clip_Max_Bullets(GameObject *obj, int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->MaxInventoryRounds.Get();
	}
	return 0;
}

int Get_Position_Total_Max_Bullets(GameObject *obj,int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		int bullets = wc->WeaponDef->ClipSize.Get();
		int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Max_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->ClipSize.Get();
			}
		}
	}
	return 0;
}

int Get_Max_Clip_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->MaxInventoryRounds.Get();
			}
		}
	}
	return 0;
}

int Get_Max_Total_Bullets(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				int bullets = wc->WeaponDef->ClipSize.Get();
				int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
				if (clipbullets < 0)
				{
					return -1;
				}
				return bullets+clipbullets;
			}
		}
	}
	return 0;
}

void Set_Current_Bullets(GameObject *obj,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		w->Vector[w->current]->InventoryBullets.Set(bullets);
	}
}

void Set_Current_Clip_Bullets(GameObject *obj,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		w->Vector[w->current]->LoadedBullets.Set(bullets);
	}
}

void Set_Position_Bullets(GameObject *obj,int position,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		w->Vector[position]->InventoryBullets.Set(bullets);
	}
}

void Set_Position_Clip_Bullets(GameObject *obj,int position,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		w->Vector[position]->LoadedBullets.Set(bullets);
	}
}

void Set_Bullets(GameObject *obj,const char *weapon,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				w->Vector[i]->InventoryBullets.Set(bullets);
			}
		}
	}
}

void Set_Clip_Bullets(GameObject *obj,const char *weapon,int bullets)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				w->Vector[i]->LoadedBullets.Set(bullets);
			}
		}
	}
}

const char *Get_Powerup_Weapon(const char *Powerup)
{
	DefinitionClass *powerupdef = Find_Named_Definition(Powerup);
	char *c = (char *)powerupdef;
	if (!c)
	{
		return "None";
	}
#ifdef RH8
	c += 0xC0;
#else
	c += 0xC4;
#endif
	unsigned long weapondefid = (unsigned long)*(unsigned long *)c;
	if (weapondefid)
	{
		DefinitionClass *weapondef = Find_Definition(weapondefid);
		return weapondef->Get_Name();
	}
	return "None";
}

AmmoDefinitionClass *Get_Weapon_Ammo_Definition(const char *weapon,bool PrimaryFire)
{
	WeaponDefinitionClass *d = (WeaponDefinitionClass *)Find_Named_Definition(weapon);
	if (d)
	{
		if (PrimaryFire)
		{
			unsigned long AmmoID = d->PrimaryAmmoDefID;
			AmmoDefinitionClass *AmmoDef = (AmmoDefinitionClass*)Find_Definition(AmmoID);
			return AmmoDef;
		}
		else
		{
			unsigned long AmmoID = d->SecondaryAmmoDefID;
			AmmoDefinitionClass *AmmoDef = (AmmoDefinitionClass*)Find_Definition(AmmoID);
			return AmmoDef;
		}
	}
	return 0;
}

AmmoDefinitionClass *GetWeapAmmoDef(WeaponClass *wc,bool PrimaryFire)
{
	if (PrimaryFire)
	{
		return wc->AmmoDef1;
	}
	else
	{
		return wc->AmmoDef2;
	}
}

AmmoDefinitionClass *Get_Current_Weapon_Ammo_Definition(GameObject *obj,bool PrimaryFire)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return GetWeapAmmoDef(w->Vector[w->current],PrimaryFire);
	}
	return 0;
}

AmmoDefinitionClass *Get_Position_Weapon_Ammo_Definition(GameObject *obj,int position,bool PrimaryFire)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position < w->Vector.Count()) && (w->Vector[w->current]))
	{
		return GetWeapAmmoDef(w->Vector[w->current],PrimaryFire);
	}
	return 0;
}

WeaponDefinitionClass *Get_Current_Weapon_Definition(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return *(WeaponDefinitionClass **)w->Vector[w->current];
	}
	return 0;
}

WeaponDefinitionClass *Get_Weapon_Definition(const char *weapon)
{
	return (WeaponDefinitionClass *)Find_Named_Definition(weapon);
}

WeaponDefinitionClass *Get_Position_Weapon_Definition(GameObject *obj,int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position < w->Vector.Count()) && (w->Vector[w->current]))
	{
		return *(WeaponDefinitionClass **)w->Vector[w->current];
	}
	return 0;
}

ExplosionDefinitionClass *Get_Explosion(const char *explosion)
{
	return (ExplosionDefinitionClass *)Find_Named_Definition(explosion);
}

const char *Get_Powerup_Weapon_By_Obj(GameObject *Powerup)
{
	DefinitionClass *powerupdef = Get_Definition(Powerup);
	char *c = (char *)powerupdef;
	if (!c)
	{
		return "None";
	}
#ifdef RH8
	c += 0xC0;
#else
	c += 0xC4;
#endif
	unsigned long weapondefid = (unsigned long)*(unsigned long *)c;
	if (weapondefid)
	{
		DefinitionClass *weapondef = Find_Definition(weapondefid);
		return weapondef->Get_Name();
	}
	return "None";
}

int Get_Current_Weapon_Style(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->Style;
	}
	return 0;
}

int Get_Position_Weapon_Style(GameObject *obj, int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->Style;
	}
	return 0;
}

int Get_Weapon_Style(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->Style;
			}
		}
	}
	return 0;
}

void Disarm_Beacon(GameObject *obj)
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
	BeaconGameObj *o3 = o2->As_BeaconGameObj();
	if (!o3)
	{
		return;
	}
	o3->Completly_Damaged(*(OffenseObjectClass *)0);
}

void Disarm_Beacons(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BeaconGameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o)
		{
			if (Get_Player_ID(Get_Beacon_Planter(o)) == PlayerID)
			{
				Disarm_Beacon(o);
			}
		}
		x = x->NodeNext;
	}
}

void Disarm_Nearest_Beacon(GameObject *Host,int Team,bool Nearest)
{
	if (!Commands->Get_ID(Host) || !Host)
	{
		return;
	}
	Vector3 HostPos = Commands->Get_Position(Host);
	HostPos.Z = 0;
	float NearestDistanceFound = 5000.0f;
	GameObject *ClosestBeacon = Commands->Create_Object("Invisible_Object",HostPos);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				if (Nearest)
				{
					Vector3 BeaconPos = Commands->Get_Position(o);
					BeaconPos.Z = 0;
					if (Commands->Get_Distance(BeaconPos,HostPos) < NearestDistanceFound)
					{
						NearestDistanceFound = Commands->Get_Distance(BeaconPos,HostPos);
						ClosestBeacon = o;
					}
				}
				else
				{
					Disarm_Beacon(o);
				}
			}
			else if (Get_Object_Type(o) == Team)
			{
				if (Nearest)
				{
					Vector3 BeaconPos = Commands->Get_Position(o);
					BeaconPos.Z = 0;
					if (Commands->Get_Distance(BeaconPos,HostPos) < NearestDistanceFound)
					{
						NearestDistanceFound = Commands->Get_Distance(BeaconPos,HostPos);
						ClosestBeacon = o;
					}
				}
				else 
				{
					Disarm_Beacon(o);
				}
			}
		}
		x = x->NodeNext;
	}
	if (Nearest && ClosestBeacon && As_BeaconGameObj(ClosestBeacon))
	{
		Disarm_Beacon(ClosestBeacon);
	}
}

void Disarm_C4(GameObject *obj)
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
	C4GameObj *o3 = o2->As_C4GameObj();
	if (!o3)
	{
		return;
	}
	o3->Defuse();
}

void Disarm_All_Proxy_C4(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 3)
		{
			if (Get_Player_ID(Get_C4_Planter(o)) == PlayerID)
			{
				Disarm_C4(o);
			}
		}
		x = x->NodeNext;
	}
}

void Disarm_All_C4(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o)
		{
			if (Get_Player_ID(Get_C4_Planter(o)) == PlayerID)
			{
				Disarm_C4(o);
			}
		}
		x = x->NodeNext;
	}
}

const char *Get_Current_Weapon(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return w->Vector[w->current]->WeaponDef->Get_Name();
	}
	return 0;
}

int Get_Weapon_Count(GameObject *obj)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	return w->Vector.Count();
}

const char *Get_Weapon(GameObject *obj,int position)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	if (w->Vector[position])
	{
		return (w->Vector[position]->WeaponDef->Get_Name());
	}
	return 0;
}

bool Has_Weapon(GameObject *obj,const char *weapon)
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
	ArmedGameObj *o3 = o2->As_ArmedGameObj();
	if (!o3)
	{
		return 0;
	}
	WeaponBagClass *w = o3->WeaponBag;
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				return true;
			}
		}
	}
	return false;
}

GameObject *Find_Beacon(int Number,int Team)
{
	if (Number < 0)
	{
		Number = 0;
	}
	if (!Number)
	{
		return 0;
	}
	int Total = 0;
	GameObject *ReturnObj = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
			if (Total == Number) ReturnObj = o;
		}
		x = x->NodeNext;
	}
	return ReturnObj;
}

int Get_C4_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_C4GameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

char Get_Mine_Limit()
{
	return *Mine_Limit;
}

int Get_Beacon_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

int Get_C4_Mode(GameObject *obj)
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
	C4GameObj *o3 = o2->As_C4GameObj();
	if (!o3)
	{
		return 0;
	}
	return o3->AmmoDef->AmmoType.Get();
}

int Get_C4_Count_Proximity(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 3)
		{
			if (Team == 2 || Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

int Get_C4_Count_Remote(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 1)
		{
			if (Team == 2 || Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

GameObject *Get_C4_Planter(GameObject *obj)
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
	C4GameObj *o3 = o2->As_C4GameObj();
	if (!o3)
	{
		return 0;
	}
	if (o3->Owner.Reference)
	{
		return (GameObject *)o3->Owner.Reference->obj;
	}
	return 0;
}

GameObject *Get_C4_Attached(GameObject *obj)
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
	C4GameObj *o3 = o2->As_C4GameObj();
	if (!o3)
	{
		return 0;
	}
	if (o3->Attached.Reference)
	{
		return (GameObject *)o3->Attached.Reference->obj;
	}
	return 0;
}

GameObject *Get_Beacon_Planter(GameObject *obj)
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
	BeaconGameObj *o3 = o2->As_BeaconGameObj();
	if (!o3)
	{
		return 0;
	}
	return o3->Get_Beacon_Owner();
}
