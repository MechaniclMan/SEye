/*	Renegade Scripts.dll
	SSGM misc. functions
	Copyright 2007 Vloktboky, Whitedragon(MDB), Mac, Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#ifndef GMFUNC_H
#define GMFUNC_H

void WriteLog(const std::string &Message, bool ShowTime); //Writes to the renlog
void FDSMessage(const std::string &, const std::string &); //Writes to the SSGM log
std::string FirstMap(); //Gets the first map in the rotation
void LoadSettingStringFirstMap(char *Setting,int Size,const char *Entry,const char *Default="null",bool Global=true,bool Map=true); //Loads a string setting for the first map
std::string Translate_Preset(GameObject *obj); //Translates a gameobject to its display name
std::string Translate_Preset_By_Name(const char *Name); //Translates a preset name to its display name
std::string Translate_Preset_By_ID(unsigned int ID); //Translates a preset ID to its display name
std::string Translate_BPreset(GameObject *obj); //Translates a gameobject to its display name without the team
std::string Translate_Weapon(GameObject *obj); //Translates a gameobject's weapon to its display name
std::string Get_Preset_Info(GameObject *obj); //Gets the display name of the gameobject and its weapon
bool isin(std::string String,std::string Search); //Checks if string1 is in strong2
bool isincs(std::string String,std::string Search); //Checks if string1 is in strong2(case sensitive)
std::string StrFormat(const char* szFmt,...); //Adds sprintf like functionality to std::string
std::string &StrFormat2(std::string &Str,const char* szFmt,...); //Adds sprintf like functionality to std::string
std::string StrFormatAppend(std::string Str,const char* szFmt,...); //Adds sprintf like functionality to std::string
std::string &StrFormatAppend2(std::string &Str,const char* szFmt,...); //Adds sprintf like functionality to std::string
void StrReplace(std::string &String,const std::string &Old,const std::string &New); //Replaces all instances of Old with New in a string
template<class T> std::string ToString(const T &What); //Converts anything to an std::string
void copyfile(const char *From,const char *Dest); //Copys a file
GameObject *GVDA(int Type, int Size, GameObject *obj); //Creates the vehicle damage animations
const char *GetIconBone(GameObject *obj, int IconNum); //Get the bone to attach the vehicle ownership icon to
bool InVector(const std::vector<std::string> &V, const std::string &Name); //Checks if an std::string is in an std::vector
void WriteGamelog(const std::string &Message); //Write to gamelog
void Reverse_Damage(GameObject *obj,float Amount); //Reverses the given amount of damage(better than using Commands->Apply_Damage)
int Get_Highest_Damager(float *Damagers);

#endif
