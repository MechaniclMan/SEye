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

#include "scripts.h"
#include "engine.h"
#include "gmmain.h"

SettingsLoader::SettingsLoader(const char *INIname) : ININame(newstr(INIname)) {
	ININameData = new char[strlen(ININame)+5];
	sprintf(ININameData,"TEMP%s",ININame);
}

SettingsLoader::~SettingsLoader() {
	INI.Release();
	remove(ININameData);
	delete[] ININame;
	delete[] ININameData;
}

void SettingsLoader::InitINI() {
	copyfile(StrFormat("./%s",ININame).c_str(),StrFormat("./data/%s",ININameData).c_str());
	INI.Release();
	INI = ININameData;
}

void SettingsLoader::Load() {
	InitINI();
	ShowSetChangeMess = false;
}

void SettingsLoader::LoadSString(std::string &Setting,const char *Entry,const char *Default,bool Global,bool Map,bool ShowNewSet) {
	std::string Temp = Setting;
	char TempSet[500];
	if (Global) {
		INI->Get_String("General",Entry,Default,TempSet,500);
		if (Map) {
			char TempSet2[500];
			INI->Get_String(Data->CurrMap,Entry,TempSet,TempSet2,500);
			Setting = TempSet2;
		}
		else {
			Setting = TempSet;
		}
	}
	else {
		INI->Get_String(Data->CurrMap,Entry,Default,TempSet,500);
		Setting = TempSet;
	}
	if (ShowNewSet && Temp != Setting && !ShowSetChangeMess) {
		ShowSetChangeMess = true;
		FDSMessage(StrFormat("New settings detected and loaded from %s!",ININame),"_GENERAL");
	}
}

void SettingsLoader::LoadFloat(float &Setting,const char *Entry,float Default,bool Global,bool Map,bool ShowNewSet) {
	float Temp = Setting;
	if (Global) {
		Setting = INI->Get_Float("General",Entry,Default);
		if (Map) {
			Setting = INI->Get_Float(Data->CurrMap,Entry,Setting);
		}
	}
	else {
		Setting = INI->Get_Float(Data->CurrMap,Entry,Default);
	}
	if (ShowNewSet && Temp != Setting && !ShowSetChangeMess) {
		ShowSetChangeMess = true;
		FDSMessage(StrFormat("New settings detected and loaded from %s!",ININame),"_GENERAL");
	}
}

void SettingsLoader::LoadInt(int &Setting,const char *Entry,int Default,bool Global,bool Map,bool ShowNewSet) {
	int Temp = Setting;
	if (Global) {
		Setting = INI->Get_Int("General",Entry,Default);
		if (Map) {
			Setting = INI->Get_Int(Data->CurrMap,Entry,Setting);
		}
	}
	else {
		Setting = INI->Get_Int(Data->CurrMap,Entry,Default);
	}
	if (ShowNewSet && Temp != Setting && !ShowSetChangeMess) {
		ShowSetChangeMess = true;
		FDSMessage(StrFormat("New settings detected and loaded from %s!",ININame),"_GENERAL");
	}
}

void SettingsLoader::LoadBool(bool &Setting,const char *Entry,bool Default,bool Global,bool Map,bool ShowNewSet) {
	bool Temp = Setting;
	if (Global) {
		Setting = INI->Get_Bool("General",Entry,Default);
		if (Map) {
			Setting = INI->Get_Bool(Data->CurrMap,Entry,Setting);
		}
	}
	else {
		Setting = INI->Get_Bool(Data->CurrMap,Entry,Default);
	}
	if (ShowNewSet && Temp != Setting && !ShowSetChangeMess) {
		ShowSetChangeMess = true;
		FDSMessage(StrFormat("New settings detected and loaded from %s!",ININame),"_GENERAL");
	}
}

void SettingsLoader::LoadVector3(Vector3 &Setting,const char *Entry,Vector3 Default,bool Global,bool Map,bool ShowNewSet) {
	LoadFloat(Setting.X,StrFormat("%s_X",Entry).c_str(),Default.X,Global,Map,ShowNewSet);
	LoadFloat(Setting.Y,StrFormat("%s_Y",Entry).c_str(),Default.Y,Global,Map,ShowNewSet);
	LoadFloat(Setting.Z,StrFormat("%s_Z",Entry).c_str(),Default.Z,Global,Map,ShowNewSet);
}

void SettingsLoader::LoadList(std::vector<std::string> &Setting,const char *Section,bool ShowNewSet) {
	std::vector<std::string> Temp = Setting;
	Setting.clear();
	for (int z = 1; ; ++z) {
		char value[500];
		INI->Get_String(Section,StrFormat("%02d",z).c_str(),"NULL",value,500);
		if (!stricmp(value,"NULL")) {
			break;
		}
		Setting.push_back(value);
	}
	if (ShowNewSet && Temp != Setting && !ShowSetChangeMess) {
		ShowSetChangeMess = true;
		FDSMessage(StrFormat("New settings detected and loaded from %s!",ININame),"_GENERAL");
	}
}
