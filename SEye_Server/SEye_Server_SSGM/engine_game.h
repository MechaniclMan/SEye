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

//forward declerations
class cGameDataCnc;
class cGameDataSkirmish;
class cGameDataSinglePlayer;
class cPlayer;

//declared here because we dont have them
class WOLGameInfo;
class cPacket;
class BaseControllerClass : public NetworkObjectClass {
public:
	float OperationTimeFactor;
	int team;
	DynamicVectorClass<GameObject *> BuildingList;
	bool IsPowered;
	bool CanGenerateSoldiers;
	bool CanGenerateVehicles;
	bool RadarEnabled;
	bool BaseDestroyed;
	bool BeaconDestroyedBase;
	OBBoxClass BeaconZone;
	unsigned int AnnouncementInterval;
	unsigned int AnnouncementUnknown;
	unsigned int AnnouncementUnknown2;
	unsigned int Unknown1;
	unsigned int Unknown2;
	~BaseControllerClass();
	void Import_Occasional(BitStreamClass &BitStream);
	void Export_Occasional(BitStreamClass &BitStream);
	void Set_Delete_Pending();
	void Delete();
	static BaseControllerClass *Find_Base(int Team);
	GameObject *Get_Harvester_Vehicle();
	GameObject *Find_Building(unsigned int Type);
	void Power_Base(bool Power);
	void Set_Can_Generate_Soldiers(bool CanGenerate);
	void Set_Can_Generate_Vehicles(bool CanGenerate);
	void Destroy_Base();
	void Set_Beacon_Destroyed_Base(bool BeaconDestroyed);
	void Enable_Radar(bool Enable);
};

template <class T1,class T2> class TypedEventPair {
	T1 signal;
	T2 data;
};

template <class T> class Signaler {
public:
	bool Dropped;
	virtual void ReceiveSignal(T &signal);
	virtual void SignalDropped(Signaler &sig);
	virtual ~Signaler();
};
#ifdef WIN32
struct TIME {
	short wYear;
	short wMonth;
	short wDayOfWeek;
	short wDay;
	short wHour;
	short wMinute;
	short wSecond;
	short wMilliseconds;
};
#else
struct TIME {
	int wMonth;
	int wDay;
	int wYear;
	int wHour;
	int wMinute;
	int wSecond;
};
#endif

class cGameData : public Signaler<TypedEventPair<bool,int> > {
public:
	bool GameplayPermitted;
	bool IsDedicated;
	bool IsAutoRestart;
	bool IsFriendlyFirePermitted;
	bool IsTeamChangingAllowed;
	bool IsPassworded;
	bool GrantWeapons;
	bool IsLaddered;
	bool IsClanGame;
	bool UseLagReduction;
	bool RemixTeams;
	bool CanRepairBuildings;
	bool DriverIsAlwaysGunner;
	bool SpawnWeapons;
	bool DoMapsLoop;
	bool MapCycleOver;
	unsigned int MapNumber;
	WideStringClass GameTitle;
	WideStringClass Motd;
	WideStringClass Password;
	char *MapName;
	char *ModName;
	char *MapList[100];
	WideStringClass Owner;
	DynamicVectorClass<WideStringClass> BottomText;
	DynamicVectorClass<WideStringClass> SettingsLimits;
	WideStringClass SettingsDescription;
	unsigned int MaxPlayers;
	unsigned int TimeLimit_Minutes;
	unsigned int IntermissionTime_Seconds;
	unsigned int ExeKey;
	bool ExeVersionsMatch;
	bool StringVersionsMatch;
	unsigned int IP;
	unsigned int Port;
	char *INI;
	unsigned int RadarMode;
	unsigned int CFGModTime;
	unsigned int CurrentPlayers;
	float IntermissionTimeLeft;
	float TimeRemaining_Seconds;
	float MaxWorldDistance;
	unsigned int MinQualifyingTime_Minutes;
	unsigned int WinnerID;
	unsigned int WinType;
	TIME GameStartTime2;
	unsigned int GameStartTime;
	unsigned long FrameCount;
	WideStringClass MVPName;
	unsigned int MVPCount;
	unsigned int GameDuration_Seconds;
	bool IsQuickMatch;
	unsigned long Clan1;
	unsigned long Clan2;
	virtual void ReceiveSignal(TypedEventPair<bool,int> &signal);
	virtual cGameData::~cGameData();
	virtual void On_Game_Begin();
	virtual void On_Game_End();
	virtual void Think();
	virtual void Render();
	virtual void Reset_Game();
	virtual WideStringClass Get_Game_Name() = 0;
	virtual int Get_Game_Type() = 0;
	virtual int Choose_Player_Type(cPlayer *Player,int type,bool SkipAutoTeam);
	virtual void Load_From_Server_Config();
	virtual void Save_To_Server_Config();
	virtual bool Is_Editable_Teaming();
	virtual bool Is_Editable_Clan_Game();
	virtual bool Is_Editable_Friendly_Fire();
	virtual void Soldier_Added(GameObject *obj);
	virtual void Show_Game_Settings_Limits();
	virtual bool Is_Single_Player();
	virtual bool Is_Skirmish();
	virtual bool Is_Cnc();
	virtual cGameDataSinglePlayer *As_Single_Player();
	virtual cGameDataSkirmish *As_Skirmish();
	virtual cGameDataCnc *As_Cnc();
	virtual unsigned int Get_Min_Players();
	virtual bool Is_Game_Over();
	virtual bool Is_Limited();
	virtual bool Is_Valid_Settings(WideStringClass &w,bool b);
	virtual void Export_Tier_1_Data(cPacket &packet);
	virtual void Import_Tier_1_Data(cPacket &packet);
	virtual void Import_Tier_1_Data(const WOLGameInfo &packet);
	virtual void Export_Tier_2_Data(cPacket &packet);
	virtual void Import_Tier_2_Data(cPacket &packet);
	virtual bool Is_Gameplay_Permitted();
	virtual bool Remember_Inventory();
	virtual void Get_Description(WideStringClass &w);
};

