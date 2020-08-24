/*	Renegade Scripts.dll
	SSGM settings loading code
	Copyright 2007 Whitedragon(MDB), Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

struct SettingsLoader {
	SettingsLoader(const char *ININame);
	~SettingsLoader();
	//Functions that load settings
	void InitINI();
	void Load();
	void LoadSString(std::string &Setting,const char *Entry,const char *Default="null",bool Global=true,bool Map=true,bool ShowNewSet=true);
	void LoadFloat(float &Setting,const char *Entry,float Default=1.0,bool Global=true,bool Map=true,bool ShowNewSet=true);
	void LoadInt(int &Setting,const char *Entry,int Default=1,bool Global=true,bool Map=true,bool ShowNewSet=true);
	void LoadBool(bool &Setting,const char *Entry,bool Default=true,bool Global=true,bool Map=true,bool ShowNewSet=true);
	void LoadVector3(Vector3 &Setting,const char *Entry,Vector3 Default=Vector3(0.0f,0.0f,0.0f),bool Global=true,bool Map=true,bool ShowNewSet=true);
	void LoadList(std::vector<std::string> &Setting,const char *Section,bool ShowNewSet=true);
	
	char *ININame;
	char *ININameData;
	INIWrapper INI;
	bool ShowSetChangeMess;

private:
	SettingsLoader();
	SettingsLoader(SettingsLoader&);
	SettingsLoader& operator=(SettingsLoader&);
};

#endif
