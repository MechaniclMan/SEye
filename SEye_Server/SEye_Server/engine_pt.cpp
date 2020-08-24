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
#include "engine_pt.h"
#include "engine_net.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_obj2.h"

void *Find_Purchase_Definition;
void *Find_Team_Purchase_Definition;
PurchaseSettingsDefClass **DefinitionArray;

TeamPurchaseSettingsDefClass THUNK *TeamPurchaseSettingsDefClass::Get_Definition(unsigned long team)
IMPLEMENT_THUNK_RETURN(Find_Team_Purchase_Definition)
PurchaseSettingsDefClass THUNK *PurchaseSettingsDefClass::Find_Definition(unsigned long type,unsigned long team)
IMPLEMENT_THUNK_RETURN(Find_Purchase_Definition)

void InitEnginePT(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			DefinitionArray = (PurchaseSettingsDefClass **)0x0085E180;
			Find_Purchase_Definition = (void *)0x006F2BD0;
			Find_Team_Purchase_Definition = (void *)0x006F3430;
			break;
		case 1: //server.dat
			DefinitionArray = (PurchaseSettingsDefClass **)0x0085D358;
			Find_Purchase_Definition = (void *)0x006F2190;
			Find_Team_Purchase_Definition = (void *)0x006F29F0;
			break;
		case 2: //RH73
			DefinitionArray = (PurchaseSettingsDefClass **)0x086CA920;
			Find_Purchase_Definition = (void *)0x08146D08;
			Find_Team_Purchase_Definition = (void *)0x0817A6D4;
			break;
		case 3: //RH8
			DefinitionArray = (PurchaseSettingsDefClass **)0x085F2180;
			Find_Purchase_Definition = (void *)0x08135F3A;
			Find_Team_Purchase_Definition = (void *)0x081658D6;
			break;
		default:
			DefinitionArray = (PurchaseSettingsDefClass **)0;
			Find_Purchase_Definition = (void *)0;
			Find_Team_Purchase_Definition = (void *)0;
			break;
	}
}

TeamPurchaseSettingsDefClass *Get_Team_Purchase_Definition(unsigned long team)
{
	return TeamPurchaseSettingsDefClass::Get_Definition(team);
}

PurchaseSettingsDefClass *Get_Purchase_Definition(unsigned long type, unsigned long team)
{
	return PurchaseSettingsDefClass::Find_Definition(type,team);
}

unsigned int Get_Team_Cost(const char *preset,unsigned int team)
{
	unsigned int ID = Get_Definition_ID(preset);
	if (Get_Team_Purchase_Definition(team)->beaconpresetid == ID)
	{
		return Get_Team_Purchase_Definition(team)->beaconcost;
	}
	for (unsigned int i = 0;i < 5;i++)
	{
		PurchaseSettingsDefClass *p = Get_Purchase_Definition(i,team);
		if (p)
		{
			for (unsigned int j = 0;j < 10;j++)
			{
				if ((p->presetids[j] == ID) || (p->altpresetids[j][0] == ID) || (p->altpresetids[j][1] == ID) || (p->altpresetids[j][2] == ID))
				{
					return p->costs[j];
				}
			}
		}
	}
	return 0;
}

unsigned int Get_Cost(const char *preset)
{
	unsigned int cost = Get_Team_Cost(preset,0);
	if (!cost)
	{
		cost = Get_Team_Cost(preset,1);
	}
	return cost;
}

