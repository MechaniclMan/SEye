/*	Renegade Scripts.dll
	Team and player data related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
class PlayerDataClass {
public:
#ifdef WIN32
	~PlayerDataClass();
#else
	virtual ~PlayerDataClass();
#endif
	virtual void Reset_Player();
	virtual void Set_Score(float score);
	virtual void Increment_Score(float score);
	virtual void Set_Money(float money);
	virtual void Increment_Money(float money);
	virtual bool Purchase_Item(int money);
	virtual void Apply_Damage_Points(float points,DamageableGameObj *damager);
	virtual void Apply_Death_Points(float points,DamageableGameObj *damager);
	FloatDataSafeClass Score;
	FloatDataSafeClass Money;
	ReferencerClass Owner;
	float PunishTimer;
	float GameTime;
	float SessionTime;
	int EnemiesKilled;
	int AlliesKilled;
	int ShotsFired;
	int HeadShots;
	int TorsoShots;
	int ArmShots;
	int LegShots;
	int CrotchShots;
	float FinalHealth;
	int PowerupsCollected;
	int VehiclesDestroyed;
	float VehicleTime;
	int KillsFromVehicle;
	int Squishes;
	float CreditGrant;
	int BuildingDestroyed;
	int HeadHit;
	int TorsoHit;
	int ArmHit;
	int LegHit;
	int CrotchHit;
	int WeaponFired;
	SimpleDynVecClass<int> WeaponsFired;
	SimpleDynVecClass<int> WeaponsFired2;
};

class cPlayer : public PlayerDataClass, public NetworkObjectClass {
public:
	~cPlayer();
	void Reset_Player();
	void Set_Score(float score);
	void Increment_Score(float score);
	void Set_Money(float money);
	void Increment_Money(float money);
	unsigned int Get_Network_Class_ID();
	void Import_Creation(BitStreamClass &BitStream);
	void Import_Rare(BitStreamClass &BitStream);
	void Import_Occasional(BitStreamClass &BitStream);
	void Export_Creation(BitStreamClass &BitStream);
	void Export_Rare(BitStreamClass &BitStream);
	void Export_Occasional(BitStreamClass &BitStream);
	void Delete();
	void Set_Player_Type(int type);
	void Set_Ladder_Points(int amount);
	void Set_Rung(int amount);
	Vector3 Get_Color();
	bool IsHuman;
	WideStringClass PlayerName;
	int PlayerId;
	IntDataSafeClass LadderPoints;
	IntDataSafeClass Kills;
	IntDataSafeClass Deaths;
	IntDataSafeClass PlayerType;
	IntDataSafeClass Rung;
	IntDataSafeClass WolRank;
	short WolPoints;
	int DamageScaleFactor;
	int Ping;
	int JoinTime;
	int TotalTime;
	unsigned long IpAddress;
	int Fps;
	unsigned long LastUpdateTimeMs;
	int FastSortKey;
	int NumWolGames;
	bool IsWaitingForIntermission;
	int GameSpyAuthState;
	unsigned long GameSpyAuthStateEntryTimeMs;
	StringClass GameSpyChallengeString;
	StringClass GameSpyHashId;
	int GameSpyKickState;
	unsigned long GameSpyKickStateEntryTimeMs;
	bool IsInGame;
	bool IsActive;
	unsigned long WolClanId;
};

void InitEnginePlayer(unsigned int exe);
GameObject *Get_GameObj(int PlayerID); //convert a player ID into a GameObject
long Get_Player_ID(GameObject *obj); //convert a GameObject into a player ID
const char *Get_Player_Name(GameObject *obj); //converts a GameObject into a player name
const char *Get_Player_Name_By_ID(int PlayerID); //gets the player name from a player ID. Will return NULL if that player doesnt exist.
void Change_Team(GameObject *obj,int Team); //changes the team of a player given their GameObject and also kills the player so they respwan,passing anything other than 0 = Nod,1 = GDI will crash
void Change_Team_By_ID(int PlayerID,int Team); //changes the team of a player given their ID and also kills the player so they respwan,passing anything other than 0 = Nod,1 = GDI will crash
int Get_Player_Count(); //gets the count of how many players there are
int Get_Team_Player_Count(int Team); //gets the count of players for a given team,0 = Nod,1 = GDI)
int Get_Team(int PlayerID); //get the team of a player
int Get_Rank(int PlayerID); //get the rank of a player
int Get_Kills(int PlayerID); //get the kills of a player
int Get_Deaths(int PlayerID); //get the deaths of a player
float Get_Score(int PlayerID); //get the score of a player
float Get_Money(int PlayerID); //get the money of a player
float Get_Kill_To_Death_Ratio(int PlayerID); //get the kill/death ratio of a player
GameObject *Get_Part_Name(const char *name1); //Will return the player with this string as part of their name if there is exactly one player with it
int Get_Part_Names(const char *name1); //Will return the count of players with this string as part of their name
void Get_Team_Color(unsigned int team, unsigned int *red, unsigned int *green, unsigned int *blue); //get color for a team
void Get_Player_Color(int PlayerID, unsigned int *red, unsigned int *green, unsigned int *blue); //get color for a player
GameObject *Get_GameObj_By_Player_Name(const char *name); //get the gameobject of a player given their name
bool Purchase_Item(GameObject *obj,int cost); //Pass a soldier object & a cost to deduct that much money from the soldier. Returns true if the transaction suceeded, false otherwise
void Set_Ladder_Points(int PlayerID,int amount); //Set the ladder points of a player
void Set_Rung(int PlayerID,int amount); //Set the rung of a player
void Set_Money(int PlayerID,float amount); //Set the money of a player
void Set_Score(int PlayerID,float amount); //Set the score of a player
GameObject *Find_First_Player(int Team); //finds the first player of Team,0 = Nod,1 = GDI,2 = either
bool Change_Player_Team(GameObject *obj,bool Retain_Score,bool Retain_Money,bool Show_Host_Message); //changes the players team
int Tally_Team_Size(int team); //gets the team size for a team
float Get_Team_Score(int team); //gets the score for a team (same as Game_Info uses)
char *stristr(const char *m_pStr1, const char *m_pStr2); //like strstr but case insenstive
void Send_Custom_All_Players(int message,GameObject *sender,int team); //send a custom to all players
float Steal_Team_Credits(float percentage, int team); //Steal credits from a team
float Get_Team_Credits(int team); //Count the total credits for a team
extern SList<cPlayer *> *PlayerList; //Current player list
void Change_Team_2(GameObject *obj,int Team); //changes the team of a player given their GameObject without killing the player,passing anything other than 0 = Nod,1 = GDI will crash
int Get_Player_Type(GameObject *obj); //Get the player type of a player from the cPlayer
const wchar_t *Get_Wide_Player_Name(GameObject *obj); //Converts a GameObject into a player name