class cGameDataCnc : public cGameData {
public:
	bool BaseDestructionEndsGame;
	bool BeaconPlacementEndsGame;
	unsigned int StartingCredits;
	BaseControllerClass GDI;
	BaseControllerClass Nod;
	bool BasesInitalized;
	cGameDataCnc::~cGameDataCnc();
	void On_Game_Begin();
	void On_Game_End();
	void Think();
	void Reset_Game();
	WideStringClass Get_Game_Name();
	int Get_Game_Type();
	void Load_From_Server_Config();
	void Save_To_Server_Config();
	bool Is_Editable_Teaming();
	bool Is_Editable_Clan_Game();
	bool Is_Editable_Friendly_Fire();
	void Soldier_Added(GameObject *obj);
	void Show_Game_Settings_Limits();
	bool Is_Cnc();
	cGameDataCnc *As_Cnc();
	bool Is_Game_Over();
	bool Is_Limited();
	bool Is_Valid_Settings(WideStringClass &w,bool b);
	void Export_Tier_2_Data(cPacket &packet);
	void Import_Tier_2_Data(cPacket &packet);
	bool Is_Gameplay_Permitted();
	void Get_Description(WideStringClass &w);
};

class cGameDataSkirmish : public cGameData {
public:
	bool BaseDestructionEndsGame;
	bool BeaconPlacementEndsGame;
	unsigned int StartingCredits;
	BaseControllerClass GDI;
	BaseControllerClass Nod;
	bool BasesInitalized;
	cGameDataSkirmish::~cGameDataSkirmish();
	void On_Game_Begin();
	void On_Game_End();
	void Think();
	void Reset_Game();
	WideStringClass Get_Game_Name();
	int Get_Game_Type();
	void Load_From_Server_Config();
	void Save_To_Server_Config();
	bool Is_Editable_Teaming();
	bool Is_Editable_Clan_Game();
	bool Is_Editable_Friendly_Fire();
	void Soldier_Added(GameObject *obj);
	void Show_Game_Settings_Limits();
	bool Is_Skirmish();
	cGameDataSkirmish *As_Skirmish();
	bool Is_Game_Over();
	bool Is_Limited();
	void Get_Description(WideStringClass &w);
};

class cGameDataSinglePlayer : public cGameData {
public:
	cGameDataSinglePlayer::~cGameDataSinglePlayer();
	WideStringClass Get_Game_Name();
	int Get_Game_Type();
	int Choose_Player_Type(cPlayer *Player,int type,bool SkipAutoTeam);
	bool Is_Single_Player();
	cGameDataSinglePlayer *As_Single_Player();
	bool Is_Limited();
	bool Remember_Inventory();
};