void Set_Enlisted(unsigned int team, unsigned int position, unsigned int presetid, unsigned int stringid, const char *texture)
{
	if ((team > 1) || (position > 3))
	{
		return;
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	t->presetids[position] = presetid;
	t->stringids[position] = stringid;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	t->textures[position] = texture;
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}
void Set_Beacon(unsigned int team, unsigned int cost, unsigned int presetid, unsigned int stringid, const char *texture)
{
	if (team > 1)
	{
		return;
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	t->beaconcost = cost;
	t->beaconpresetid = presetid;
	t->beaconstringid = stringid;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	t->beacontexture = texture;
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Set_Refill(unsigned int team, unsigned int stringid, const char *texture)
{
	if (team > 1)
	{
		return;
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	t->refillstringid = stringid;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	t->refilltexture = texture;
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Set_Preset(unsigned int team, unsigned int type, unsigned int position, unsigned int cost, unsigned int presetid, unsigned int stringid, const char *texture)
{
	if ((team > 1) || (type > 4) || (position > 9))
	{
		return;
	}
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(type,team);
	if (!p)
	{
		return;
	}
	p->costs[position] = cost;
	p->presetids[position] = presetid;
	p->stringids[position] = stringid;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	p->textures[position] = texture;
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Set_Alternate(unsigned int team, unsigned int type, unsigned int position, unsigned int altpos, unsigned int presetid, const char *texture)
{
	if ((team > 1) || (type > 4) || (position > 9) || (altpos > 2))
	{
		return;
	}
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(type,team);
	p->altpresetids[position][altpos] = presetid;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	p->alttextures[position][altpos] = texture;
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Disable_Enlisted(unsigned int team, unsigned int position)
{
	if ((team > 1) || (position > 3))
	{
		return;
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	t->presetids[position] = 0;
	t->stringids[position] = 0;
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	t->textures[position] = " ";
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Disable_Preset_By_Name(unsigned int Team,const char *Name)
{
	unsigned int ID = Get_Definition_ID(Name);
	PurchaseSettingsDefClass *p = 0;
	unsigned int i;
	for (i = 0; i < 5; i++)
	{
		p = Get_Purchase_Definition(i,Team);
		if (!p)
		{
			continue;
		}
		for (unsigned int j = 0; j < 10; j++)
		{
			if (p->presetids[j] == ID)
			{
				p->presetids[j] = 0;
				p->costs[j] = 1000000;
				p->stringids[j] = 7265;
			}
		}
	}
}

void Disable_Enlisted_By_Name(unsigned int Team,const char *Name)
{
	unsigned int ID = Get_Definition_ID(Name);
	TeamPurchaseSettingsDefClass *p = Get_Team_Purchase_Definition(Team);
	for (unsigned int j = 0; j < 4; j++)
	{
		if (p->presetids[j] == ID)
		{
			p->presetids[j] = 0;
		}
	}
}

void Hide_Preset_By_Name(unsigned int Team,const char *Name)
{
	unsigned int ID = Get_Definition_ID(Name);
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(Team);
	for (unsigned int j = 0; j < 4; j++)
	{
		if (t->presetids[j] == ID)
		{
			t->stringids[j] = 12574;
		}
	}
	PurchaseSettingsDefClass *p = 0;
	unsigned int i;
	for (i = 0; i < 5; i++)
	{
		p = Get_Purchase_Definition(i,Team);
		if (!p)
		{
			continue;
		}
		for (unsigned int j = 0; j < 10; j++)
		{
			if (p->presetids[j] == ID)
			{
				p->stringids[j] = 12574;
			}
		}
	}
}

void Disable_Preset(unsigned int team, unsigned int type, unsigned int position)
{
	if ((team > 1) || (type > 4) || (position > 9))
	{
		return;
	}
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(type,team);
	if (!p)
	{
		return;
	}
#ifdef DEBUG
	memoryPassthrough = true;
	memoryDestroyPassthrough = true;
#endif
	p->presetids[position] = 0;
	p->costs[position] = 0;
	p->stringids[position] = 0;
	p->textures[position] = " ";
	for (unsigned int i = 0;i < 3;++i)
	{
		p->altpresetids[position][i] = 0;
		p->alttextures[position][i] = " ";
	}
#ifdef DEBUG
	memoryPassthrough = false;
	memoryDestroyPassthrough = false;
#endif
}

void Disable_All_Ground_Vehicles(unsigned int team)
{
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(VEHICLES,team);
	if (p)
	{
		unsigned int i;
		for (i = 0;i < 10;i++)
		{
			if (Get_Vehicle_Definition_Mode_By_ID(p->presetids[i]) != FLYING)
			{
				p->presetids[i] = 0;
			}
		}
	}
	p = Get_Purchase_Definition(SECRETVEHICLES,team);
	if (!p)
	{
		return;
	}
	for (int i = 0;i < 10;i++)
	{
		if (Get_Vehicle_Definition_Mode_By_ID(p->presetids[i]) != FLYING)
		{
			p->presetids[i] = 0;
		}
	}
}

void Disable_All_Flying_Vehicles(unsigned int team)
{
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(VEHICLES,team);
	if (p)
	{
		unsigned int i;
		for (i = 0;i < 10;i++)
		{
			if (Get_Vehicle_Definition_Mode_By_ID(p->presetids[i]) == FLYING)
			{
				p->presetids[i] = 0;
			}
		}
	}
	p = Get_Purchase_Definition(SECRETVEHICLES,team);
	if (!p)
	{
		return;
	}
	for (int i = 0;i < 10;i++)
	{
		if (Get_Vehicle_Definition_Mode_By_ID(p->presetids[i]) == FLYING)
		{
			p->presetids[i] = 0;
		}
	}
}

char *Get_Team_Icon(const char *preset,unsigned int team)
{
	unsigned int ID = Get_Definition_ID(preset);
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	if (t->beaconpresetid == ID)
	{
		return t->beacontexture.Peek_Buffer();
	}
	for (unsigned int i = 0;i < 3;i++)
	{
		if (t->presetids[i] == ID)
		{
			return t->textures[i].Peek_Buffer();
		}
	}
	for (unsigned int i = 0;i < 5;i++)
	{
		PurchaseSettingsDefClass *p = Get_Purchase_Definition(i,team);
		if (p)
		{
			for (unsigned int j = 0;j < 10;j++)
			{
				if (p->presetids[j] == ID)
				{
					return p->textures[j].Peek_Buffer();
				}
				if (p->altpresetids[j][0] == ID)
				{
					return p->alttextures[j][0].Peek_Buffer();
				}
				if (p->altpresetids[j][1] == ID)
				{
					return p->alttextures[j][1].Peek_Buffer();
				}
				if (p->altpresetids[j][2] == ID)
				{
					return p->alttextures[j][2].Peek_Buffer();
				}
			}
		}
	}
	return 0;
}

char *Get_Icon(const char *preset)
{
	char *icon = Get_Team_Icon(preset,0);
	if (!icon)
	{
		icon = Get_Team_Icon(preset,1);
	}
	return icon;
}
