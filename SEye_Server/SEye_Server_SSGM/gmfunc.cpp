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

#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm>
#include <map>
#include <stdarg.h>
#include "scripts.h"
#include "date.h"
#include "engine.h"
#include "gmmain.h"
#pragma warning(disable: 6031)


//******************************************************************************
//************************ MISCELLANEOUS FUNCTIONS *****************************
//******************************************************************************

std::string FirstMap() {
	copyfile("./server.ini","./data/server.ini");
	char Conf[50],FirstMap[30];
	INIWrapper INI("server.ini");
	INI->Get_String("Server","Config","svrcfg_cnc.ini",Conf,50);
	INI = Conf;
	INI->Get_String("Settings","MapName00","null",FirstMap,30);
	remove("./data/server.ini");
	return FirstMap;
}

void LoadSettingStringFirstMap(char *Setting,int Size,const char *Entry,const char *Default,bool Global,bool Map) {
	Settings->InitINI();
	if (Global) {
		Settings->INI->Get_String("General",Entry,Default,Setting,Size);
	}
	if (Map) {
		Settings->INI->Get_String(FirstMap().c_str(),Entry,Setting,Setting,Size);
	}
}

bool isin(std::string String,std::string Search) {
	std::transform(String.begin(),String.end(),String.begin(),tolower);
	std::transform(Search.begin(),Search.end(),Search.begin(),tolower);
	if (String.find(Search) != std::string::npos) return true;
	return false;
}

bool isincs(std::string String,std::string Search) {
	if (String.find(Search) != std::string::npos) return true;
	return false;
}


std::string StrFormat(const char* Format,...) {
   char Buf[2048];
   va_list va;
   va_start(va,Format);
   vsnprintf(Buf,sizeof(Buf),Format,va);
   va_end(va);
   return Buf;
}

std::string &StrFormat2(std::string &Str,const char* Format,...) {
   char Buf[2048];
   va_list va;
   va_start(va,Format);
   vsnprintf(Buf,sizeof(Buf),Format,va);
   va_end(va);
   Str = Buf;
   return Str;
}

std::string StrFormatAppend(std::string Str,const char* Format,...) {
   char Buf[2048];
   va_list va;
   va_start(va,Format);
   vsnprintf(Buf,sizeof(Buf),Format,va);
   va_end(va);
   Str += std::string(" ") + Buf;
   return Str;
}

std::string &StrFormatAppend2(std::string &Str,const char* Format,...) {
   char Buf[2048];
   va_list va;
   va_start(va,Format);
   vsnprintf(Buf,sizeof(Buf),Format,va);
   va_end(va);
   Str += std::string(" ") + Buf;
   return Str;
}

void StrReplace(std::string &String,const std::string &Old,const std::string &New) {
	unsigned int Pos;
	while ((Pos = String.find(Old)) != std::string::npos) {
		String.replace(Pos,Old.size(),New);
	}
}

template<class T> std::string ToString(const T &What) {
	std::stringstream Stream;
	Stream << What;
	return Stream.str();
}

void copyfile(const char *From,const char *Dest) {
	remove(Dest);
#ifdef WIN32
	CopyFile(From,Dest,0);
#else
	std::ifstream In;
	In.open(From);
	std::ofstream Out;
	Out.open(Dest);
	std::string Buff;
	if (In.is_open()) {
		while (!In.eof()) {
			std::getline(In,Buff);
			Out << Buff << std::endl;
		}
	}
	In.close();
	Out.close();
#endif
}

void WriteLog(const std::string &Message, bool ShowTime) {
	date logdate;
	logdate.refreshdate();
	std::ofstream FP;
	FP.open(StrFormat("renlog_%s.txt",logdate.get_date_string()).c_str(),std::ios::app);
	std::string messageprint;
	if (!ShowTime) {
		StrFormat2(messageprint,"0 %s",Message.c_str());
	}
	else {
		time_t rawtime;
		tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		StrFormat2(messageprint,"[%02d:%02d:%02d] %s",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,Message.c_str());
	}
	FP << messageprint << std::endl;
	FP.close();
}

std::string Translate_Preset(GameObject *obj) {
	if (!Commands->Get_ID(obj) || !obj) return "None";
	if (Is_C4(obj)) {
		if (Get_C4_Mode(obj) == 1) {
			return "Remote C4";
		}
		else if (Get_C4_Mode(obj) == 3) {
			return "Proximity C4";
		}
		else if (Get_C4_Mode(obj) == 2) {
			return "Timed C4";
		}
	}
	char TransName[256];
	const char *preset = Commands->Get_Preset_Name(obj);
	Settings->INI->Get_String("Translated_Preset",preset,"0",TransName,255);
	std::string Ret = TransName;
	if (Ret == "0") {
		Ret = WideCharToString(Get_Wide_Translated_Preset_Name(obj));
		if (Ret == "No String" || Ret == "None") {
			Ret = preset;
		}
		else if (Is_Building(obj) || Is_DecorationPhys(obj) || Is_Harvester_Preset(obj)) {
			if (!isin(Ret,WideCharToString(Get_Wide_Team_Name(Get_Object_Type(obj))))) {
				Ret = StrFormat ("%ls %s",Get_Wide_Team_Name(Get_Object_Type(obj)),Ret.c_str());
			}
		}
	}
	return Ret;
}

