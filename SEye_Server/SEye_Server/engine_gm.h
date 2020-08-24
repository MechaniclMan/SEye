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
#ifdef DEBUG
#undef new
#undef delete
#endif
#include <string>
#include <vector>
#ifdef DEBUG
#include "mmgr.h"
#endif

//Wrapper for INIClass
class INIWrapper {
private:
	INIClass *INI;
	INIWrapper(const INIWrapper&) { }
	INIWrapper &operator=(const INIWrapper&) { return *this; }
public:

	INIWrapper() {
		INI = 0;
	}

	INIWrapper(const char *ini) {
		INI = Get_INI(ini);
	}

	INIWrapper(INIClass *ini) {
		INI = ini;
	}

	INIWrapper &operator=(INIClass *ini) {
		if (INI && ini != INI) Release_INI(INI);
		INI = ini;
		return *this;
	}

	INIWrapper &operator=(const char *ini) {
		if (INI) Release_INI(INI);
		INI = Get_INI(ini);
		return *this;
	}

	inline void Release() {
		if (INI) Release_INI(INI);
		INI = 0;
	}

	inline INIClass *operator->() const {
		return INI;
	}

	~INIWrapper() {
		if (INI) Release_INI(INI);
	}

};

#define WeaponDefID 0xB001
#define AmmoDefID 0xB002

void InitEngineSSGM();
char *Get_Objects_File(); //Returns the extension of the current objects file
void Change_Objects_File(const char *Name); //Changes the extension of the objects file to load
GameObject *Get_Veh_Owner(GameObject *obj); //Get the owner of a vehicle
GameObject *Find_My_Veh(GameObject *obj); //Find my vehicle
void Do_C4_Command(GameObject *Player); //!c4 command
std::string WideCharToString(const wchar_t *wcs); //Converts a wide char to an std::string
const wchar_t *Get_Wide_Translated_Preset_Name(GameObject *obj); //Get the translated name for the preset of this object, if it has one
std::string Get_String_Player_Name(GameObject *obj); //Converts a GameObject into a player name
std::string Get_String_Player_Name_By_ID(int ID); //Converts a player ID into a player name
const wchar_t *Get_Wide_Player_Name_By_ID(int ID); //Converts a player ID into a player name
bool Is_Base_Defense(GameObject *obj); //Checks if the object is a base defense
const wchar_t *Get_Wide_Translated_Preset_Name_By_Preset(const char *Preset); //Get the translated name for the preset name
const wchar_t *Get_Wide_Team_Name(int Team); //Get the name of a team
void Set_Bullets_All_Except_C4_Beacon(GameObject *obj,int bullets); //Set the ammo of all of this player's weapons, except C4 or beacons
void Set_Clip_Bullets_All_Except_C4_Beacon(GameObject *obj,int bullets); //Set the clip ammo of all of this player's weapons, except C4 or beacons
int Get_Weapon_Style_By_Name(const char *weapon); //Get the style of a weapon given its preset name
const wchar_t *Translate_Preset_ID_To_PT_String_Name(int Team,unsigned int ID); //Gets the translated name of the PT icon that is used to buy this preset ID
void Set_Obj_Radar_Blip_Shape(GameObject *obj,int Shape); //Workaround for broken Commands->Set_Obj_Radar_Blip_Shape
void Set_Obj_Radar_Blip_Color(GameObject *obj,int Color); //Workaround for broken Commands->Set_Obj_Radar_Blip_Color
int Get_Powerup_Weapon_Style_By_Obj(GameObject *Powerup); //Get the style of the weapon that this powerup grants
void Enable_Infinite_Ammo(); //Gives all weapons besides C4 and beacons infinite ammo
void Attach_Script_To_Definition(const char *Name,const char *Script,const char *Params); //Attaches a script to a preset definition

