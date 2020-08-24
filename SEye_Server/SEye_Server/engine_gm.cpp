/*	Renegade Scripts.dll
	SSGM engine functions
	Copyright 2007 Vloktboky, WhiteDragon(MDB), Mac, Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#include "scripts.h"
#include "engine.h"
#include "gmmain.h"

typedef cPlayer *(*Find_Player) (int);
extern Find_Player FindPlayer;

typedef DefinitionClass *(*GetFirstDefinition) (unsigned long,char);
GetFirstDefinition Get_First_Definition;
typedef DefinitionClass *(*GetNextDefinition) (DefinitionClass *,unsigned long,char);
GetNextDefinition Get_Next_Definition;
char *ObjectsFile;

void InitEngineSSGM() {
	switch (Exe) {
	case 1: { //server.dat
			Get_First_Definition = (GetFirstDefinition)0x00526540;
			Get_Next_Definition = (GetNextDefinition)0x005265B0;
			ObjectsFile = (char*)0x008110EC;
		}
		break;
	case 2: { //RH73
			Get_First_Definition = (GetFirstDefinition)0x08365FD4;
			Get_Next_Definition = (GetNextDefinition)0x08366064;
			ObjectsFile = (char*)0x08624DC8;
		}
		break;
	case 3: { //RH8
			Get_First_Definition = (GetFirstDefinition)0x08318DD0;
			Get_Next_Definition = (GetNextDefinition)0x08318E5A;
			ObjectsFile = (char*)0x0850CCAE;
		}
		break;
	default: {
		}
		break;
	}
}

GameObject *Get_Veh_Owner(GameObject *obj) {
	if (!As_ScriptableGameObj(obj)) {
		return 0;
	}
	void *ptr = (void *)(obj+0x6EC);
	SimpleDynVecClass<GameObjObserverClass *>* observers = (SimpleDynVecClass<GameObjObserverClass *>*)ptr;
	for (int i = 0;i < observers->Count();i++) {
		if (stricmp((*observers)[i]->Get_Name(),"MDB_SSGM_Vehicle_Owner") == 0) {
			return Commands->Find_Object(((ScriptImpClass*)(*observers)[i])->Get_Int_Parameter("ID"));
		}
	}
	return 0;
}

GameObject *Find_My_Veh(GameObject *Owner) {
	if (!Commands->Get_ID(Owner) || !Owner) {
		return 0;
	}
	GenericSLNode *z = BaseGameObjList->HeadNode;
	while (z != 0) {
		GameObject *obj = As_VehicleGameObj((GameObject *)z->NodeData);
		if (obj && Get_Veh_Owner(obj) == Owner) {
			return obj;
		}
		z = z->NodeNext;
	}
	return 0;
}

char *Get_Objects_File() {
	return ObjectsFile;
}

void Change_Objects_File(const char *Name) {
	if (!Name) {
		return;
	}
	memcpy(ObjectsFile,Name,3);
}

void Track_New_C4() {
	GenericSLNode *z = BaseGameObjList->HeadNode;
	while (z) {
		GameObject *obj = As_C4GameObj((GameObject *)z->NodeData);
		if (obj && !Is_Script_Attached(obj,"MDB_New_C4")) {
			Commands->Attach_Script(obj,"MDB_New_C4","");
			Commands->Send_Custom_Event(obj,obj,9955,0,0);
		}
		z = z->NodeNext;
	}
}

void Do_C4_Command(GameObject *Player) {
	int Remote = 0,Prox = 0;
	int Team = Get_Object_Type(Player);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x != 0) {
		GameObject *o = As_C4GameObj((GameObject *)x->NodeData);
		if (o != 0) {
			if (Get_Object_Type(o) == Team) {
				if (Get_C4_Mode(o) == 3) {
					++Prox;
				}
				else if (Get_C4_Mode(o) == 1) {
					++Remote;
				}
			}
		}
		x = x->NodeNext;
	}
	Console_Input(StrFormat("ppage %d Remote: %d  - Proximity: %d - Total: %d - Limit: %d",Get_Player_ID(Player),Remote,Prox,Remote+Prox,Get_Mine_Limit()).c_str());
}

std::string WideCharToString(const wchar_t *wcs) {
	int length = wcslen(wcs);
	char *text = new char[length+1];
	wcstombs(text,wcs,length+1);
	std::string Ret = text;
	delete[] text;
	return Ret;
}

const wchar_t *Get_Wide_Translated_Preset_Name(GameObject *obj) {
	if (!Commands->Get_ID(obj) || !obj) {
		return L"";
	}
	GameObject *o = As_DamageableGameObj(obj);
	if (!o) {
		return L"";
	}
	DamageableGameObjDef *d = (DamageableGameObjDef *)Get_Definition(obj);
	return Get_Wide_Translated_String(d->TranslatedNameID);
}

std::string Get_String_Player_Name(GameObject *obj) {
	if (!Commands->Get_ID(obj) || !obj) {
		return "None";
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o) {
		return "None";
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x) {
		return "None";
	}
	return WideCharToString(x->PlayerName.Peek_Buffer());
}

std::string Get_String_Player_Name_By_ID(int ID) {
	cPlayer *x = FindPlayer(ID);
	if (!x)
	{
		return "None";
	}
	return WideCharToString(x->PlayerName.Peek_Buffer());
}


const wchar_t *Get_Wide_Player_Name_By_ID(int ID) {
	cPlayer *x = FindPlayer(ID);
	if (!x)
	{
		return L"None";
	}
	return x->PlayerName.Peek_Buffer();
}

bool Is_Base_Defense(GameObject *obj) {
	if (obj == Find_Base_Defense(0) || obj == Find_Base_Defense(1)) {
		return true;
	}
	return false;
}

const wchar_t *Get_Wide_Translated_Preset_Name_By_Preset(const char *Preset) {
	if (!Preset) {
		return L"None";
	}
	DefinitionClass *d = Find_Named_Definition(Preset);
	if (!d) {
		return L"None";
	}
	char *c = (char *)d;
	c += 0x70;
	unsigned long DefID = *(unsigned long *)c;
	return Get_Wide_Translated_String(DefID);
}

const wchar_t *Get_Wide_Team_Name(int Team) {
	if (!Team) {
		return Get_Wide_Translated_String(7198);
	}
	else if (Team == 1) {
		return Get_Wide_Translated_String(7199);
	}
	return L"Neutral";
}

void Set_Bullets_All_Except_C4_Beacon(GameObject *obj,int bullets) {
	if (!Commands->Get_ID(obj) || !obj) {
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o) {
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++) {
		WeaponClass *wc = w->Vector[i];
		if (wc) {
			if (wc->WeaponDef->Style != Style_C4 && wc->WeaponDef->Style != Style_Beacon) {
				wc->InventoryBullets.Set(bullets);
			}
		}
	}
}

void Set_Clip_Bullets_All_Except_C4_Beacon(GameObject *obj,int bullets) {
	if (!Commands->Get_ID(obj) || !obj){
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o) {
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++) {
		WeaponClass *wc = w->Vector[i];
		if (wc) {
			if (wc->WeaponDef->Style != Style_C4 && wc->WeaponDef->Style != Style_Beacon) {
				wc->LoadedBullets.Set(bullets);
			}
		}
	}
}

int Get_Weapon_Style_By_Name(const char *weapon) {
	WeaponDefinitionClass *Weap = Get_Weapon_Definition(weapon);
	if (Weap) {
		return Weap->Style;
	}
	return 0;
}

const wchar_t *Translate_Preset_ID_To_PT_String_Name(int Team,unsigned int ID) {
	PurchaseSettingsDefClass *p = 0;
	unsigned int i;
	for (i = 0; i < 5; i++) {
		p = Get_Purchase_Definition(i,PTTEAM(Team));
		if (!p) {
			continue;
		}
		for (unsigned int j = 0; j < 10; j++) {
			if (p->presetids[j] == ID) {
				return Get_Wide_Translated_String(p->stringids[j]);
			}
		}
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(PTTEAM(Team));
	for (i = 0; i < 4; i++) {
		if (t->presetids[i] == ID) {
			return Get_Wide_Translated_String(t->stringids[i]);
		}
	}
	if (t->beaconpresetid == ID) {
		return Get_Wide_Translated_String(t->beaconstringid);
	}
	return L"No String";
}

void Set_Obj_Radar_Blip_Shape(GameObject *obj,int Shape) {
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x != 0) {
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (Commands->Is_A_Star(o)) {
			Set_Obj_Radar_Blip_Shape_Player(o,obj,Shape);
		}
		x = x->NodeNext;
	}
}

void Set_Obj_Radar_Blip_Color(GameObject *obj,int Color) {
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x != 0) {
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (Commands->Is_A_Star(o)) {
			Set_Obj_Radar_Blip_Color_Player(o,obj,Color);
		}
		x = x->NodeNext;
	}
}

int Get_Powerup_Weapon_Style_By_Obj(GameObject *Powerup) {
	DefinitionClass *powerupdef = Get_Definition(Powerup);
	char *c = (char *)powerupdef;
	if (!c) {
		return -1;
	}
#ifdef RH8
	c += 0xC0;
#else
	c += 0xC4;
#endif
	unsigned long weapondefid = (unsigned long)*(unsigned long *)c;
	if (weapondefid) {
		WeaponDefinitionClass *weapondef = (WeaponDefinitionClass*)Find_Definition(weapondefid);
		if (weapondef) {
			return weapondef->Style;
		}
	}
	return -1;
}

void Enable_Infinite_Ammo() {
	WeaponDefinitionClass *Def = (WeaponDefinitionClass*)Get_First_Definition(WeaponDefID,1);

	while (Def) {
		if (Def->Style != Style_C4 && Def->Style != Style_Beacon) {
			int NegOne = -1;
			Def->MaxInventoryRounds.Set(NegOne);
		}
		Def = (WeaponDefinitionClass*)Get_Next_Definition(Def,WeaponDefID,1);
	}
}

void Attach_Script_To_Definition(const char *Name,const char *Script,const char *Params) {
	ScriptableGameObjDef *Def = (ScriptableGameObjDef*)Find_Named_Definition(Name);
	if (Def) {
		StringClass String;
		String = Script;
		Def->Scripts.Add(String);
		String = Params;
		Def->Parameters.Add(String);
	}
}