std::string Translate_Preset_By_Name(const char *Name) {
	if (!Name) return "None";
	char TransName[256];
	Settings->INI->Get_String("Translated_Preset",Name,"0",TransName,255);
	std::string Ret = TransName;
	if (Ret == "0") {
		Ret = WideCharToString(Get_Wide_Translated_Preset_Name_By_Preset(Name));
		if (Ret == "No String" || Ret == "None") {
			Ret = Name;
		}
	}
	return Ret;
}

std::string Translate_Preset_By_ID(unsigned int ID) {
	const char *Name = Get_Definition_Name(ID);
	if (!Name) return "None";
	char TransName[256];
	Settings->INI->Get_String("Translated_Preset",Name,"0",TransName,255);
	std::string Ret = TransName;
	if (Ret == "0") {
		Ret = WideCharToString(Get_Wide_Translated_Preset_Name_By_Preset(Name));
		if (Ret == "no string" || Ret == "None") {
			Ret = Name;
		}
	}
	return Ret;
}

std::string Translate_BPreset(GameObject *obj) {
	if (!Commands->Get_ID(obj) || !obj) return "None";
	if (Is_C4(obj)) {
		if (Get_C4_Mode(obj) == 1) {
			return "Remote C4";
		}
		else if (Get_C4_Mode(obj) == 3) {
			return "Proximity C4";
		}
		else if (Get_C4_Mode(obj) == 2) {
			return "Timed C4";
		}
	}
	char TransName[256];
	const char *preset = Commands->Get_Preset_Name(obj);
	Settings->INI->Get_String("Translated_Preset",preset,"0",TransName,255);
	std::string Ret = TransName;
	if (Ret == "0") {
		Ret = WideCharToString(Get_Wide_Translated_Preset_Name(obj));
		if (Ret == "no string" || Ret == "None") {
			Ret = preset;
		}
	}
	return Ret;
}

std::string Translate_Weapon(GameObject *obj) {
	if (!Is_Armed(obj)) {
		return "None";
	}
	char TransName[256];
	const char *Weap = Get_Current_Weapon(obj);
	Settings->INI->Get_String("Translated_Preset",Weap,WideCharToString(Get_Current_Wide_Translated_Weapon(obj)).c_str(),TransName,255);
	std::string Ret = TransName;
	if (Ret == "no string" || Ret == "None") {
		Ret = Weap;
	}
	return Ret;
}

std::string Get_Preset_Info(GameObject *obj) {
	if (!Commands->Get_ID(obj) || !obj) {
		return "None";
	}
	if (Commands->Is_A_Star(obj)) {
		if (Get_Vehicle(obj)) {
			return Translate_Preset(Get_Vehicle(obj));
		}
		else {
			return StrFormat("%s/%s",Translate_Preset(obj).c_str(),Translate_Weapon(obj).c_str());
		}
	}
	return Translate_Preset(obj);
}

GameObject *GVDA(int Type, int Size, GameObject *obj) {
	GameObject *Ret = Commands->Create_Object("Invisible_Object",Commands->Get_Position(obj));
	int Random;
	if (Type == 1) {
		if (Size == 1) {
			Random = Commands->Get_Random_Int(1,3);
			if (Random == 1) {
				Commands->Set_Model(Ret,"ag_pucreation");
			}
			else if (Random == 2) {
				Commands->Set_Model(Ret,"ag_smwoodexp");
			}
			else {
				Commands->Set_Model(Ret,"ag_pucreation");
			}
		}
		else if (Size == 2) {
			Random = Commands->Get_Random_Int(1,3);
			if (Random == 1) {
				Commands->Set_Model(Ret,"ag_bgwoodexp");
			}
			else if (Random == 2) {
				Commands->Set_Model(Ret,"ag_brlexp1");
			}
			else {
				Commands->Set_Model(Ret,"ag_bgwoodexp");
			}
		}
	}
	else if (Type == 2) {
		Commands->Set_Model(Ret,"ag_flame01");
	}
	else {
		Commands->Set_Model(Ret,"e_dsp_tibgas");
	}
	Commands->Attach_Script(Ret,"MDB_SSGM_Destroy_When_Object_Destroyed",ToString(Commands->Get_ID(obj)).c_str());
	return Ret;
}