void InitEngineGame(unsigned int exe);
void Power_Base(int team,bool powered); //Power a base up or down, correctly handles the doubled build time and costs
void Set_Can_Generate_Soldiers(int team,bool cangenerate); //Sets if soliders are purchasable
void Set_Can_Generate_Vehicles(int team,bool cangenerate); //Sets if vehicles are purchaseable
void Destroy_Base(int team); //Destroys a base completly
void Beacon_Destroyed_Base(int team, bool destroyed); //Sets if a base was destroyed by a beacon in the beacon zone
void Enable_Base_Radar(int team, bool enable); //Enables radar for a base, same thing as the communications center does
bool Is_Harvester(GameObject *obj); //Is this object one of the 2 team AI harvesters?
bool Is_Radar_Enabled(int team); //returns if the radar is enabled
int Building_Type(GameObject *obj); //returns the type of a BuildingGameObj
//type values for building objects
#define NONE -1
#define POWER_PLANT 0 //note that this list reflects the list in leveledit
#define SOLDIER_FACTORY 1
#define VEHICLE_FACTORY 2
#define REFINERY 3
#define COM_CENTER 4
#define REPAIR_BAY 5
#define SHRINE 6
#define HELIPAD 7
#define CONYARD 8
#define BASE_DEFENSE 9
bool Is_Building_Dead(GameObject *obj); //Does the game consider the building dead
GameObject *Find_Building(int team,int type); //Find a building by team and type
GameObject *Find_Base_Defense(int team); //Find base defense for a team
bool Is_Map_Flying(); //Is the current map a flying map
GameObject *Create_Building(const char *preset,const Vector3 & Position); //Create a building controller
GameObject *Find_Harvester(int team); //Find this teams current harvester, if any
bool Is_Base_Powered(int team); //Is this teams base powered
bool Can_Generate_Vehicles(int team); //Can this team buy vehicles
bool Can_Generate_Soliders(int team); //Can this team buy soldiers
cGameData *The_Game(); //get the cGameData
cGameDataSkirmish *The_Skirmish_Game(); //get the cGameDataSkirmish
cGameDataCnc *The_Cnc_Game(); //get the cGameDataCnc
cGameDataSinglePlayer *The_Single_Player_Game(); //get the cGameDataSinglePlayer
bool Is_A_Building(GameObject *obj); //is this object any building type
int Get_Building_Count_Team(int Team); //number of buildings a team has that are alive
GameObject *Find_Building_By_Team(int Team); //finds the first building of this team,0 = Nod,1 = GDI
GameObject *Find_Building_By_Name(int Team,const char *Preset_Name); //finds the first building of team where preset name matches name,0 = Nod,1 = GDI
GameObject *Find_Power_Plant(int Team); //finds the first powerplant for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Refinery(int Team); //finds the first refinery for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Repair_Bay(int Team); //finds the first repair bay for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Soldier_Factory(int Team); //finds the first soldier factory for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Airstrip(int Team); //finds the first airstrip for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_War_Factory(int Team); //finds the first war factory for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Vehicle_Factory(int Team); //finds the first airstrip for Team,if none is found,finds the first war factory for Team,0 = Nod,1 = GDI,2 = either
GameObject *Find_Com_Center(int Team); //finds the first communications center for Team,0 = Nod,1 = GDI,2 = either
bool Is_Gameplay_Permitted(); //is gameplay permitted
bool Is_Dedicated(); //returns false if game.exe, true if WFDS/LFDS
bool Is_Linux(); //returns true if linux, false if win32
unsigned int Get_Current_Game_Mode(); //Get the current game mode, 0 = function error, 1 = single player, 2 = skirmish, 3 = WOL, 4 = GameSpy, 5 = LAN. May not always differentiate correctly between WOL, Gamespy and LAN, especially when running as a non-dedicated server.
void Get_Private_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue); //get color for private messages
void Get_Public_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue); //get color for public messages
int Get_Harvester_Preset_ID(int Team); //Get the harvester preset ID for this team
bool Is_Harvester_Preset(GameObject *obj); //Checks if the object has the same preset used for the harvesters
