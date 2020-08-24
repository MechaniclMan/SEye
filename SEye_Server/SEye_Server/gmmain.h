/*	Renegade Scripts.dll
	SSGM main functions and classes
	Copyright 2007 Vloktboky, Whitedragon(MDB), Mac, Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/

#ifndef GMMAIN_H
#define GMMAIN_H

#pragma warning(disable: 4702 4996)


#define SSGMVersion "2.0.2"
#define ScriptsVersion "3.4.1"

#include <vector>
#include <string>
#include "gmfunc.h"
#include "gmsettingsclass.h"
#include "gmcommandclass.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define DLLEXPORT __declspec(dllexport)
#else 
#define stricmp strcasecmp
#define DLLEXPORT
#endif


typedef ScriptClass *(*cs) (const char *);


//General SSGM settings
struct SSGMSettings : public virtual SettingsLoader {
	SSGMSettings(const char *ININame);

	virtual void Load();

	virtual bool Is_Disabled(const char *Preset);
	virtual bool Is_Disabled(GameObject *obj);
	virtual bool Is_Sniper(const char *Preset);
	virtual bool Is_Sniper(GameObject *obj);

	//Settings added in 1.0
	bool LogBuildingDamage;
	bool LogBuildingKills;
	bool BuildingDeathRewardPage;
	float BuildingDamageInt;
	bool AFKKick;
	int AFKWait;
	std::string AFKPageMessage;
	bool DropWeapons;
	bool LogPlayerPurchase;
	bool LogPlayerKills;
	bool LogVehiclePurchase;
	bool Weather;
	std::string WeatherType;
	bool LogVehicleKills;
	bool EnableVehicleDeathAnim;
	bool EnableVehicleDamageAnim;
	std::string OBGPageMessage;
	bool OBGEnable;
	//Settings added in 1.1
	bool DestroyPlayerVeh;
	//Settings added in 1.2 through 1.3
	bool DisableBaseDefenses;
	bool DisablePowerPlants;
	bool DisableRefineries;
	bool DisableSoldierFactories;
	bool DisableVehicleFactories;
	bool DisableRepairPads;
	bool DisableCommCenters;
	//Settings added in 1.3.3
	bool Gamelog; //Gamelog isn't cool enough to get its own settings struct
	//Settings added in 1.3.4
	bool EnableVehicleWreckages;
	//Settings added in 1.4
	bool DefenseShell;
	bool CombatRefill;
	unsigned int RefillTime;
	bool EnableVehOwn;
	int GameMode;
	bool InvinBuild;
	bool DisableBeacons;
	bool EnableLogging;
	bool EchoLog;
	bool Gamelog_Archive_Logfiles;
	bool SpawnWeap;
	bool NewGamelog;
	//Settings added in 1.4.1
	int ForceTeam;
	//Settings added in 1.5
	bool BWDetector;
	int BWDefault;
	bool BWPunishKick;
	bool MergeGamelogRenlog;
	//Settings added in 2.0
	std::vector<std::string> ModNames;
	std::string FDSLogRoot;
	std::vector<std::string> SvSKillMsg;
	std::vector<std::string> VvSKillMsg;
	std::vector<std::string> DisableList;
	std::vector<std::string> WeaponStartEngL1;
	std::vector<std::string> WeaponStartEngL2;
	std::vector<std::string> WeaponStartOther;
	bool InfiniteAmmo;
	bool ExtraKillMessages;
	bool LogPowerupPurchase;
	bool LogBeacons;
	bool LogC4;
	std::vector<std::string> SniperChars;
};

//CTF specific settings
struct CTFSettings : public virtual SettingsLoader {
	CTFSettings(const char *ININame);

	virtual void Load();

	//CTF settings added in 2.0
	int CTFClass;
	std::string CTFClassName;
	bool CTFEnableReverse;
	bool CTFReverse;
	bool CTFRegenForHolder;
	float CTFRegenAmount;
	std::string CTFFlagPreset;
	std::string CTFFlagModel[2];
	std::string CTFFlagBackPreset;
	std::string CTFPedPreset[2];
	int CTFCapLimit;
	Vector3 CTFFlagOffset;
	Vector3 CTFPedPos[2];
	float CTFCapPoints;
	float CTFCapPointsTeam;
	float CTFCapMoney;
	float CTFCapMoneyTeam;
	float CTFReturnTime;
	bool CTFFriendlyFlagRadar;
	bool CTFEnemyFlagRadar;
};

//CTF specific data
struct CTFData {
	CTFData();
	int CTFFlagHolder[2];
	int CTFFlagAttached[2][2];
	int CTFCaps[2];
	int CTFFlagLoc[2];
	int CTFFlagIcon[2];
};

//Crate specific settings
struct CrateSettings : public virtual SettingsLoader {
	CrateSettings(const char *ININame);

	virtual void Load();

	//Settings added in 1.3.4
	bool EnableCrates;
	//Settings added in 1.4
	bool EnableNewCrates;
	bool VehCrate;
	//Settings added in 2.0
	Vector3	CrateVehSpawnPos[2];
	int	CrateWeapon;
	int	CrateMoney;	
	int	CratePoints;
	int	CrateVehicle;
	int	CrateDeath;
	int	CrateTiberium;
	int	CrateAmmo;
	int	CrateArmor;
	int	CrateHealth;
	int	CrateCharacter;
	int	CrateButterFingers;
	int	CrateRefill;
	int	CrateBeacon;
	int	CrateSpy;
	int	CrateStealth;
	int	CrateThief;
};

//Crate specific data
struct CrateData {
	CrateData();
	bool CrateExists;
	int	CrateLastPickup;
	int CrateID;
};

//Combination of all the settings structs
struct SettingsStruct : public SSGMSettings, public CrateSettings, public CTFSettings {
	SettingsStruct(const char *ININame);
	virtual void Load();
private:
	SettingsStruct(SettingsStruct&);
	SettingsStruct& operator=(SettingsStruct&);
};

typedef bool(*DDEHook) (const char *);

enum PluginType {
	StandAlone,
	Scripts,
	Plugin,
};

struct PluginInfo {
	std::string Name;
	PluginType Type;
	std::string Version;
	std::string SSGMVer;
	bool SSGMVerRequired;
	std::string File;
	cs CreateScriptHandle;
	//Hooks
	ChatHook ChatHookHandle;
	HostHook HostHookHandle;
	PlayerJoin PlayerJoinHookHandle;
	PlayerLeave PlayerLeaveHookHandle;
	LoadLevelHook LevelLoadedHookHandle;
	LoadLevelHook GameOverHookHandle;
	ConsoleOutputHook ConsoleOutputHookHandle;
	DDEHook DDEHookHandle;
#ifdef WIN32
	HMODULE Handle;
	virtual bool Load(HMODULE PHandle,const char *FileName);
#else
	void *Handle;
	virtual bool Load(void *PHandle,const char *FileName);
#endif
	virtual void Unload();
	virtual void *Get_Address(const char *Func);
};

//General SSGM data
struct SSGMData {
	SSGMData();
	virtual inline std::string &Get_Mod_Name();
	virtual void Add_Chat_Command(ChatCommandClass *Ptr,const char *Command,int ChatType,int NumParams,int GameMode);
	virtual void Copy_Chat_Commands(const std::vector<ChatCommandInfo*> *List);
	virtual void Trigger_Chat_Command(int ID,int Type,const std::string &Command,const TokenClass &Text);
	char CurrMap[50];
	unsigned int Mod;
	int PlayerPurchaseHookID;
	int VehiclePurchaseHookID;
	int PowerupPurchaseHookID;
	int ObjectHookID;
	bool AllowGamelogWrite;
	ObjectCreateHookStruct *ObjectHookStruct;
	std::vector<PluginInfo*> Plugins;
	std::vector<ChatCommandInfo*> Commands;
};

//Combination of all the data structs
struct DataStruct : public SSGMData, public CrateData, public CTFData {
};

extern SettingsStruct *Settings; //Settings struct
extern DataStruct *Data; //Data struct

#endif