void FDSMessage(const std::string &Message, const std::string &LogHeader) {
	if (!Settings->EnableLogging && LogHeader != "_GAMELOG") return;
	date logdate;
	logdate.refreshdate();

	std::ofstream FP;
	FP.open(StrFormat("%s_%s.txt",Settings->FDSLogRoot.c_str(),logdate.get_date_string()).c_str(),std::ios::app);

	time_t rawtime;
	tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (Settings->EchoLog && LogHeader != "_GAMELOG") printf("%s\n",Message.c_str());
	FP << StrFormat("[%02d:%02d:%02d] %s %s",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,LogHeader.c_str(),Message.c_str()) << std::endl;
	FP.close();
}

const char *GetIconBone(GameObject *obj, int IconNum) {
	if (Data->Mod) {
		return 0;
	}
	else if (Is_Stealth(obj)) {
		return 0;
	}
	else {
		const char *Preset = Commands->Get_Preset_Name(obj);
		if (IconNum == 1) {
			if (strstr(Preset,"CnC_Nod_Buggy")) return "muzzlea0";
			else if (strstr(Preset,"CnC_Nod_APC")) return "barrel";
			else if (strstr(Preset,"CnC_Nod_Mobile_Artillery")) return "muzzlea0";
			else if (strstr(Preset,"CnC_Nod_Light_Tank")) return "muzzlea0";
			else if (strstr(Preset,"CnC_Nod_Flame_Tank")) return "muzzlea0";
			else if (strstr(Preset,"CnC_Nod_Apache")) return "muzzleb0";
			else if (strstr(Preset,"CnC_GDI_Humm-vee")) return "muzzlea0";
			else if (strstr(Preset,"CnC_GDI_APC")) return "muzzlea0";
			else if (strstr(Preset,"CnC_GDI_MRLS")) return "muzzlea0";
			else if (strstr(Preset,"CnC_GDI_Medium_Tank")) return "muzzlea0";
			else if (strstr(Preset,"CnC_GDI_Mammoth_Tank")) return "muzzleb0";
			else if (strstr(Preset,"CnC_GDI_Orca")) return "muzzlea0";
			else if (strstr(Preset,"recon")) return "muzzlea0";
			else if (strstr(Preset,"Recon")) return "muzzlea0";
			else if (strstr(Preset,"Mobileart")) return "muzzlea0";
			else if (strstr(Preset,"towhumvee")) return "muzzlea0";
			return "muzzlea0";
		}
		else if (IconNum == 2) {
			if (strstr(Preset,"CnC_Nod_Flame_Tank")) return "muzzlea1";
			else if (strstr(Preset,"CnC_Nod_Apache")) return "muzzleb1";
			else if (strstr(Preset,"CnC_GDI_MRLS")) return "muzzlea1";
			else if (strstr(Preset,"CnC_GDI_Mammoth_Tank")) return "muzzleb1";
			else if (strstr(Preset,"CnC_GDI_Orca")) return "muzzlea1";
		}
	}
	return 0;
}

bool InVector(const std::vector<std::string> &V, const std::string &Name) {
	if (V.empty()) {
		return false;
	}
	std::vector<std::string>::const_iterator it;
	for (it = V.begin(); it != V.end(); ++it) {
		if ((*it) == Name) {
			return true;
		}
	}
	return false;
}

void WriteGamelog(const std::string &Message) {
	if (Settings->NewGamelog && !Data->AllowGamelogWrite) {
		return;
	}

	if (Settings->MergeGamelogRenlog) {
		FDSMessage(Message,"_GAMELOG");
	}
	else {
		std::ofstream FP;
		if (Settings->NewGamelog) {
			FP.open("gamelog2.txt",std::ios::app);
		}
		else {
			FP.open("gamelog.txt",std::ios::app);
		}
		time_t rawtime;
		tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		FP << StrFormat("[%02d:%02d:%02d] ",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec) << Message << std::endl;
		FP.close();
	}
}

void Reverse_Damage(GameObject *obj,float Amount) {
	float Health = Commands->Get_Health(obj);
	float Armor = Commands->Get_Shield_Strength(obj);
	if (Health != Commands->Get_Max_Health(obj)) {
		Health += Amount;
		float OverFlow = Health-Commands->Get_Max_Health(obj);
		if (OverFlow > 0) {
			Armor += OverFlow;
			Commands->Set_Shield_Strength(obj,Armor);
		}
		Commands->Set_Health(obj,Health);
	}
	else {
		Commands->Set_Shield_Strength(obj,Armor+Amount);
	}
}

int Get_Highest_Damager(float *Damagers) {
    float dammax = 0.0f;
	int playerid = 0;
	int maxplayers = The_Game()->MaxPlayers;
	for (int i = 1; i <= maxplayers; i++)
		if (Damagers[i] > dammax) {
			dammax = Damagers[i];
			playerid = i;
		}
	return playerid;
}

