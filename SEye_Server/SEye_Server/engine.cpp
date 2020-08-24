/*	Renegade Scripts.dll
	Engine calls
	Copyright 2006 Vloktboky, WhiteDragon(MDB), Joshua "NeoSaber" Kraft, Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif
#include "scripts.h"
#include "engine.h"
#include <float.h>
#include <stddef.h>
int Exe = 6;
#ifdef WIN32
typedef void (*SetTransform) (Matrix3D *mat);
typedef Matrix3D *(*GetTransform) ();
typedef void (*ReInit) (DefinitionClass *def);
typedef char *(*GetRemoteHost) (int player);
typedef sockaddr_in *(*GetAddress) ();
typedef void (*PowerupGrant) (GameObject *obj,int powerup,bool unk);
typedef bool (*IsAvailable) (void);
typedef int (*BandwidthOut) (sockaddr_in *addr);
typedef bool (*RequestVehicle) (int Preset,float Delay,GameObject *Owner);
typedef void (*ToggleFlyMode) (void);
typedef GameObject *(*GetBeaconOwner) ();
typedef void (*GetObjColor) (Vector3 *color);
typedef void (*Defuse) ();
typedef unsigned int (*GetCount) ();
typedef wchar_t *(*GetVehicleName) ();
typedef void (*CompletlyDamaged) (void *offense);
typedef void (*cbc) (void);
#else
typedef void (*SetTransform) (GameObject *obj,Matrix3D *mat);
typedef Matrix3D *(*GetTransform) (GameObject *obj);
typedef void (*ReInit) (GameObject *obj,DefinitionClass *def);
typedef char *(*GetRemoteHost) (char *connection,int player);
typedef sockaddr_in *(*GetAddress) (void *host);
typedef void (*PowerupGrant) (DefinitionClass *def,GameObject *obj,int powerup,bool unk);
typedef bool (*IsAvailable) (GameObject *obj);
typedef int (*BandwidthOut) (void *packetmgr,sockaddr_in *addr);
typedef bool (*RequestVehicle) (GameObject *obj,int Preset,float Delay,GameObject *Owner);
typedef void (*ToggleFlyMode) (GameObject *obj);
typedef GameObject *(*GetBeaconOwner) (GameObject *Obj);
typedef void (*GetObjColor) (Vector3 *color, GameObject *obj);
typedef void (*Defuse) (GameObject *obj);
typedef unsigned int (*GetCount) (GameObject *obj);
typedef wchar_t *(*GetVehicleName) (GameObject *obj);
typedef void (*CompletlyDamaged) (GameObject *obj,void *offense);
typedef void (*cbc) (GameObject *obj);
#endif
typedef GameObject *(*ago) (GameObject *obj);
typedef const char *(*Get_Name) (char *ro);
typedef const char *(*Get_Htree) (char *ro);
typedef char *(*FindTeam) (int team);
typedef int (*tts) (int team);
typedef cPlayer *(*Find_Player) (int);
typedef DefinitionClass *(*Find_Named_Def) (const char *name,bool twiddle);
typedef void *(*rennew) (unsigned long size);
typedef void (*rendelete) (void *ptr);
typedef void (*GrantSupplies) (GameObject *obj);
typedef const char *(*GetArmorName) (unsigned int ID);
typedef unsigned int(*GetArmorType) (const char *name);
typedef void (*ConsoleInput)(const char *);
typedef bool (*CheckTransitions) (GameObject *obj,bool unk);
typedef bool (*GetSafeDataUintRef) (void *Handle,unsigned int *&Data);
typedef bool (*GetSafeDataIntRef) (void *Handle,int *&Data);
typedef bool (*SetSafeDataUintRef) (void *Handle,unsigned int &Data);
typedef bool (*SetSafeDataIntRef) (void *Handle,int &Data);
typedef void *(*GameModeFind) (const char *mode);
typedef bool (*GetSafeDataFloatRef) (void *Handle,float *&Data);
typedef bool (*SetSafeDataFloatRef) (void *Handle,float &Data);
typedef TDBObjClass *(*GetTDBObject) (unsigned long ID);
typedef void (*GetTeamColor) (Vector3 *color,int team);
typedef DefinitionClass *(*FindDefinition) (unsigned long ID,bool b);
typedef GameObject *(*CreateLibraryObject) (const char *preset);

SetTransform Set_Transform;
GetTransform Get_Transform;
FindTeam Find_Team;
tts TallyTeamSize;
Find_Player FindPlayer;
Find_Named_Def FindNamedDef;
ReInit SoldierReInit;
char **ServerConnection;
GetRemoteHost Get_Remote_Host;
rennew RenNew = 0;
rennew RenVecNew = 0;
rendelete RenDelete;
rendelete RenVecDelete;
GetAddress Get_Address;
GrantSupplies Grant_Supplies;
PowerupGrant Powerup_Grant;
GetArmorName Get_Armor_Name;
GetArmorType Get_Armor_Type;
void *MarkOwnerDirty;
IsAvailable Is_Available_For_Purchase;
BandwidthOut Bandwidth_Out;
void *PacketManager;
char *Mine_Limit;
RequestVehicle Request_Vehicle;
ToggleFlyMode ToggleFly;
void *SetMaxHealth;
void *SetMaxShieldStrength;
ConsoleInput Parse_Console_Input;
void *Output_To_Console;
void *SetPlayerType;
void *GetPlayerCount;
CheckTransitions Check_Transitions;
GetSafeDataUintRef Get_Safe_Data_Uint_Ref;
SetSafeDataUintRef Set_Safe_Data_Uint_Ref;
GetSafeDataIntRef Get_Safe_Data_Int_Ref;
SetSafeDataIntRef Set_Safe_Data_Int_Ref;
void *Game;
void *Skirmish_Game;
void *Cnc_Game;
void *Single_Player_Game;
SList<GameObject> *BuildingGameObjList;
SList<GameObject> *SmartGameObjList;
SList<GameObject> *BaseGameObjList;
char *SpawnCharNod;
char *SpawnCharGDI;
GameModeFind Game_Mode_Find;
bool *IsListed;
int *GameType;
void *Get_Safe_Data_Int;
void *Get_Safe_Data_Uint;
void *Get_Safe_Data_Float;
GetSafeDataFloatRef Get_Safe_Data_Float_Ref;
SetSafeDataFloatRef Set_Safe_Data_Float_Ref;
GetTDBObject Get_TDB_Object;
GetBeaconOwner Get_Beacon_Owner;
GetTeamColor Get_Color_For_Team;
void *GetColor;
GetObjColor Get_Obj_Color;
Defuse C4Defuse;
GetCount GetVehicleCount;
void *FindBase;
float *GDIHouseColor;
float *NodHouseColor;
float *PrivateMessageColor;
float *PublicMessageColor;
GetVehicleName Get_VehicleName;
CompletlyDamaged Completly_Damaged;
void *GetHarvester;
void *PowerBase;
void *SetCanGenerateSoldiers;
void *SetCanGenerateVehicles;
void *DestroyBase;
void *SetBeaconDestroyedBase;
void *EnableRadar;
void *GetINI;
void *ReleaseINI;
void *IniClassGetInt;
void *IniClassGetDouble;
void *IniClassGetBool;
void *IniClassGetString;
FindDefinition Find_Definition;
void *Find_Purchase_Definition;
void *Find_Team_Purchase_Definition;
PurchaseSettingsDefClass **DefinitionArray;
void *FindBuilding;
bool *IsMapVTOL;
void *FindClosestZone;
void *InsideMe;
CreateLibraryObject Create_Library_Object;
void *StartObservers;
cbc Collect_Building_Components;
void *overlap;
void *SetLadderPoints;
void *SetRung;
unsigned int *GameMode;
FileFactoryClass **TheFileFactory;
void *ServerKillConnection;
unsigned int *StringClass::ReservedMask;
char *StringClass::m_TempStrings;
char **StringClass::m_EmptyString;
char *StringClass::m_NullChar;

wchar_t **WideStringClass::m_FreeTempPtr;
wchar_t **WideStringClass::m_ResTempPtr;
wchar_t **WideStringClass::m_EmptyString;
wchar_t *WideStringClass::m_NullChar;
int *WideStringClass::m_UsedTempStringCount;

void *CriticalLock;
#ifdef WIN32
class CriticalSectionClass {
	unsigned int x;
public:
	void Lock();
	void Unlock()
	{
		x = 0;
	}
};
void THUNK CriticalSectionClass::Lock()
IMPLEMENT_THUNK(CriticalLock)
#else
class CriticalSectionClass {
	unsigned int x;
	unsigned int y;
public:
	void Lock()
	{
	}
	void Unlock()
	{
	}
};
#endif
CriticalSectionClass *StringClass::m_Mutex;
CriticalSectionClass *WideStringClass::m_TempMutex;
#ifdef WIN32
int THUNK IntDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Int)
float THUNK FloatDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Float)
unsigned int THUNK UIntDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Uint)
bool IntDataSafeClass::Set(int &data)
{
	return Set_Safe_Data_Int_Ref(Data,data);
}
bool FloatDataSafeClass::Set(float &data)
{
	return Set_Safe_Data_Float_Ref(Data,data);
}
bool UIntDataSafeClass::Set(unsigned int &data)
{
	return Set_Safe_Data_Uint_Ref(Data,data);
}
#else
union un {
	float f;
	void *v;
};
int IntDataSafeClass::Get()
{
	return (int)Data;
}
float FloatDataSafeClass::Get()
{
	un u;
	u.v = Data;
	return u.f;
}
unsigned int UIntDataSafeClass::Get()
{
	return (unsigned int)Data;
}
bool IntDataSafeClass::Set(int &data)
{
	Data = (void *)data;
	return true;
}
bool FloatDataSafeClass::Set(float &data)
{
	un u;
	u.f = data;
	Data = u.v;
	return true;
}
bool UIntDataSafeClass::Set(unsigned int &data)
{
	Data = (void *)data;
	return true;
}
#endif

#ifndef BHS
_Enable_Stealth_Player Enable_Stealth_Player;
_Set_Fog_Enable_Player Set_Fog_Enable_Player;
_Set_Fog_Range_Player Set_Fog_Range_Player;
_Set_Background_Music_Player Set_Background_Music_Player;
_Fade_Background_Music_Player Fade_Background_Music_Player;
_Stop_Background_Music_Player Stop_Background_Music_Player;
_Enable_Radar_Player Enable_Radar_Player;
_Display_GDI_Player_Terminal_Player Display_GDI_Player_Terminal_Player;
_Display_NOD_Player_Terminal_Player Display_NOD_Player_Terminal_Player;
_Set_Screen_Fade_Color_Player Set_Screen_Fade_Color_Player;
_Set_Screen_Fade_Opacity_Player Set_Screen_Fade_Opacity_Player;
_Force_Camera_Look_Player Force_Camera_Look_Player;
_Enable_HUD_Player Enable_HUD_Player;
_Create_Sound_Player Create_Sound_Player;
_Create_2D_Sound_Player Create_2D_Sound_Player;
_Create_2D_WAV_Sound_Player Create_2D_WAV_Sound_Player;
_Create_3D_WAV_Sound_At_Bone_Player Create_3D_WAV_Sound_At_Bone_Player;
_Create_3D_Sound_At_Bone_Player Create_3D_Sound_At_Bone_Player;
_Set_Display_Color_Player Set_Display_Color_Player;
_Display_Text_Player Display_Text_Player;
_Display_Int_Player Display_Int_Player;
_Display_Float_Player Display_Float_Player;
_Set_Obj_Radar_Blip_Shape_Player Set_Obj_Radar_Blip_Shape_Player;
_Set_Obj_Radar_Blip_Color_Player Set_Obj_Radar_Blip_Color_Player;
ss Set_Scope;
sh Set_HUD_Texture;
aoch AddObjectCreateHook;
roch RemoveObjectCreateHook;
akh AddKeyHook;
rkh RemoveKeyHook;
ach AddChatHook;
avh AddVersionHook;
ahh AddHostHook;
allh AddLoadLevelHook;
allh AddGameOverHook;
apjh AddPlayerJoinHook;
aplh AddPlayerLeaveHook;
aph AddPowerupPurchaseHook;
aph AddVehiclePurchaseHook;
aph AddCharacterPurchaseHook;
apmh AddPowerupPurchaseMonHook;
apmh AddVehiclePurchaseMonHook;
apmh AddCharacterPurchaseMonHook;
rph RemovePowerupPurchaseHook;
rph RemoveVehiclePurchaseHook;
rph RemoveCharacterPurchaseHook;
rph RemovePowerupPurchaseMonHook;
rph RemoveVehiclePurchaseMonHook;
rph RemoveCharacterPurchaseMonHook;
gcmt GetCurrentMusicTrack;
gbhsv GetBHSVersion;
sit Set_Info_Texture;
cit Clear_Info_Texture;
svl Set_Vehicle_Limit;
gvl Get_Vehicle_Limit;
sm Send_Message;
smp Send_Message_Player;
sw Set_Wireframe_Mode;
lnhi Load_New_HUD_INI;
rw Remove_Weapon;
upd Update_PT_Data;
crm Change_Radar_Map;
gbm Get_Build_Time_Multiplier;
scb Set_Currently_Building;
icb Is_Currently_Building;
acoh AddConsoleOutputHook;
acrch AddCRCHook;
adh AddDataHook;
srt Set_Reticle_Texture1;
srt Set_Reticle_Texture2;
sfc Set_Fog_Color;
sfcp Set_Fog_Color_Player;
sfm Set_Fog_Mode;
sfmp Set_Fog_Mode_Player;
ssn Set_Shader_Number;
sfd Set_Fog_Density;
sfdp Set_Fog_Density_Player;
ctr Change_Time_Remaining;
ctl Change_Time_Limit;
dps Display_GDI_Sidebar;
dps Display_NOD_Sidebar;
dps Display_Security_Dialog;
#endif

void Console_Input(const char *Input)
{
	if (strlen(Input) > 255)
	{
		return;
	}
	Parse_Console_Input(Input);
}

void THUNK Console_Output(const char *Output,...)
IMPLEMENT_THUNK(Output_To_Console)
int THUNK Get_Player_Count()
IMPLEMENT_THUNK_RETURN(GetPlayerCount)
cGameData THUNK *The_Game()
IMPLEMENT_THUNK_RETURN(Game)
cGameDataSkirmish THUNK *The_Skirmish_Game()
IMPLEMENT_THUNK_RETURN(Skirmish_Game)
cGameDataCnc THUNK *The_Cnc_Game()
IMPLEMENT_THUNK_RETURN(Cnc_Game)
cGameDataSinglePlayer THUNK *The_Single_Player_Game()
IMPLEMENT_THUNK_RETURN(Single_Player_Game)
INIClass THUNK *Get_INI(char const *filename)
IMPLEMENT_THUNK_RETURN(GetINI)
void THUNK Release_INI(INIClass *ini)
IMPLEMENT_THUNK(ReleaseINI)
int THUNK INIClass::Get_Int(char const *section,char const *entry,int defaultvalue)
IMPLEMENT_THUNK_RETURN(IniClassGetInt)
float THUNK INIClass::Get_Float(char const *section,char const *entry,float defaultvalue)
IMPLEMENT_THUNK_RETURN_X(IniClassGetDouble)
bool THUNK INIClass::Get_Bool(char const *section,char const *entry,bool defaultvalue)
IMPLEMENT_THUNK_RETURN(IniClassGetBool)
void THUNK INIClass::Get_String(char const *section,char const *entry,char const *defaultvalue,char *result,int size)
IMPLEMENT_THUNK(IniClassGetString)
TeamPurchaseSettingsDefClass THUNK *TeamPurchaseSettingsDefClass::Get_Definition(unsigned long team)
IMPLEMENT_THUNK_RETURN(Find_Team_Purchase_Definition)
PurchaseSettingsDefClass THUNK *PurchaseSettingsDefClass::Find_Definition(unsigned long type,unsigned long team)
IMPLEMENT_THUNK_RETURN(Find_Purchase_Definition)
BaseControllerClass THUNK *BaseControllerClass::Find_Base(int Team)
IMPLEMENT_THUNK_RETURN(FindBase)
GameObject THUNK *BaseControllerClass::Get_Harvester_Vehicle()
IMPLEMENT_THUNK_RETURN(GetHarvester)
void THUNK BaseControllerClass::Power_Base(bool Power)
IMPLEMENT_THUNK(PowerBase)
void THUNK BaseControllerClass::Set_Can_Generate_Soldiers(bool CanGenerate)
IMPLEMENT_THUNK(SetCanGenerateSoldiers)
void THUNK BaseControllerClass::Set_Can_Generate_Vehicles(bool CanGenerate)
IMPLEMENT_THUNK(SetCanGenerateVehicles)
void THUNK BaseControllerClass::Destroy_Base()
IMPLEMENT_THUNK(DestroyBase)
void THUNK BaseControllerClass::Enable_Radar(bool Enable)
IMPLEMENT_THUNK(EnableRadar)
void THUNK BaseControllerClass::Set_Beacon_Destroyed_Base(bool BeaconDestroyed)
IMPLEMENT_THUNK(SetBeaconDestroyedBase)
GameObject THUNK *BaseControllerClass::Find_Building(unsigned int Type)
IMPLEMENT_THUNK_RETURN(FindBuilding)
GameObject THUNK *Find_Closest_Zone(Vector3 &Location,unsigned int Type)
IMPLEMENT_THUNK_RETURN(FindClosestZone)
unsigned int THUNK Overlap_Test(const OBBoxClass &box,const Vector3 &v)
IMPLEMENT_THUNK_RETURN(overlap)
void THUNK Destroy_Connection(int PlayerID)
IMPLEMENT_THUNK(ServerKillConnection)
bool THUNK ScriptZoneGameObj::Inside_Me(SmartGameObj *obj)
IMPLEMENT_THUNK_RETURN(InsideMe)
void THUNK ScriptableGameObj::Start_Observers()
IMPLEMENT_THUNK(StartObservers);
void THUNK cPlayer::Set_Player_Type(int type)
IMPLEMENT_THUNK(SetPlayerType)
void THUNK cPlayer::Set_Ladder_Points(int amount)
IMPLEMENT_THUNK(SetLadderPoints)
void THUNK cPlayer::Set_Rung(int amount)
IMPLEMENT_THUNK(SetRung)
Vector3 THUNK cPlayer::Get_Color()
IMPLEMENT_THUNK_RETURN_V(GetColor)
void THUNK DefenceObjectClass::Set_Max_Health(float health)
IMPLEMENT_THUNK(SetMaxHealth)
void THUNK DefenceObjectClass::Set_Max_Shield_Strength(float shieldstrength)
IMPLEMENT_THUNK(SetMaxShieldStrength)
void THUNK DefenceObjectClass::Mark_Owner_Dirty()
IMPLEMENT_THUNK(MarkOwnerDirty)

#ifdef WIN32
extern "C" extern void Init();
void *operator new (size_t nbytes)
{
	if (!RenNew)
	{
		Init();
	}
	void *x = RenNew((unsigned long)nbytes);
	return x;
}

void* operator new[](size_t nbytes)
{
	if (!RenVecNew)
	{
		Init();
	}
	void *x = RenVecNew((unsigned long)nbytes);
	return x;
}

void operator delete(void *ptr)
{
	RenDelete(ptr);
}

void operator delete[](void *ptr)
{
	RenVecDelete(ptr);
}
#endif

void InitEngine()
{
	switch (Exe)
	{
	case 0: //game.exe
		{
			StringClass::m_Mutex = (CriticalSectionClass *)0x0083DC08;
			StringClass::ReservedMask = (unsigned int *)0x0083EC10;
			StringClass::m_TempStrings = (char *)0x0083DC0C;
			WideStringClass::m_FreeTempPtr = (wchar_t **)0x00809D40;
			WideStringClass::m_ResTempPtr = (wchar_t **)0x0083F440;
			WideStringClass::m_EmptyString = (wchar_t **)0x00809D3C;
			WideStringClass::m_NullChar = (wchar_t *)0x0083F43C;
			WideStringClass::m_UsedTempStringCount = (int *)0x0083F438;
			WideStringClass::m_TempMutex = (CriticalSectionClass *)0x0083F024;
			CriticalLock = (void *)0x00402AA0;
			SetLadderPoints = (void *)0x0040FC90;
			SetRung = (void *)0x00410790;
			ServerKillConnection = (void *)0x00462190;
			TheFileFactory = (FileFactoryClass **)0x00809E74;
			GameMode = (unsigned int *)0x0081F5F0;
			overlap = (void *)0x00616B90;
			Collect_Building_Components = (cbc)0x006843E0;
			StartObservers = (void *)0x006B6C40;
			Create_Library_Object = (CreateLibraryObject)0x006C6420;
			FindClosestZone = (void *)0x00722B90;
			InsideMe = (void *)0x00722B40;
			IsMapVTOL = (bool *)0x0085E31C;
			FindBuilding = (void *)0x006EF6D0;
			PowerBase = (void *)0x006EF310;
			SetCanGenerateSoldiers = (void *)0x006EF420;
			SetCanGenerateVehicles = (void *)0x006EF440;
			DestroyBase = (void *)0x006EF840;
			SetBeaconDestroyedBase = (void *)0x006EF8D0;
			EnableRadar = (void *)0x006EFD00;
			DefinitionArray = (PurchaseSettingsDefClass **)0x0085E180;
			StringClass::m_EmptyString = (char **)0x00809D38;
			StringClass::m_NullChar = (char *)0x0083EC0C;
			Find_Purchase_Definition = (void *)0x006F2BD0;
			Find_Team_Purchase_Definition = (void *)0x006F3430;
			Find_Definition = (FindDefinition)0x00526760;
			GetHarvester = (void *)0x006EFD60;
			Completly_Damaged = (CompletlyDamaged)0x0070AA90;
			GetINI = (void *)0x006DAB30;
			ReleaseINI = (void *)0x006DABE0;
			IniClassGetInt = (void *)0x005E10B0;
			IniClassGetDouble = (void *)0x005E1670;
			IniClassGetBool = (void *)0x005E27A0;
			IniClassGetString = (void *)0x005E1DE0;
			Get_VehicleName = (GetVehicleName)0x0067C740;
			Get_Beacon_Owner = (GetBeaconOwner)0x0070AA50;
			Get_Color_For_Team = (GetTeamColor)0x006D99E0;
			GetColor = (void *)0x0040E530;
			Get_Obj_Color = (GetObjColor)0x006D97B0;
			C4Defuse = (Defuse)0x0070D610;
			GetVehicleCount = (GetCount)0x006EE060;
			FindBase = (void *)0x006EF790;
			PrivateMessageColor = (float *)0x0082FC20;
			PublicMessageColor = (float *)0x0082FBA0;
			GDIHouseColor = (float *)0x0085CAA8;
			NodHouseColor = (float *)0x0085CA98;
			Get_TDB_Object = (GetTDBObject)0x0076C5B0;
			Get_Safe_Data_Int = (void *)0x00408280;
			Get_Safe_Data_Uint = (void *)0x00408280;
			Get_Safe_Data_Float = (void *)0x00413510;
			Get_Safe_Data_Float_Ref = (GetSafeDataFloatRef)0x00428F80;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0x00694F90;
			GameType = (int *)0x00856518;
			IsListed = (bool *)0x0082FD94;
			Game_Mode_Find = (GameModeFind)0x004372B0;
			SpawnCharGDI = (char *)0x007F5428;
			SpawnCharNod = (char *)0x007F5440;
			PacketManager = (void *)0x00854708;
			Bandwidth_Out = (BandwidthOut)0x0061D310;
			Mine_Limit = (char *)0x0070DD95;
			RenNew = (rennew)0x00672B70;
			RenVecNew = (rennew)0x00672B70;
			RenDelete = (rendelete)0x00672C80;
			RenVecDelete = (rendelete)0x00672C80;
			Get_Address = (GetAddress)0x0061DAF0;
			Get_Remote_Host = (GetRemoteHost)0x0061A840;
			ServerConnection = (char **)0x00820D9C;
			Game = (void *)0x00477CA0;
			Find_Team = (FindTeam)0x0041DA10;
			TallyTeamSize = (tts)0x004170D0;
			Skirmish_Game = (void *)0x00477CC0;
			Cnc_Game = (void *)0x00477CD0;
			Single_Player_Game = (void *)0x00477CB0;
			Get_Safe_Data_Uint_Ref = (GetSafeDataUintRef)0x00695AF0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0x00696200;
			Get_Safe_Data_Int_Ref = (GetSafeDataIntRef)0x00407B70;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0x00414350;
			Check_Transitions = (CheckTransitions)0x006D55C0;
			Set_Transform = (SetTransform)0x006A5EF0;
			Get_Transform = (GetTransform)0x006A5F10;
			BuildingGameObjList = (SList<GameObject> *)0x00856FE8;
			SmartGameObjList = (SList<GameObject> *)0x00856FD8;
			BaseGameObjList = (SList<GameObject> *)0x00856FF8;
			FindPlayer = (Find_Player)0x004157E0;
			FindNamedDef = (Find_Named_Def)0x00526860;
			SoldierReInit = (ReInit)0x006C7410;
			SetMaxHealth = (void *)0x00691820;
			SetMaxShieldStrength = (void *)0x006930E0;
			Grant_Supplies = (GrantSupplies)0x00470AC0;
			Powerup_Grant = (PowerupGrant)0x006F09F0;
			Get_Armor_Name = (GetArmorName)0x006877D0;
			Get_Armor_Type = (GetArmorType)0x00687750;
			MarkOwnerDirty = (void *)0x00693740;
			Is_Available_For_Purchase = (IsAvailable)0x006EE010;
			Request_Vehicle = (RequestVehicle)0x006EE1A0;
			ToggleFly = (ToggleFlyMode)0x006CFC80;
			Parse_Console_Input = (ConsoleInput)0x004287E0;
			Output_To_Console = (void *)0x00428B50;
			SetPlayerType = (void *)0x0040D600;
			GetPlayerCount = (void *)0x00417040;
		}
		break;
	case 1: //server.dat
		{
			StringClass::m_Mutex = (CriticalSectionClass *)0x0083CDF0;
			StringClass::ReservedMask = (unsigned int *)0x0083DDF8;
			StringClass::m_TempStrings = (char *)0x0083CDF4;
			WideStringClass::m_FreeTempPtr = (wchar_t **)0x00808F18;
			WideStringClass::m_ResTempPtr = (wchar_t **)0x0083E628;
			WideStringClass::m_EmptyString = (wchar_t **)0x00808F14;
			WideStringClass::m_NullChar = (wchar_t *)0x0083E624;
			WideStringClass::m_UsedTempStringCount = (int *)0x0083E620;
			WideStringClass::m_TempMutex = (CriticalSectionClass *)0x0083E20C;
			CriticalLock = (void *)0x00402AA0;
			SetLadderPoints = (void *)0x0040FC90;
			SetRung = (void *)0x00410790;
			ServerKillConnection = (void *)0x00461AC0;
			TheFileFactory = (FileFactoryClass **)0x0080904C;
			GameMode = (unsigned int *)0x0081E7D8;
			overlap = (void *)0x00616430;
			Collect_Building_Components = (cbc)0x00683C80;
			StartObservers = (void *)0x006B64E0;
			Create_Library_Object = (CreateLibraryObject)0x006C5CC0;
			FindClosestZone = (void *)0x00722150;
			InsideMe = (void *)0x00722100;
			IsMapVTOL = (bool *)0x0085D4F4;
			FindBuilding = (void *)0x006EEC90;
			PowerBase = (void *)0x006EE8D0;
			SetCanGenerateSoldiers = (void *)0x006EE9E0;
			SetCanGenerateVehicles = (void *)0x006EEA00;
			DestroyBase = (void *)0x006EEE00;
			SetBeaconDestroyedBase = (void *)0x006EEE90;
			EnableRadar = (void *)0x006EF2C0;
			DefinitionArray = (PurchaseSettingsDefClass **)0x0085D358;
			StringClass::m_EmptyString = (char **)0x00808F10;
			StringClass::m_NullChar = (char *)0x0083DDF4;
			Find_Purchase_Definition = (void *)0x006F2190;
			Find_Team_Purchase_Definition = (void *)0x006F29F0;
			Find_Definition = (FindDefinition)0x00526000;
			GetHarvester = (void *)0x006EF320;
			Completly_Damaged = (CompletlyDamaged)0x0070A050;
			GetINI = (void *)0x006DA3D0;
			ReleaseINI = (void *)0x006DA480;
			IniClassGetInt = (void *)0x005E0950;
			IniClassGetDouble = (void *)0x005E0F10;
			IniClassGetBool = (void *)0x005E2040;
			IniClassGetString = (void *)0x005E1680;
			Get_VehicleName = (GetVehicleName)0x0067BFE0;
			Get_Beacon_Owner = (GetBeaconOwner)0x0070A010;
			Get_Color_For_Team = (GetTeamColor)0x006D9280;
			GetColor = (void *)0x0040E530;
			Get_Obj_Color = (GetObjColor)0x006D9050;
			C4Defuse = (Defuse)0x0070CBD0;
			GetVehicleCount = (GetCount)0x006ED620;
			FindBase = (void *)0x006EED50;
			PrivateMessageColor = (float *)0x0082EE08;
			PublicMessageColor = (float *)0x0082ED88;
			GDIHouseColor = (float *)0x0085BC90;
			NodHouseColor = (float *)0x0085BC80;
			Get_TDB_Object = (GetTDBObject)0x0076BE50;
			Get_Safe_Data_Int = (void *)0x00408280;
			Get_Safe_Data_Uint = (void *)0x00408280;
			Get_Safe_Data_Float = (void *)0x00413510;
			Get_Safe_Data_Float_Ref = (GetSafeDataFloatRef)0x00429100;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0x00694830;
			GameType = (int *)0x00855700;
			IsListed = (bool *)0x0082EF7C;
			Game_Mode_Find = (GameModeFind)0x00437350;
			SpawnCharGDI = (char *)0x007F442C;
			SpawnCharNod = (char *)0x007F4444;
			PacketManager = (void *)0x008538F0;
			Bandwidth_Out = (BandwidthOut)0x0061CBB0;
			Mine_Limit = (char *)0x0070D355;
			RenNew = (rennew)0x00672410;
			RenVecNew = (rennew)0x00672410;
			RenDelete = (rendelete)0x00672520;
			RenVecDelete = (rendelete)0x00672520;
			Get_Address = (GetAddress)0x0061D390;
			Get_Remote_Host = (GetRemoteHost)0x0061A0E0;
			ServerConnection = (char **)0x0081FF84;
			Game = (void *)0x00477370;
			Find_Team = (FindTeam)0x0041DA10;
			TallyTeamSize = (tts)0x004170D0;
			Skirmish_Game = (void *)0x00477390;
			Cnc_Game = (void *)0x004773A0;
			Single_Player_Game = (void *)0x00477380;
			Get_Safe_Data_Uint_Ref = (GetSafeDataUintRef)0x00695390;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0x00695AA0;
			Get_Safe_Data_Int_Ref = (GetSafeDataIntRef)0x00407B70;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0x00414350;
			Check_Transitions = (CheckTransitions)0x006D4E60;
			Set_Transform = (SetTransform)0x006A5790;
			Get_Transform = (GetTransform)0x006A57B0;
			BuildingGameObjList = (SList<GameObject> *)0x008561D0;
			SmartGameObjList = (SList<GameObject> *)0x008561C0;
			BaseGameObjList = (SList<GameObject> *)0x008561E0;
			FindPlayer = (Find_Player)0x004157E0;
			FindNamedDef = (Find_Named_Def)0x00526100;
			SoldierReInit = (ReInit)0x006C6CB0;
			SetMaxHealth = (void *)0x006910C0;
			SetMaxShieldStrength = (void *)0x00692980;
			Grant_Supplies = (GrantSupplies)0x00470230;
			Powerup_Grant = (PowerupGrant)0x006EFFB0;
			Get_Armor_Name = (GetArmorName)0x00687700;
			Get_Armor_Type = (GetArmorType)0x00686FF0;
			MarkOwnerDirty = (void *)0x00692FE0;
			Is_Available_For_Purchase = (IsAvailable)0x006ED5D0;
			Request_Vehicle = (RequestVehicle)0x006ED760;
			ToggleFly = (ToggleFlyMode)0x006CF520;
			Parse_Console_Input = (ConsoleInput)0x00428960;
			Output_To_Console = (void *)0x00428CD0;
			SetPlayerType = (void *)0x0040D600;
			GetPlayerCount = (void *)0x00417040;
		}
		break;
	case 2: //RH73
		{
			StringClass::m_Mutex = (CriticalSectionClass *)0x08BB5FDC;
			StringClass::ReservedMask = (unsigned int *)0x086E8410;
			StringClass::m_TempStrings = (char *)0x08BE8CE0;
			WideStringClass::m_FreeTempPtr = (wchar_t **)0x086E83E4;
			WideStringClass::m_ResTempPtr = (wchar_t **)0x086E83F4;
			WideStringClass::m_EmptyString = (wchar_t **)0x086E83E0;
			WideStringClass::m_NullChar = (wchar_t *)0x086E83DC;
			WideStringClass::m_UsedTempStringCount = (int *)0x086E83D8;
			WideStringClass::m_TempMutex = (CriticalSectionClass *)0x08BB5FD4;
			CriticalLock = (void *)0x0;
			SetLadderPoints = (void *)0x080A84B0;
			SetRung = (void *)0x080A8560;
			ServerKillConnection = (void *)0x08094DF0;
			TheFileFactory = (FileFactoryClass **)0x086E5F44;
			GameMode = (unsigned int *)0x086C4A30;
			overlap = (void *)0x083257A0;
			Collect_Building_Components = (cbc)0x080F55C4;
			StartObservers = (void *)0x08152F78;
			Create_Library_Object = (CreateLibraryObject)0x0813868C;
			FindClosestZone = (void *)0x08156204;
			InsideMe = (void *)0x081561B0;
			IsMapVTOL = (bool *)0x086C9D94;
			FindBuilding = (void *)0x080ED548;
			PowerBase = (void *)0x080ED15C;
			SetCanGenerateSoldiers = (void *)0x080ED28C;
			SetCanGenerateVehicles = (void *)0x080ED2B0;
			DestroyBase = (void *)0x080ED720;
			SetBeaconDestroyedBase = (void *)0x080ED7B8;
			EnableRadar = (void *)0x080EDABC;
			DefinitionArray = (PurchaseSettingsDefClass **)0x086CA920;
			StringClass::m_EmptyString = (char **)0x086E840C;
			StringClass::m_NullChar = (char *)0x086E8408;
			Find_Purchase_Definition = (void *)0x08146D08;
			Find_Team_Purchase_Definition = (void *)0x0817A6D4;
			Find_Definition = (FindDefinition)0x08365410;
			GetHarvester = (void *)0x080EDB54;
			Completly_Damaged = (CompletlyDamaged)0x080F064C;
			GetINI = (void *)0x080E0F40;
			ReleaseINI = (void *)0x080E101C;
			IniClassGetInt = (void *)0x083544AC;
			IniClassGetDouble = (void *)0x083547C4;
			IniClassGetBool = (void *)0x0835524C;
			IniClassGetString = (void *)0x08354DB4;
			Get_VehicleName = (GetVehicleName)0x08188FD0;
			Get_Beacon_Owner = (GetBeaconOwner)0x080F05D8;
			Get_Color_For_Team = (GetTeamColor)0x08102AA8;
			GetColor = (void *)0x080A74D4;
			Get_Obj_Color = (GetObjColor)0x0810E304;
			C4Defuse = (Defuse)0x080FA990;
			GetVehicleCount = (GetCount)0x0818C900;
			FindBase = (void *)0x080ED660;
			PrivateMessageColor = (float *)0x08B9B18C;
			PublicMessageColor = (float *)0x08B9B180;
			GDIHouseColor = (float *)0x08B9FA40;
			NodHouseColor = (float *)0x08B9FA34;
			Get_TDB_Object = (GetTDBObject)0x08346D80;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Get_Safe_Data_Float_Ref = (GetSafeDataFloatRef)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			GameType = (int *)0x086C8F78;
			IsListed = (bool *)0x086C2BA8;
			Game_Mode_Find = (GameModeFind)0x0807FC90;
			SpawnCharGDI = (char *)0x086151D5;
			SpawnCharNod = (char *)0x086151C0;
			PacketManager = (void *)0x08BB6420;
			Bandwidth_Out = (BandwidthOut)0x08370754;
			Mine_Limit = (char *)0x080FABCE;
			RenNew = (rennew)0x0804AA48;
			RenVecNew = (rennew)0x0804A7B8;
			RenDelete = (rendelete)0x0804A8F8;
			RenVecDelete = (rendelete)0x0804AA08;
			Get_Address = (GetAddress)0x08371194;
			Get_Remote_Host = (GetRemoteHost)0x0836B438;
			ServerConnection = (char **)0x086C0EDC;
			Game = (void *)0x0807CCD0;
			Find_Team = (FindTeam)0x080BFBD4;
			TallyTeamSize = (tts)0x080AA84C;
			Skirmish_Game = (void *)0x0807CCF0;
			Cnc_Game = (void *)0x0807CD08;
			Single_Player_Game = (void *)0x0807CCD8;
			Get_Safe_Data_Uint_Ref = (GetSafeDataUintRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Get_Safe_Data_Int_Ref = (GetSafeDataIntRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			Check_Transitions = (CheckTransitions)0x0817EDAC;
			Set_Transform = (SetTransform)0x0813DA90;
			Get_Transform = (GetTransform)0x0813DAAC;
			BuildingGameObjList = (SList<GameObject> *)0x08BA05FC;
			SmartGameObjList = (SList<GameObject> *)0x08BA05E4;
			BaseGameObjList = (SList<GameObject> *)0x08BA05D8;
			FindPlayer = (Find_Player)0x080A9CDC;
			FindNamedDef = (Find_Named_Def)0x0836557C;
			SoldierReInit = (ReInit)0x0815C23C;
			SetMaxHealth = (void *)0x08111B88;
			SetMaxShieldStrength = (void *)0x08111C9C;
			Grant_Supplies = (GrantSupplies)0x080C472C;
			Powerup_Grant = (PowerupGrant)0x08144268;
			Get_Armor_Name = (GetArmorName)0x0810F87C;
			Get_Armor_Type = (GetArmorType)0x0810F7B4;
			MarkOwnerDirty = (void *)0x08111D84;
			Is_Available_For_Purchase = (IsAvailable)0x0818C8C4;
			Request_Vehicle = (RequestVehicle)0x0818CAF0;
			ToggleFly = (ToggleFlyMode)0x08168740;
			Parse_Console_Input = (ConsoleInput)0x0805BBB8;
			Output_To_Console = (void *)0x0805BF40;
			SetPlayerType = (void *)0x080A7438;
			GetPlayerCount = (void *)0x080AA7F0;
		}
		break;
	case 3: //RH8
		{
			StringClass::m_Mutex = (CriticalSectionClass *)0x089D0CC0;
			StringClass::ReservedMask = (unsigned int *)0x08610F84;
			StringClass::m_TempStrings = (char *)0x089D0CE0;
			WideStringClass::m_FreeTempPtr = (wchar_t **)0x08610F58;
			WideStringClass::m_ResTempPtr = (wchar_t **)0x08610F68;
			WideStringClass::m_EmptyString = (wchar_t **)0x08610F54;
			WideStringClass::m_NullChar = (wchar_t *)0x08610F50;
			WideStringClass::m_UsedTempStringCount = (int *)0x08610F4C;
			WideStringClass::m_TempMutex = (CriticalSectionClass *)0x089CFC20;
			CriticalLock = (void *)0x0;
			SetLadderPoints = (void *)0x080A3BEE;
			SetRung = (void *)0x080A3C8E;
			ServerKillConnection = (void *)0x08090D84;
			TheFileFactory = (FileFactoryClass **)0x0860E9E4;
			GameMode = (unsigned int *)0x085EBB70;
			overlap = (void *)0x082E22F0;
			Collect_Building_Components = (cbc)0x080EA1F2;
			StartObservers = (void *)0x081410B2;
			Create_Library_Object = (CreateLibraryObject)0x081287B6;
			FindClosestZone = (void *)0x08143F90;
			InsideMe = (void *)0x08143F44;
			IsMapVTOL = (bool *)0x085F1554;
			FindBuilding = (void *)0x080E2C52;
			PowerBase = (void *)0x080E28C8;
			SetCanGenerateSoldiers = (void *)0x080E29EE;
			SetCanGenerateVehicles = (void *)0x080E2A0E;
			DestroyBase = (void *)0x080E2DEA;
			SetBeaconDestroyedBase = (void *)0x080E2E78;
			EnableRadar = (void *)0x080E319A;
			DefinitionArray = (PurchaseSettingsDefClass **)0x085F2180;
			StringClass::m_EmptyString = (char **)0x08610F80;
			StringClass::m_NullChar = (char *)0x08610F7C;
			Find_Purchase_Definition = (void *)0x08135F3A;
			Find_Team_Purchase_Definition = (void *)0x081658D6;
			Find_Definition = (FindDefinition)0x083187AE;
			GetHarvester = (void *)0x080E322C;
			Completly_Damaged = (CompletlyDamaged)0x080E5E02;
			GetINI = (void *)0x080D3D74;
			ReleaseINI = (void *)0x080D3E4C;
			IniClassGetInt = (void *)0x0830832E;
			IniClassGetDouble = (void *)0x08308634;
			IniClassGetBool = (void *)0x08308E94;
			IniClassGetString = (void *)0x08308A40;
			Get_VehicleName = (GetVehicleName)0x08172B74;
			Get_Beacon_Owner = (GetBeaconOwner)0x080E5D98;
			Get_Color_For_Team = (GetTeamColor)0x080F5EB8;
			GetColor = (void *)0x080A2EE6;
			Get_Obj_Color = (GetObjColor)0x081006FC;
			C4Defuse = (Defuse)0x080EE1EA;
			GetVehicleCount = (GetCount)0x08175FBE;
			FindBase = (void *)0x080E2D3A;
			PrivateMessageColor = (float *)0x089A36F4;
			PublicMessageColor = (float *)0x089A36E8;
			GDIHouseColor = (float *)0x089A8398;
			NodHouseColor = (float *)0x089A838C;
			Get_TDB_Object = (GetTDBObject)0x082FBF90;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Get_Safe_Data_Float_Ref = (GetSafeDataFloatRef)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			GameType = (int *)0x085F0670;
			IsListed = (bool *)0x085E9AB8;
			Game_Mode_Find = (GameModeFind)0x0807F36A;
			SpawnCharGDI = (char *)0x084FB353;
			SpawnCharNod = (char *)0x084FB33E;
			PacketManager = (void *)0x089D20E0;
			Bandwidth_Out = (BandwidthOut)0x083238EA;
			Mine_Limit = (char *)0x080EE422;
			RenNew = (rennew)0x08053B04;
			RenVecNew = (rennew)0x08053A14;
			RenDelete = (rendelete)0x08053434;
			RenVecDelete = (rendelete)0x08053A54;
			Get_Address = (GetAddress)0x08324566;
			Get_Remote_Host = (GetRemoteHost)0x0831E694;
			ServerConnection = (char **)0x085E7C2C;
			Game = (void *)0x0807C7A8;
			Find_Team = (FindTeam)0x080B82C4;
			TallyTeamSize = (tts)0x080A5AB6;
			Skirmish_Game = (void *)0x0807C7C2;
			Cnc_Game = (void *)0x0807C7D6;
			Single_Player_Game = (void *)0x0807C7AE;
			Get_Safe_Data_Uint_Ref = (GetSafeDataUintRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Get_Safe_Data_Int_Ref = (GetSafeDataIntRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			Check_Transitions = (CheckTransitions)0x08169ADC;
			Set_Transform = (SetTransform)0x0812DA3A;
			Get_Transform = (GetTransform)0x0812DA56;
			BuildingGameObjList = (SList<GameObject> *)0x089A9090;
			SmartGameObjList = (SList<GameObject> *)0x089A9078;
			BaseGameObjList = (SList<GameObject> *)0x089A906C;
			FindPlayer = (Find_Player)0x080A510A;
			FindNamedDef = (Find_Named_Def)0x0831890A;
			SoldierReInit = (ReInit)0x0814A676;
			SetMaxHealth = (void *)0x08103C18;
			SetMaxShieldStrength = (void *)0x08103D2E;
			Grant_Supplies = (GrantSupplies)0x080BC8D8;
			Powerup_Grant = (PowerupGrant)0x081332C6;
			Get_Armor_Name = (GetArmorName)0x08101AB8;
			Get_Armor_Type = (GetArmorType)0x081019FC;
			MarkOwnerDirty = (void *)0x08103E20;
			Is_Available_For_Purchase = (IsAvailable)0x008175F7A;
			Request_Vehicle = (RequestVehicle)0x08176184;
			ToggleFly = (ToggleFlyMode)0x08155762;
			Parse_Console_Input = (ConsoleInput)0x08063F56;
			Output_To_Console = (void *)0x080642B2;
			SetPlayerType = (void *)0x080A2E50;
			GetPlayerCount = (void *)0x080A5A62;
		}
		break;
	case 4: //leveledit
		{
			StringClass::m_Mutex = (CriticalSectionClass *)0;
			StringClass::ReservedMask = (unsigned int *)0;
			StringClass::m_TempStrings = (char *)0;
			WideStringClass::m_FreeTempPtr = (wchar_t **)0;
			WideStringClass::m_ResTempPtr = (wchar_t **)0;
			WideStringClass::m_EmptyString = (wchar_t **)0;
			WideStringClass::m_NullChar = (wchar_t *)0;
			WideStringClass::m_UsedTempStringCount = (int *)0;
			WideStringClass::m_TempMutex = (CriticalSectionClass *)0;
			CriticalLock = (void *)0;
			SetLadderPoints = (void *)0;
			SetRung = (void *)0;
			ServerKillConnection = (void *)0;
			TheFileFactory = (FileFactoryClass **)0;
			GameMode = (unsigned int *)0;
			overlap = (void *)0;
			Collect_Building_Components = (cbc)0;
			StartObservers = (void *)0;
			Create_Library_Object = (CreateLibraryObject)0;
			FindClosestZone = (void *)0;
			InsideMe = (void *)0;
			IsMapVTOL = (bool *)0;
			FindBuilding = (void *)0;
			PowerBase = (void *)0;
			SetCanGenerateSoldiers = (void *)0;
			SetCanGenerateVehicles = (void *)0;
			DestroyBase = (void *)0;
			SetBeaconDestroyedBase = (void *)0;
			EnableRadar = (void *)0;
			DefinitionArray = (PurchaseSettingsDefClass **)0;
			StringClass::m_EmptyString = (char **)0;
			StringClass::m_NullChar = (char *)0;
			Find_Purchase_Definition = (void *)0;
			Find_Team_Purchase_Definition = (void *)0;
			Find_Definition = (FindDefinition)0;
			GetHarvester = (void *)0;
			Completly_Damaged = (CompletlyDamaged)0;
			GetINI = (void *)0;
			ReleaseINI = (void *)0;
			IniClassGetInt = (void *)0;
			IniClassGetDouble = (void *)0;
			IniClassGetBool = (void *)0;
			IniClassGetString = (void *)0;
			Get_VehicleName = (GetVehicleName)0;
			Get_Beacon_Owner = (GetBeaconOwner)0;
			Get_Color_For_Team = (GetTeamColor)0;
			GetColor = (void *)0;
			Get_Obj_Color = (GetObjColor)0;
			C4Defuse = (Defuse)0;
			GetVehicleCount = (GetCount)0;
			FindBase = (void *)0;
			PrivateMessageColor = (float *)0;
			PublicMessageColor = (float *)0;
			GDIHouseColor = (float *)0;
			NodHouseColor = (float *)0;
			Get_TDB_Object = (GetTDBObject)0;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Get_Safe_Data_Float_Ref = (GetSafeDataFloatRef)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			GameType = (int *)0;
			IsListed = (bool *)0;
			Game_Mode_Find = (GameModeFind)0;
			SpawnCharGDI = (char *)0;
			SpawnCharNod = (char *)0;
			PacketManager = (void *)0;
			Bandwidth_Out = (BandwidthOut)0;
			Mine_Limit = (char *)0;
			RenNew = (rennew)0x007A783D;
			RenVecNew = (rennew)0x007A783D;
			RenDelete = (rendelete)0x007A7866;
			RenVecDelete = (rendelete)0x007A7866;
			Get_Address = (GetAddress)0;
			Get_Remote_Host = (GetRemoteHost)0;
			ServerConnection = (char **)0;
			Game = (void *)0;
			Find_Team = (FindTeam)0;
			TallyTeamSize = (tts)0;
			Skirmish_Game = (void *)0;
			Cnc_Game = (void *)0;
			Single_Player_Game = (void *)0;
			Get_Safe_Data_Uint_Ref = (GetSafeDataUintRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Get_Safe_Data_Int_Ref = (GetSafeDataIntRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			Check_Transitions = (CheckTransitions)0;
			Set_Transform = (SetTransform)0;
			Get_Transform = (GetTransform)0;
			BuildingGameObjList = (SList<GameObject> *)0;
			SmartGameObjList = (SList<GameObject> *)0;
			BaseGameObjList = (SList<GameObject> *)0;
			FindPlayer = (Find_Player)0;
			FindNamedDef = (Find_Named_Def)0;
			SoldierReInit = (ReInit)0;
			SetMaxHealth = (void *)0;
			SetMaxShieldStrength = (void *)0;
			Grant_Supplies = (GrantSupplies)0;
			Powerup_Grant = (PowerupGrant)0;
			Get_Armor_Name = (GetArmorName)0;
			Get_Armor_Type = (GetArmorType)0;
			MarkOwnerDirty = (void *)0;
			Is_Available_For_Purchase = (IsAvailable)0;
			Request_Vehicle = (RequestVehicle)0;
			ToggleFly = (ToggleFlyMode)0;
			Parse_Console_Input = (ConsoleInput)0;
			Output_To_Console = (void *)0;
			SetPlayerType = (void *)0;
			GetPlayerCount = (void *)0;
		}
		break;
	}
}

GameObject *As_ScriptableGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_ScriptableGameObj();
}

GameObject *As_PhysicalGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_PhysicalGameObj();
}

GameObject *As_CinematicGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x98]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xC0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0xA0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_VehicleGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_VehicleGameObj();
}

GameObject *As_SmartGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_SmartGameObj();
}

GameObject *As_DamageableGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_DamageableGameObj();
}

GameObject *As_SoldierGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_SoldierGameObj();
}

GameObject *As_ScriptZoneGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
}

GameObject *As_BuildingGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return (GameObject *)((ScriptableGameObj *)obj)->As_BuildingGameObj();
}

const char *Get_Model(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "DUMMY";
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return "DUMMY";
	}
#ifdef WIN32
	_asm {
		mov eax,o
		mov ebx,[eax+0x774]
		mov ecx,[ebx+0x3C]
		mov eax,[ecx]
		mov ebx,[eax+0x10]
		call ebx
	}
#else
	o+=0x774;
	char *p = (char *)*(unsigned int *)o;
	p+=0x54;
	char *r = (char *)*(unsigned int *)p;
#ifndef RH8
	r += 0x1C;
#endif
	char *v = (char *)*(unsigned int *)r;
#ifndef RH8
	r -= 0x1C;
	v += 4;
#endif
	v += 0x14;
	Get_Name *n = (Get_Name*)v;
	Get_Name gn = (Get_Name)*n;
	return gn(r);
#endif
}

int Get_Object_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return 0;
	}
	return o->PlayerType;
}

void Set_Object_Type(GameObject *obj,int type)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->PlayerType = type;
}

DefinitionClass *Get_Definition(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return ((ScriptableGameObj *)obj)->definition;
}

DefinitionClass *Get_Phys_Definition(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return 0;
	}
	o+=0x774;
	char *p = (char *)*(unsigned int *)o;
#ifdef WIN32
	p += 0x50;
#else
	p += 0x68;
#endif
	return (DefinitionClass *)*(unsigned int *)p;
}

void Soldier_Re_Init(GameObject *obj,DefinitionClass *def)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,obj
		mov eax,def
		mov ebx,SoldierReInit
		push eax
		call ebx
	}
#else
	SoldierReInit(obj,def);
#endif
}

DefinitionClass *Find_Named_Definition(const char *name)
{
	return FindNamedDef(name,1);
}

void Post_Re_Init(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	((ScriptableGameObj *)obj)->Post_Re_Init();
}

bool Change_Character(GameObject *obj,const char *Preset_Name)
{
	if (!Commands->Get_ID(obj) || !obj || Get_Vehicle(obj))
	{
		return false;
	}
	DefinitionClass *def = Find_Named_Definition(Preset_Name);
	if (!def)
	{
		return false;
	}
	if (def->Get_Class_ID() != 0x3001)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return false;
	}
	Soldier_Re_Init(o,def);
	Post_Re_Init(o);
	return true;
}

const char *WideCharToChar(const wchar_t *wcs)
{
	if (!wcs)
	{
		char *c = new char[2];
		c[0] = 0;
		c[1] = 0;
		return c;
	}
	int length = wcslen(wcs);
	char *text = new char[length+1];
	wcstombs(text,wcs,length+1);
	return text;
}

const char *Get_Player_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return newstr("None");
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return newstr("None");
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return newstr("None");
	}
	return WideCharToChar(x->PlayerName);
}

const char *Get_Player_Name_By_ID(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return WideCharToChar(x->PlayerName);
}

void Change_Team_By_ID(int PlayerID,int Team)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Player_Type(Team);
	GameObject *obj = Get_GameObj(PlayerID);
	Commands->Destroy_Object(obj);
}

void Change_Team(GameObject *obj,int Team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return;
	}
	char *c = (char *)o;
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return;
	}
	x->Set_Player_Type(Team);
	Commands->Destroy_Object(obj);
}

long Get_Player_ID(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return -1;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return -1;
	}
	char *c = (char *)o;
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return -1;
	}
	return x->PlayerId;
}

GameObject *Get_GameObj(int PlayerID) {
	cPlayer *x = FindPlayer(PlayerID);
	if (x) {
		if (x->Owner.Reference) {
			return (GameObject *)x->Owner.Reference->obj;
		}
	}
	return 0;
}

GameObject *Find_Building_By_Class_ID(int Team,unsigned long Class_ID)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == Class_ID)
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Building_By_Team(int Team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Building_By_Name(int Team,const char *Preset_Name)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),Preset_Name))
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

void Kill_All_Buildings_By_Team(int Team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				Commands->Apply_Damage(o,10000,"Explosive",0);
			}
		}
		x = x->NodeNext;
	}
}

void Damage_All_Buildings_By_Team(int Team,float Damage,const char *Warhead,GameObject *Damager)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) || (Team == 2))
			{
				Commands->Apply_Damage(o,Damage,Warhead,Damager);
			}
		}
		x = x->NodeNext;
	}
}

void Repair_All_Buildings_By_Team(int Team,int ConstructionYardID,float Health)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) && (Commands->Get_ID(o) != ConstructionYardID))
			{
				float amount = Commands->Get_Health(o);
				if (amount>0)
				{
					Commands->Set_Health(o,(amount+Health));
				}
			}
		}
		x = x->NodeNext;
	}
}

void Repair_All_Static_Vehicles_By_Team(int Team,int Message)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_VehicleGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team && Is_DecorationPhys(o))
			{
				Commands->Send_Custom_Event(o,o,Message,0,0);
			}
		}
		x = x->NodeNext;
	}
}

GameObject *Find_Smart_Object_By_Team(int Team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Object_By_Team(int Team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if (Get_Object_Type(o) == Team)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Non_Player_Object_By_Team(int Team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) && (!Commands->Is_A_Star(o)))
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Object_By_Preset(int Team,const char *Preset_Name)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),Preset_Name))
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Power_Plant(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD003);
}

GameObject *Find_Refinery(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD002);
}

GameObject *Find_Repair_Bay(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD009);
}

GameObject *Find_Soldier_Factory(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD004);
}

GameObject *Find_Airstrip(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD006);
}

GameObject *Find_War_Factory(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD007);
}

GameObject *Find_Vehicle_Factory(int Team)
{
	GameObject *o = Find_Airstrip(Team);
	if (o)
	{
		return o;
	}
	return Find_War_Factory(Team);
}

GameObject *Find_Com_Center(int Team)
{
	return Find_Building_By_Class_ID(Team,0xD008);
}

bool Is_Building(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_BuildingGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Soldier(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_SoldierGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Vehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_VehicleGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Cinematic(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_CinematicGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_ScriptZone(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_ScriptZoneGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_TrackedVehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900C)
	{
		return false;
	}
	return true;
}

bool Is_VTOLVehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900D)
	{
		return false;
	}
	return true;
}

bool Is_WheeledVehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9006)
	{
		return false;
	}
	return true;
}

bool Is_Motorcycle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9002)
	{
		return false;
	}
	return true;
}

bool Is_Door(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9080)
	{
		return false;
	}
	return true;
}

bool Is_Elevator(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9081)
	{
		return false;
	}
	return true;
}

bool Is_DamageableStaticPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9082)
	{
		return false;
	}
	return true;
}

bool Is_AccessablePhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9010)
	{
		return false;
	}
	return true;
}

bool Is_DecorationPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9000)
	{
		return false;
	}
	return true;
}

bool Is_HumanPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9001)
	{
		return false;
	}
	return true;
}

bool Is_MotorVehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9003)
	{
		return false;
	}
	return true;
}

bool Is_Phys3(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9004)
	{
		return false;
	}
	return true;
}

bool Is_RigidBody(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9005)
	{
		return false;
	}
	return true;
}

bool Is_ShakeableStatricPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900F)
	{
		return false;
	}
	return true;
}

bool Is_StaticAnimPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9008)
	{
		return false;
	}
	return true;
}

bool Is_StaticPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9007)
	{
		return false;
	}
	return true;
}

bool Is_TimedDecorationPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900A)
	{
		return false;
	}
	return true;
}

bool Is_VehiclePhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900B)
	{
		return false;
	}
	return true;
}

bool Is_DynamicAnimPhys(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x900E)
	{
		return false;
	}
	return true;
}

bool Is_BuildingAggregate(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9083)
	{
		return false;
	}
	return true;
}

bool Is_Projectile(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return false;
	}
	int Class_ID = Get_Phys_Definition(o)->Get_Class_ID();
	if (Class_ID != 0x9009)
	{
		return false;
	}
	return true;
}

void Set_Max_Health(GameObject *obj,float health)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->Defence.Set_Max_Health(health);
	Commands->Set_Health(obj,health);
}

void Set_Max_Shield_Strength(GameObject *obj,float shieldstrength)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->Defence.Set_Max_Shield_Strength(shieldstrength);
	Commands->Set_Shield_Strength(obj,shieldstrength);
}

GameObject *Find_First_Player(int Team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_SoldierGameObj(o))
		{
			if (Commands->Is_A_Star(o))
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

//doesnt work for CinematicGameObjs
float Get_Animation_Frame(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return 0;
	}
	unsigned char *c = o+0x778;
	unsigned char *x = *(unsigned char **)c;
	float a = (float)*(float *)(x+0x14);
	return a;
}

void Grant_Refill(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		Grant_Supplies(obj);
	}
}

void Grant_Powerup(GameObject *obj,const char *Preset_Name)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SmartGameObj(obj);
	if (o)
	{
		DefinitionClass *def = Find_Named_Definition(Preset_Name);
#ifdef WIN32
		_asm {
			mov ecx,def
			mov eax,o
			mov ebx,Powerup_Grant
			push 1
			push 0
			push eax
			call ebx
		}
#else
		Powerup_Grant(def,o,0,true);
#endif
	}
}

GameObject *Get_Vehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		char *c = (char *)o;
		c += 0x98C;
		unsigned long *l = (unsigned long *)c;
		GameObject *vehicle = (GameObject *)*l;
		if (vehicle)
		{
			GameObject *v = As_VehicleGameObj(vehicle);
			return v;
		}
		return 0;
	}
	return 0;
}

const char *Get_Shield_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "";
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return "";
	}
	return Get_Armor_Name(o->Defence.ShieldType.Get());
}

const char *Get_Skin(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "";
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return "";
	}
	return Get_Armor_Name(o->Defence.Skin.Get());
}

void Set_Skin(GameObject *obj,const char *Skintype)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	unsigned int skin = Get_Armor_Type(Skintype);
	o->Defence.Skin.Set(skin);
	o->Defence.Mark_Owner_Dirty();
}

void Create_Vehicle(const char *Preset_Name,float Delay,GameObject *Owner,int Team)
{
	GameObject *o = 0;
	if (Owner)
	{
		o = As_SoldierGameObj(Owner);
	}
	DefinitionClass *def = Find_Named_Definition(Preset_Name);
	if (def)
	{
		if (!Get_Vehicle(o))
		{
			GameObject *factory = Find_Vehicle_Factory(Team);
			if (factory)
			{
				bool IsAvail;
#ifdef WIN32
				_asm {
					mov ecx,factory
					mov ebx,Is_Available_For_Purchase
					call ebx
					mov IsAvail,al;
				}
#else
				IsAvail = Is_Available_For_Purchase(factory);
#endif
				if (IsAvail)
				{
					unsigned int ID = def->Get_ID();
#ifdef WIN32
					_asm {
						mov ecx,factory
						mov ebx,Request_Vehicle
						mov eax,o
						push eax
						mov eax,Delay
						push eax
						mov eax,ID
						push eax
						call ebx
					}
#else
					Request_Vehicle(factory,ID,Delay,o);
#endif
				}
			}
		}
	}
}

void Toggle_Fly_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
#ifdef WIN32
		_asm {
			mov ecx,o
			mov ebx,ToggleFly
			call ebx
		}
#else
		ToggleFly(o);
#endif
		Commands->Enable_Collisions(o);
	}
}

GameObject *As_PowerupGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x88]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xB0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x90;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_C4GameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x8C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xB4;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x94;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_BeaconGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x90]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xB8;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x98;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_ArmedGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x94]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xBC;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x9C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_SimpleGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_PhysicalGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x9C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xC4;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0xA4;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_PowerPlantGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x70]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x94;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x78;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_SoldierFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x74]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x98;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x7C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_VehicleFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x78]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0x9C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x80;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_AirstripGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x7C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x84;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_WarFactoryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x80]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA4;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x88;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_RefineryGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x84]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xA8;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x8C;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_ComCenterGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x88]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xAC;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x90;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

GameObject *As_RepairBayGameObj(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o2 = As_BuildingGameObj(obj);
	if (!o2)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o2
		mov ebx,[ecx]
		mov eax,[ebx+0x8C]
		call eax
	}
#elif defined RH8
	char *c = (char *)*(unsigned int *)obj;
	c += 0xB0;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#else
	GameObject *o = obj + 4;
	char *c = (char *)*(unsigned int *)o;
	c += 0x94;
	ago *t = (ago *)c;
	ago agox = *t;
	return agox(obj);
#endif
}

bool Is_Powerup(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_PowerupGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_C4(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_C4GameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Scriptable(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_ScriptableGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Beacon(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_BeaconGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Armed(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_ArmedGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Simple(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_SimpleGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_PowerPlant(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_PowerPlantGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_SoldierFactory(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_SoldierFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_VehicleFactory(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_VehicleFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Airstrip(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_AirstripGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_WarFactory(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_WarFactoryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_Refinery(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_RefineryGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_ComCenter(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_ComCenterGameObj(obj))
	{
		return true;
	}
	return false;
}

bool Is_RepairBay(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (As_RepairBayGameObj(obj))
	{
		return true;
	}
	return false;
}

void Damage_All_Objects_Area(float Damage,const char *Warhead,const Vector3 &Position,float Distance,GameObject *Host,GameObject *Damager) 
{
	if (!Commands->Get_ID(Host) || !Host)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj)) 
		{
			Vector3 ObjPosition = Commands->Get_Position(obj);
			Vector3 TestPosition = Position;
			ObjPosition.Z = 0;
			TestPosition.Z = 0;
			if ((Commands->Get_Distance(ObjPosition,TestPosition) <= Distance) && (Commands->Get_ID(obj) != Commands->Get_ID(Host)))
			{
				Commands->Apply_Damage(obj,Damage,Warhead,Damager);
			}
		}
		x = x->NodeNext;
	}
}

void Damage_All_Vehicles_Area(float Damage,const char *Warhead,const Vector3 &Position,float Distance,GameObject *Host,GameObject *Damager)
{
	if (!Commands->Get_ID(Host) || !Host)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = As_VehicleGameObj((GameObject *)x->NodeData);
		if (obj && As_ScriptableGameObj(obj)) 
		{
			Vector3 ObjPosition = Commands->Get_Position(obj);
			Vector3 TestPosition = Position;
			ObjPosition.Z = 0;
			TestPosition.Z = 0;
			if ((Commands->Get_Distance(ObjPosition,TestPosition) <= Distance) && (Commands->Get_ID(obj) != Commands->Get_ID(Host)))
			{
				Commands->Apply_Damage(obj,Damage,Warhead,Damager);
			}
		}
		x = x->NodeNext;
	}
}

int Get_Team_Player_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o && Get_Object_Type(o) == Team)
		{
			Total ++;
		}
		x = x->NodeNext;
	}
	return Total;
}

const char *Get_Building_Type(GameObject *obj)
{
	if (Is_PowerPlant(obj))
	{
		return "Is_PowerPlant";
	}
	else if (Is_SoldierFactory(obj))
	{
		return "Is_SoldierFactory";
	}
	else if (Is_VehicleFactory(obj))
	{
		if (Is_Airstrip(obj))
		{
			return "Is_Airstrip";
		}
		else if (Is_WarFactory(obj))
		{
			return "Is_WarFactory";
		}
	}
	else if (Is_Refinery(obj))
	{
		return "Is_Refinery";
	}
	else if (Is_ComCenter(obj))
	{
		return "Is_ComCenter";
	}
	else if (Is_RepairBay(obj))
	{
		return "Is_RepairBay";
	}
	else
	{
		return "(null)";
	}
	return "(null)";
}

const char *Get_Physics(GameObject *obj)
{
	if (Is_Door(obj)) return "Is_Door";
	else if (Is_Elevator(obj)) return "Is_Elevator";
	else if (Is_DamageableStaticPhys(obj)) return "Is_DamageableStaticPhys";
	else if (Is_AccessablePhys(obj)) return "Is_AccessablePhys";
	else if (Is_DecorationPhys(obj)) return "Is_DecorationPhys";
	else if (Is_HumanPhys(obj)) return "Is_HumanPhys";
	else if (Is_MotorVehicle(obj)) return "Is_MotorVehicle";
	else if (Is_Phys3(obj)) return "Is_Phys3";
	else if (Is_RigidBody(obj)) return "Is_RigidBody";
	else if (Is_ShakeableStatricPhys(obj)) return "Is_ShakeableStatricPhys";
	else if (Is_StaticAnimPhys(obj)) return "Is_StaticAnimPhys";
	else if (Is_StaticPhys(obj)) return "Is_StaticPhys";
	else if (Is_TimedDecorationPhys(obj)) return "Is_TimedDecorationPhys";
	else if (Is_VehiclePhys(obj)) return "Is_VehiclePhys";
	else if (Is_DynamicAnimPhys(obj)) return "Is_DynamicAnimPhys";
	else if (Is_BuildingAggregate(obj)) return "Is_BuildingAggregate";
	else if (Is_Projectile(obj)) return "Is_Projectile";
	else return "(null)";
}

void Disarm_Nearest_Beacon(GameObject *Host,int Team,bool Nearest)
{
	if (!Commands->Get_ID(Host) || !Host)
	{
		return;
	}
	Vector3 HostPos = Commands->Get_Position(Host);
	HostPos.Z = 0;
	float NearestDistanceFound = 5000.0f;
	GameObject *ClosestBeacon = Commands->Create_Object("Invisible_Object",HostPos);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				if (Nearest)
				{
					Vector3 BeaconPos = Commands->Get_Position(o);
					BeaconPos.Z = 0;
					if (Commands->Get_Distance(BeaconPos,HostPos) < NearestDistanceFound)
					{
						NearestDistanceFound = Commands->Get_Distance(BeaconPos,HostPos);
						ClosestBeacon = o;
					}
				}
				else
				{
					Disarm_Beacon(o);
				}
			}
			else if (Get_Object_Type(o) == Team)
			{
				if (Nearest)
				{
					Vector3 BeaconPos = Commands->Get_Position(o);
					BeaconPos.Z = 0;
					if (Commands->Get_Distance(BeaconPos,HostPos) < NearestDistanceFound)
					{
						NearestDistanceFound = Commands->Get_Distance(BeaconPos,HostPos);
						ClosestBeacon = o;
					}
				}
				else 
				{
					Disarm_Beacon(o);
				}
			}
		}
		x = x->NodeNext;
	}
	if (Nearest && ClosestBeacon && As_BeaconGameObj(ClosestBeacon))
	{
		Disarm_Beacon(ClosestBeacon);
	}
}

bool Change_Player_Team(GameObject *obj,bool Retain_Score,bool Retain_Money,bool Show_Host_Message)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (!Commands->Is_A_Star(obj))
	{
		return false;
	}
	Disarm_All_C4(Get_Player_ID(obj));
	float Score = Commands->Get_Points(obj);
	float Credits = Commands->Get_Money(obj);
	Commands->Give_Points(obj,(Score*-1),false);
	if (Score < 0)
	{
		Commands->Give_Money(obj,Score,false);
	}
	Commands->Give_Money(obj,(Credits*-1),false);
	if (!Commands->Get_Player_Type(obj))
	{
		Change_Team(obj,1);
	}
	else if (Commands->Get_Player_Type(obj) == 1)
	{
		Change_Team(obj,0);
	}
	if (Retain_Score)
	{
		Commands->Give_Points(obj,Score,false);
		if (Score > 0)
		{
			Commands->Give_Money(obj,(Score*-1),false);
		}
	}
	if (Retain_Money)
	{
		Commands->Give_Money(obj,Credits,false);
	}
	if (Show_Host_Message)
	{
		char outputmsg[100];
		const char *name = Get_Player_Name(obj);
		sprintf(outputmsg,"msg %s switched teams",name);
		delete name;
		Console_Input(outputmsg);
	}
	return true;
}

void Ranged_Damage_To_Buildings(float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				float health = Commands->Get_Health(o);
				if (health > 0)
				{
					Vector3 pos1 = Commands->Get_Position(o);
					Vector3 pos2 = Location;

					float Distance = Commands->Get_Distance(pos1,pos2);

					if (Distance <= DamageRadius)
					{
						Commands->Apply_Damage(o,Damage,Warhead,Damager);
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Ranged_Scale_Damage_To_Buildings(float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		float Ratio = Damage/DamageRadius;

		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				float health = Commands->Get_Health(o);
				if (health > 0)
				{
					Vector3 pos1 = Commands->Get_Position(o);
					Vector3 pos2 = Location;

					float Distance = Commands->Get_Distance(pos1,pos2);

					if (Distance <= DamageRadius)
					{
						float scaledamage = (Damage - (Distance*(Ratio)));
						Commands->Apply_Damage(o,scaledamage,Warhead,Damager);
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Ranged_Percentage_Damage_To_Buildings(float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				float health = Commands->Get_Health(o);
				if (health > 0)
				{
					Vector3 pos1 = Commands->Get_Position(o);
					Vector3 pos2 = Location;

					float Distance = Commands->Get_Distance(pos1,pos2);

					if (Distance <= DamageRadius)
					{
						float Max_Health = Commands->Get_Max_Health(o);
						float Damage = Max_Health*Percentage;
						Commands->Apply_Damage(o,Damage,Warhead,Damager);
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Ranged_Damage_To_Buildings_Team(int Team,float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					float health = Commands->Get_Health(o);
					if (health > 0)
					{
						Vector3 pos1 = Commands->Get_Position(o);
						Vector3 pos2 = Location;
						float Distance = Commands->Get_Distance(pos1,pos2);
						if (Distance <= DamageRadius)
						{
							Commands->Apply_Damage(o,Damage,Warhead,Damager);
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Ranged_Scale_Damage_To_Buildings_Team(int Team,float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		float Ratio = Damage/DamageRadius;

		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					float health = Commands->Get_Health(o);
					if (health > 0)
					{
						Vector3 pos1 = Commands->Get_Position(o);
						Vector3 pos2 = Location;
						float Distance = Commands->Get_Distance(pos1,pos2);
						if (Distance <= DamageRadius)
						{
							float scaledamage = (Damage - (Distance*(Ratio)));
							Commands->Apply_Damage(o,scaledamage,Warhead,Damager);
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Ranged_Percentage_Damage_To_Buildings_Team(int Team,float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		GenericSLNode *x = BuildingGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
			if (o)
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					float health = Commands->Get_Health(o);
					if (health > 0)
					{
						Vector3 pos1 = Commands->Get_Position(o);
						Vector3 pos2 = Location;
						float Distance = Commands->Get_Distance(pos1,pos2);
						if (Distance <= DamageRadius)
						{
							float Max_Health = Commands->Get_Max_Health(o);
							float Damage = Max_Health*Percentage;
							Commands->Apply_Damage(o,Damage,Warhead,Damager);
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Send_Custom_To_Team_Buildings(int Team,GameObject *sender,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team)
			{
				int ReceiverID = Commands->Get_ID(o);
				int SenderID = Commands->Get_ID(sender);
				if (SenderID != ReceiverID)
				{
					Commands->Send_Custom_Event(sender,o,message,param,delay);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_To_Team_Preset(int Team,const char *PresetName,GameObject *sender,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if (Get_Object_Type(o) == Team)
			{
				if (!_stricmp(Commands->Get_Preset_Name(o),PresetName))
				{
					Commands->Send_Custom_Event(sender,o,message,param,delay);
				}
			}
		}
		x = x->NodeNext;
	}
}

#ifndef BHS
bool Can_Team_Build_Vehicle(int Team)
{
	if (Is_Currently_Building(Team))
	{
		return false;
	}
	GameObject *factory = Find_Vehicle_Factory(Team);
	if (factory && !Is_Building_Dead(factory))
	{
		bool IsAvail;
#ifdef WIN32
		_asm {
			mov ecx,factory
			mov ebx,Is_Available_For_Purchase
			call ebx
			mov IsAvail,al;
		}
#else
		IsAvail = Is_Available_For_Purchase(factory);
#endif
		return IsAvail;
	}
	return true;
}

void Send_Message_With_Team_Color(int Team,const char *Msg)
{
	unsigned int Red = 0,Blue = 0,Green = 0;
	Get_Team_Color(Team,&Red,&Green,&Blue);
	Send_Message(Red,Green,Blue,Msg);
}

void Send_Message_With_Obj_Color(GameObject *obj,const char *Msg)
{
	unsigned int Red = 0,Blue = 0,Green = 0;
	Get_Object_Color(obj,&Red,&Green,&Blue);
	Send_Message(Red,Green,Blue,Msg);
}

void Send_Message_Team(int team,unsigned int red,unsigned int green,unsigned int blue,const char *msg)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Send_Message_Player(o,red,green,blue,msg);
			}
		}
		x = x->NodeNext;
	}
}

void Set_Obj_Radar_Blip_Shape_Team(int Team,GameObject *obj,int shape)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) || (Team == 2))
			{
				Set_Obj_Radar_Blip_Shape_Player(o,obj,shape);
			}
		}
		x = x->NodeNext;
	}
}

void Set_Obj_Radar_Blip_Color_Team(int Team,GameObject *obj,int color)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) || (Team == 2))
			{
				Set_Obj_Radar_Blip_Color_Player(o,obj,color);
			}
		}
		x = x->NodeNext;
	}
}

void Set_Occupants_Fade(GameObject *obj,float red,float green,float blue,float opacity)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	if (!As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			Set_Screen_Fade_Color_Player(occupants[i],red,green,blue,0);
			Set_Screen_Fade_Opacity_Player(occupants[i],opacity,0);
		}
	}
}

void Enable_Team_Radar(int Team,bool Enable)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) || (Team == 2))
			{
				Enable_Radar_Player(o,Enable);
			}
		}
		x = x->NodeNext;
	}
}

void Create_Sound_Team(const char *soundname,const Vector3 & position,GameObject *obj,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Create_Sound_Player(o,soundname,position,obj);
			}
		}
		x = x->NodeNext;
	}
}

void Create_2D_Sound_Team(const char *soundname,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Create_2D_Sound_Player(o,soundname);
			}
		}
		x = x->NodeNext;
	}
}

void Create_2D_WAV_Sound_Team(const char *soundname,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Create_2D_WAV_Sound_Player(o,soundname);
			}
		}
		x = x->NodeNext;
	}
}

void Create_3D_WAV_Sound_At_Bone_Team(const char *soundname,GameObject *obj,const char *bonename,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Create_3D_WAV_Sound_At_Bone_Player(o,soundname,obj,bonename);
			}
		}
		x = x->NodeNext;
	}
}

void Create_3D_Sound_At_Bone_Team(const char *soundname,GameObject *obj,const char *bonename,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Create_3D_Sound_At_Bone_Player(o,soundname,obj,bonename);
			}
		}
		x = x->NodeNext;
	}
}

void Set_Display_Color_Team(unsigned char red,unsigned char green,unsigned char blue,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Set_Display_Color_Player(o,red,green,blue);
			}
		}
		x = x->NodeNext;
	}
}

void Display_Text_Team(int strnum,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Display_Text_Player(o,strnum);
			}
		}
		x = x->NodeNext;
	}
}

void Display_Int_Team(int num,const char *msg,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Display_Int_Player(o,num,msg);
			}
		}
		x = x->NodeNext;
	}
}

void Display_Float_Team(float num,const char *msg,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SmartGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Display_Float_Player(o,num,msg);
			}
		}
		x = x->NodeNext;
	}
}

void Remove_Script(GameObject *obj,const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			((ScriptImpClass*)(*observers)[i])->Destroy_Script();
		}
	}
}

void Remove_Duplicate_Script(GameObject *obj, const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	bool Found = false;
	for (int i = 0;i < observers->Count();i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			if (!Found)
			{
				Found = true;
			}
			else
			{
				((ScriptImpClass*)(*observers)[i])->Destroy_Script();
			}
		}
	}
}

void Remove_Script_Preset(const char *script,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Remove_Script(o,script);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Remove_Script_Type(const char *script,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Remove_Script(o,script);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Remove_All_Scripts(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		((ScriptImpClass*)(*observers)[i])->Destroy_Script();
	}
}
#endif

int Get_Vehicle_Occupant_Count(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int count = 0;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			count++;
		}
	}
	return count;
}

GameObject *Get_Vehicle_Occupant(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (seat >= occupants.Length())
	{
		return 0;
	}
	return occupants[seat];
}

GameObject *Get_Vehicle_Driver(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (occupants.Length() <= 0)
	{
		return 0;
	}
	return occupants[0];
}

GameObject *Get_Vehicle_Gunner_Pos(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (occupants.Length() <= 1)
	{
		return 0;
	}
	return occupants[1];
}

GameObject *Get_Vehicle_Gunner(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	GameObject *o = Get_Vehicle_Gunner_Pos(obj);
	if ((!o) || (*(bool *)(obj+0x994)))
	{
		o = Get_Vehicle_Driver(obj);
	}
	return o;
}

void Attach_Script_Preset(const char *script,const char *params,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Commands->Attach_Script(o,script,params);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Type(const char *script,const char *params,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Commands->Attach_Script(o,script,params);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Copy_Transform(GameObject *in,GameObject *out)
{
	if (!Commands->Get_ID(in) || !in || !Commands->Get_ID(out) || !out)
	{
		return;
	}
	GameObject *i2 = As_PhysicalGameObj(in);
	if (!i2)
	{
		return;
	}
	GameObject *o2 = As_PhysicalGameObj(out);
	if (!o2)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,i2
		mov ebx,Get_Transform
		call ebx
		push eax
		mov ecx,o2
		mov ebx,Set_Transform
		call ebx
	}
#else
	Set_Transform(o2,Get_Transform(i2));
#endif
}

const char *Get_Current_Weapon(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return w->Vector[w->current]->WeaponDef->Get_Name();
	}
	return 0;
}

int Get_Current_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->LoadedBullets.Get();
	}
	return 0;
}

int Get_Current_Clip_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->InventoryBullets.Get();
	}
	return 0;
}

int Get_Current_Total_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		int bullets = wc->LoadedBullets.Get();
		int clipbullets = wc->InventoryBullets.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Position_Bullets(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->LoadedBullets.Get();
	}
	return 0;
}

int Get_Position_Clip_Bullets(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->InventoryBullets.Get();
	}
	return 0;
}

int Get_Position_Total_Bullets(GameObject *obj, int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		int bullets = wc->LoadedBullets.Get();
		int clipbullets = wc->InventoryBullets.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->LoadedBullets.Get();
			}
		}
	}
	return 0;
}

int Get_Clip_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->InventoryBullets.Get();
			}
		}
	}
	return 0;
}

int Get_Total_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				int bullets = wc->LoadedBullets.Get();
				int clipbullets = wc->InventoryBullets.Get();
				if (clipbullets < 0)
				{
					return -1;
				}
				return bullets+clipbullets;
			}
		}
	}
	return 0;
}

int Get_Current_Max_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->ClipSize.Get();
	}
	return 0;
}

int Get_Current_Clip_Max_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->MaxInventoryRounds.Get();
	}
	return 0;
}

int Get_Current_Total_Max_Bullets(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		int bullets = wc->WeaponDef->ClipSize.Get();
		int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Position_Max_Bullets(GameObject *obj, int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->ClipSize.Get();
	}
	return 0;
}

int Get_Position_Clip_Max_Bullets(GameObject *obj, int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->MaxInventoryRounds.Get();
	}
	return 0;
}

int Get_Position_Total_Max_Bullets(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		int bullets = wc->WeaponDef->ClipSize.Get();
		int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
		if (clipbullets < 0)
		{
			return -1;
		}
		return bullets+clipbullets;
	}
	return 0;
}

int Get_Max_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->ClipSize.Get();
			}
		}
	}
	return 0;
}

int Get_Max_Clip_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->MaxInventoryRounds.Get();
			}
		}
	}
	return 0;
}

int Get_Max_Total_Bullets(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				int bullets = wc->WeaponDef->ClipSize.Get();
				int clipbullets = wc->WeaponDef->MaxInventoryRounds.Get();
				if (clipbullets < 0)
				{
					return -1;
				}
				return bullets+clipbullets;
			}
		}
	}
	return 0;
}

int Get_Weapon_Count(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	return w->Vector.Count();
}

const char *Get_Weapon(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if (w->Vector[position])
	{
		return (w->Vector[position]->WeaponDef->Get_Name());
	}
	return 0;
}

bool Has_Weapon(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return false;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				return true;
			}
		}
	}
	return false;
}

float Get_Mass(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return 0;
	}
	o+=0x774;
	char *p = (char *)*(unsigned int *)o;
#ifdef WIN32
	p += 0x84;
#else
#ifndef RH8
	p += 0xA0;
#else
	p += 0x9C;
#endif
#endif
	return *(float *)p;
}

const char *Get_Htree_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "DUMMY";
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return "DUMMY";
	}
#ifdef WIN32
	_asm {
		mov eax,o
		mov ebx,[eax+0x774]
		mov ecx,[ebx+0x3C]
		mov eax,[ecx]
		mov ebx,[eax+0xC8]
		call ebx
	}
#else
	o+=0x774;
	char *p = (char *)*(unsigned int *)o;
	p+=0x54;
	char *r = (char *)*(unsigned int *)p;
#ifndef RH8
	r += 0x1C;
#endif
	char *v = (char *)*(unsigned int *)r;
#ifndef RH8
	r -= 0x1C;
	v += 4;
#endif
	v += 0xCC;
	Get_Htree *h = (Get_Htree*)v;
	Get_Htree gh = (Get_Htree)*h;
	const char *c = gh(r);
	return c;
#endif
}

char Get_Sex(GameObject *obj)
{
	return Get_Htree_Name(obj)[2];
}

void Force_Occupant_Exit(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	if (seat >= occupants.Length())
	{
		return;
	}
	if (occupants[seat])
	{
		Check_Transitions(occupants[seat],true);
	}
}

void Force_Occupants_Exit(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			Check_Transitions(occupants[i],true);
		}
	}
}

void Damage_Objects_Half()
{
	GenericSLNode *z = BaseGameObjList->HeadNode;
	while (z)
	{
		GameObject *obj = (GameObject *)z->NodeData;
		if (obj)
		{
			if (As_SoldierGameObj(obj) || As_VehicleGameObj(obj))
			{
				float Health = Commands->Get_Max_Health(obj) + Commands->Get_Max_Shield_Strength(obj);
				Commands->Apply_Damage(obj,(Health / 2),"None",0);
			}
		}
		z = z->NodeNext;
	}
}

GameObject *Get_Vehicle_Return(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return obj;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (o)
	{
		char *c = (char *)o;
		c += 0x98C;
		unsigned long *l = (unsigned long *)c;
		GameObject *vehicle = (GameObject *)*l;
		if (vehicle)
		{
			GameObject *v = As_VehicleGameObj(vehicle);
			return v;
		}
		return obj;
	}
	return obj;
}

int Get_Beacon_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

GameObject *Find_Beacon(int Number,int Team)
{
	if (Number < 0)
	{
		Number = 0;
	}
	if (!Number)
	{
		return 0;
	}
	int Total = 0;
	GameObject *ReturnObj = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_BeaconGameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
			if (Total == Number) ReturnObj = o;
		}
		x = x->NodeNext;
	}
	return ReturnObj;
}

bool Is_Script_Attached(GameObject *obj,const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			return true;
		}
	}
	return false;
}

void Attach_Script_Once(GameObject *obj,const char *script,const char *params)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	if (!Is_Script_Attached(obj,script))
	{
		Commands->Attach_Script(obj,script,params);
	}
}

void Attach_Script_Preset_Once(const char *script,const char *params,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Type_Once(const char *script,const char *params,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Player_Once(const char *script,const char *params,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == Soldier)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Building(const char *script,const char *params,int team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if ((o) && As_BuildingGameObj(o))
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Commands->Attach_Script(o,script,params);
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Is_Preset(GameObject *obj,const char *preset,const char *script,const char *params,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DefinitionClass *d = Get_Definition(obj);
	if (!_stricmp(d->Get_Name(),preset))
	{
		if ((Get_Object_Type(obj) == team) || (team == 2))
		{
			Commands->Attach_Script(obj,script,params);
		}
	}
}

void Attach_Script_Is_Type(GameObject *obj,unsigned long type,const char *script,const char *params,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DefinitionClass *d = Get_Definition(obj);
	if (d->Get_Class_ID() == type)
	{
		if ((Get_Object_Type(obj) == team) || (team == 2))
		{
			Commands->Attach_Script(obj,script,params);
		}
	}
}

bool Is_A_Building(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (((ScriptableGameObj *)obj)->As_BuildingGameObj())
	{
		return true;
	}
	return false;
}

GameObject *Find_Closest_Non_Building_Object_By_Team(int Team,Vector3 position)
{
	float closestdist = FLT_MAX;
	GameObject *closest = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if ((Get_Object_Type(o) == Team) && !Is_A_Building(o))
			{
				Vector3 pos = Commands->Get_Position(o);
				float dist = Commands->Get_Distance(pos,position);
				if (dist < closestdist)
				{
					closestdist = dist;
					closest = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return closest;
}

bool Get_Fly_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return false;
	}
	char *c = (char *)obj;
	c += 0xD24;
	return *(bool *)c;
}

bool Is_Stealth(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SmartGameObj(obj);
	if (!o)
	{
		return false;
	}
	char *c = (char *)obj;
	c += 0x83D;
	return *(bool *)c;
}

void Send_Custom_All_Objects_Area(int message,const Vector3 &Position,float Distance,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj))
		{
			Vector3 ObjPosition = Commands->Get_Position(obj);
			Vector3 TestPosition = Position;
			ObjPosition.Z = 0;
			TestPosition.Z = 0;
			if ((Commands->Get_Distance(ObjPosition,TestPosition) <= Distance))
			{
				if ((Get_Object_Type(obj) == team) || (team == 2))
				{
					Commands->Send_Custom_Event(sender,obj,message,0,0);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Send_Custom_All_Objects(int message,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj))
		{
			if ((Get_Object_Type(obj) == team) || (team == 2))
			{
				Commands->Send_Custom_Event(sender,obj,message,0,0);
			}
		}
		x = x->NodeNext;
	}
}

void Create_Effect_All_Stealthed_Objects_Area(const Vector3 &Position,float Distance,const char *object,const Vector3 &offset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && As_ScriptableGameObj(obj))
		{
			Vector3 ObjPosition = Commands->Get_Position(obj);
			Vector3 TestPosition = Position;
			ObjPosition.Z = 0;
			TestPosition.Z = 0;
			if ((Commands->Get_Distance(ObjPosition,TestPosition) <= Distance))
			{
				if ((Get_Object_Type(obj) == team) || (team == 2))
				{
					bool stealth = Is_Stealth(obj);
					if (stealth)
					{
						ObjPosition = Commands->Get_Position(obj);
						ObjPosition.X += offset.X;
						ObjPosition.Y += offset.Y;
						ObjPosition.Z += offset.Z;
						Commands->Create_Object(object,ObjPosition);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Kill_Occupants(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			Commands->Apply_Damage(occupants[i],100,"Death",0);
		}
	}
}

int Tally_Team_Size(int team)
{
	return TallyTeamSize(team);
}

float Get_Team_Score(int team)
{
	char *teamdata = Find_Team(team);
	teamdata += 0x6C0;
	return *((float *)teamdata);
}

const char *Get_IP_Address(int PlayerID)
{
	sockaddr_in *addr;
	bool noaddr = false;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov addr,eax
		jmp loc2
loc1:
		mov noaddr,1
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		addr = Get_Address(RemoteHost);
	}
	else
	{
		noaddr = true;
	}
#endif
	char *temp;
	temp = new char[40];
	int ip1,ip2,ip3,ip4;
	if (!noaddr)
	{
		ip1 = addr->sin_addr.s_addr&0x000000FF;
		ip2 = (addr->sin_addr.s_addr&0x0000FF00)>>8;
		ip3 = (addr->sin_addr.s_addr&0x00FF0000)>>16;
		ip4 = (addr->sin_addr.s_addr&0xFF000000)>>24;
	}
	else
	{
		ip1 = 0;
		ip2 = 0;
		ip3 = 0;
		ip4 = 0;
	}
	sprintf(temp,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
	return temp;
}

int Get_C4_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_C4GameObj(o))
		{
			if (Team == 2)
			{
				Total++;
			}
			else if (Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

char *newstr(const char *str)
{
	unsigned long len = strlen(str)+1;
	char *s = new char[len];
	memcpy(s,str,len);
	return s;
}

wchar_t *newwcs(const wchar_t *str)
{
	unsigned long len = wcslen(str)+2;
	wchar_t *s = new wchar_t[len];
	memcpy(s,str,len*2);
	return s;
}

char Get_Mine_Limit()
{
	return *Mine_Limit;
}

bool Is_Gameplay_Permitted()
{
	return The_Game()->Is_Gameplay_Permitted();
}

unsigned long Get_Ping(int PlayerID)
{
	int ping;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov eax,[eax+0x2A4]
		mov ping,eax
		jmp loc2
loc1:
		mov ping, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		RemoteHost += 0x29C;
		ping = *(int *)RemoteHost;
	}
	else
	{
		ping = 0;
	}
#endif
	return ping;
}

unsigned long Get_Kbits(int PlayerID)
{
	int kbits;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov ecx, PacketManager
		push eax
		call Bandwidth_Out
		mov kbits, eax
		jmp loc2
loc1:
		mov kbits, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		sockaddr_in *addr = Get_Address(RemoteHost);
		kbits = Bandwidth_Out(PacketManager,addr);
	}
	else
	{
		kbits = 0;
	}
#endif
	return kbits >> 0x0A;
}

void Send_Custom_Event_To_Object(GameObject *sender,const char *Preset,int message,int param,float delay)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),Preset))
			{
				Commands->Send_Custom_Event(sender,o,message,param,delay);
			}
		}
		x = x->NodeNext;
	}
}

int Get_Vehicle_Seat_Count(GameObject *obj,int seat)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return 0;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	return occupants.Length();
}

char *Get_Spawn_Char(int Team)
{
	if (!Team)
	{
		return SpawnCharNod;
	}
	else if (Team == 1)
	{
		return SpawnCharGDI;
	}
	return "None";
}

void Change_Spawn_Char(int Team,const char *Name)
{
	if (strlen(Name) > 24)
	{
		return;
	}
	else if (!Team)
	{
		memcpy((void*)SpawnCharNod,(void*)Name,24);
	}
	else if (Team == 1)
	{
		memcpy((void*)SpawnCharGDI,(void*)Name,24);
	}
}

int Get_Building_Count_Team(int Team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	int Count = 0;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o && Commands->Get_Health(o) > 0 && (Get_Object_Type(o) == Team || Team == 2))
		{
			Count++;
		}
		x = x->NodeNext;
	}
	return Count;
}
void Ranged_Percentage_Damage_To_Vehicles(float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	if (DamageRadius > 0)
	{
		GenericSLNode *x = BaseGameObjList->HeadNode;
		while (x)
		{
			GameObject *o = (GameObject *)x->NodeData;
			if (o)
			{
				if (As_VehicleGameObj(o))
				{
					float health = Commands->Get_Health(o);
					if (health > 0)
					{
						Vector3 pos1 = Commands->Get_Position(o);
						Vector3 pos2 = Location;

						float Distance = Commands->Get_Distance(pos1,pos2);

						if (Distance <= DamageRadius)
						{
							float Max_Health = Commands->Get_Max_Health(o);
							float Max_Shield = Commands->Get_Max_Shield_Strength(o);
							float Damage = (Max_Health + Max_Shield) * Percentage;
							Commands->Apply_Damage(o,Damage,Warhead,Damager);
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

int Get_Bandwidth(int PlayerID)
{
	int bandwidth;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov eax,[eax+0x338]
		mov bandwidth,eax
		jmp loc2
loc1:
		mov bandwidth, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		RemoteHost += 0x330;
		bandwidth = *(int *)RemoteHost;
	}
	else
	{
		bandwidth = 0;
	}
#endif
	return bandwidth;
}

bool Is_Dedicated()
{
	return Exe;
}

void Soldier_Transition_Vehicle(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj || !As_SoldierGameObj(obj))
	{
		return;
	}
	Check_Transitions(obj,true);
}

bool Is_Linux()
{
	if ((Exe == 2) || (Exe == 3))
	{
		return true;
	}
	return false;
}
unsigned int Get_Current_Game_Mode()
{
	if (*GameType == 1)
	{
		return 1;
	}
	if (*GameType == 2)
	{
		return 2;
	}
	if (*GameType == 3)
	{
		if (*GameMode == 1)
		{
			return 5;
		}
		if (*GameMode == 2)
		{
			return 3;
		}
		if (*GameMode == 3)
		{
			return 4;
		}
		if (Game_Mode_Find("WOL"))
		{
			return 3;
		}
		if (Game_Mode_Find("LAN"))
		{
			if (*IsListed)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
	}
	return 0;
}

int Get_Team(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->PlayerType.Get();
}

int Get_Rank(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Rung.Get();
}

int Get_Kills(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Kills.Get();
}

int Get_Deaths(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Deaths.Get();
}

float Get_Score(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Score.Get();
}

float Get_Money(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Money.Get();
}

float Get_Kill_To_Death_Ratio(int PlayerID)
{
	int kills = Get_Kills(PlayerID);
	int deaths = Get_Deaths(PlayerID);
	if (deaths <= 0)
	{
		return -1.0;
	}
	return (float)kills/(float)deaths;
}

float Get_Damage_Points(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return 0;
	}
	return o->Defence.DamagePoints.Get();
}

float Get_Death_Points(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return 0;
	}
	return o->Defence.DeathPoints.Get();
}

void Set_Damage_Points(GameObject *obj,float points)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->Defence.DamagePoints.Set(points);
}

void Set_Death_Points(GameObject *obj,float points)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DamageableGameObj *o = ((ScriptableGameObj *)obj)->As_DamageableGameObj();
	if (!o)
	{
		return;
	}
	o->Defence.DeathPoints.Set(points);
}

int Get_C4_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_C4GameObj(obj);
	if (!o)
	{
		return 0;
	}
	unsigned int *def = (unsigned int *)(o+0x7C8);
	unsigned int *x = (unsigned int *)*def;
	x+=0x23;
	int mode;
#ifdef WIN32
	_asm {
		mov ecx, x
		call Get_Safe_Data_Int
		mov mode, eax
	}
#else
	mode = *(int *)x;
#endif
	return mode;
}

const char *Get_IP_Port(int PlayerID)
{
	sockaddr_in *addr;
	bool noaddr = false;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov addr,eax
		jmp loc2
loc1:
		mov noaddr,1
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		addr = Get_Address(RemoteHost);
	}
	else
	{
		noaddr = true;
	}
#endif
	char *temp;
	temp = new char[40];
	int ip1,ip2,ip3,ip4,port;
	if (!noaddr)
	{
		ip1 = addr->sin_addr.s_addr&0x000000FF;
		ip2 = (addr->sin_addr.s_addr&0x0000FF00)>>8;
		ip3 = (addr->sin_addr.s_addr&0x00FF0000)>>16;
		ip4 = (addr->sin_addr.s_addr&0xFF000000)>>24;
		port = ntohs(addr->sin_port);
	}
	else
	{
		ip1 = 0;
		ip2 = 0;
		ip3 = 0;
		ip4 = 0;
		port = 0;
	}
	sprintf(temp,"%d.%d.%d.%d;%d",ip1,ip2,ip3,ip4,port);
	return temp;
}

void Repair_All_Buildings_By_Team_Radius(int Team,int ConstructionYardID,float Health,float Radius)
{
	Vector3 Location = Commands->Get_Position(Commands->Find_Object(ConstructionYardID));
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team) && (Commands->Get_ID(o) != ConstructionYardID))
			{
				float amount = Commands->Get_Health(o);
				if (amount>0)
				{
					Vector3 pos1 = Commands->Get_Position(o);
					Vector3 pos2 = Location;
					float Distance = Commands->Get_Distance(pos1,pos2);
					if (Distance <= Radius)
					{
						Commands->Set_Health(o,(amount+Health));
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

const char *Get_Translated_String(unsigned long ID)
{
	if (ID < 1000)
	{
		return newstr("No String");
	}
	return WideCharToChar(*Get_TDB_Object(ID-1000)->Get_String());
}

const wchar_t *Get_Wide_Translated_String(unsigned long ID)
{
	if (ID < 1000)
	{
		return L"No String";
	}
	return *Get_TDB_Object(ID-1000)->Get_String();
}

const char *Get_Translated_Preset_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return "";
	}
	GameObject *o = As_DamageableGameObj(obj);
	if (!o)
	{
		return "";
	}
	DamageableGameObjDef *d = (DamageableGameObjDef *)Get_Definition(obj);
	return Get_Translated_String(d->TranslatedNameID);
}

const wchar_t *Get_Current_Wide_Translated_Weapon(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return Get_Wide_Translated_String(w->Vector[w->current]->WeaponDef->IconNameID);
	}
	return 0;
}

const char *Get_Current_Translated_Weapon(GameObject *obj)
{
	return WideCharToChar(Get_Current_Wide_Translated_Weapon(obj));
}

const char *Get_Translated_Weapon(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if (w->Vector[position])
	{
		return Get_Translated_String(w->Vector[position]->WeaponDef->IconNameID);
	}
	return 0;
}

int Get_C4_Count_Proximity(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 3)
		{
			if (Team == 2 || Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

int Get_C4_Count_Remote(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 1)
		{
			if (Team == 2 || Get_Object_Type(o) == Team)
			{
				Total++;
			}
		}
		x = x->NodeNext;
	}
	return Total;
}

void Attach_Script_All_Buildings_Team(int Team,const char *Script,const char *Params,bool Once)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team || Team == 2)
			{
				if (Once)
				{
					Attach_Script_Once(o,Script,Params);
				}
				else
				{
					Commands->Attach_Script(o,Script,Params);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_All_Turrets_Team(int Team,const char *Script,const char *Params,bool Once)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_VehicleGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Is_DecorationPhys(o) && (Get_Object_Type(o) == Team || Team == 2))
			{
				if (Once)
				{
					Attach_Script_Once(o,Script,Params);
				}
				else
				{
					Commands->Attach_Script(o,Script,Params);
				}
			}
		}
		x = x->NodeNext;
	}
}

#define LOWER(chr) ((chr >= 'A') && (chr <= 'Z') ? chr+32 : chr)

char *stristr(const char *m_pStr1, const char *m_pStr2)
{
	register char *m_pCP = (char *)m_pStr1;
	register char *m_pS1, *m_pS2;
	while (*m_pCP)
	{
		m_pS1 = m_pCP;
		m_pS2 = (char *) m_pStr2;
		while (*m_pS1 && *m_pS2 && !(LOWER(*m_pS1) - LOWER(*m_pS2)))
		{
			m_pS1++, m_pS2++;
		}
		if (!*m_pS2)
		{
			return m_pCP;
		}
		m_pCP++;
	}
	return NULL;
}

GameObject *Get_Part_Name(const char *name1)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	int count = 0;
	GameObject *current = 0;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o)
		{
			const char *name = Get_Player_Name(o);
			if (!stristr(name,name1))
			{
				current = o;
				count++;
			}
			delete name;
		}
		x = x->NodeNext;
	}
	if ((count == 1) && (current) && (Commands->Get_ID(current)))
	{
		return current;
	}
	else
	{
		return 0;
	}
}

int Get_Part_Names(const char *name1)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	int count = 0;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o)
		{
			const char *name = Get_Player_Name(o);
			if (!stristr(name,name1))
			{
				count++;
			}
			delete name;
		}
		x = x->NodeNext;
	}
	return count;
}

GameObject *Get_C4_Planter(GameObject *obj)
{	
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_C4GameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x7BC;
	ReferenceableClass<ScriptableGameObj> *r = *(ReferenceableClass<ScriptableGameObj> **)c;
	if (r)
	{
		return (GameObject *)r->obj;
	}
	return 0;
}

GameObject *Get_C4_Attached(GameObject *obj)
{	
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_C4GameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x7DC;
	ReferenceableClass<ScriptableGameObj> *r = *(ReferenceableClass<ScriptableGameObj> **)c;
	if (r)
	{
		return (GameObject *)r->obj;
	}
	return 0;
}

GameObject *Get_Beacon_Planter(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_BeaconGameObj(obj);
	if (!o)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx,o
		mov ebx,Get_Beacon_Owner
		call ebx
	}
#else
	Get_Beacon_Owner(o);
#endif
}

unsigned int Get_Vehicle_Mode(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		return 0;
	}
	DefinitionClass *d = Get_Definition(obj);
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

void Repair_All_Turrets_By_Team(int team,float health)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_VehicleGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == team && (Get_Vehicle_Mode(o) == TURRET))
			{
				float amount = Commands->Get_Health(o);
				if (amount>0)
				{
					Commands->Set_Health(o,(amount+health));
				}
				amount = Commands->Get_Shield_Strength(o);
				if (amount>0)
				{
					Commands->Set_Shield_Strength(o,(amount+health));
				}
			}
		}
		x = x->NodeNext;
	}
}

void Get_Team_Color(unsigned int team, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	Vector3 v;
	Get_Color_For_Team(&v,team);
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

void Get_Player_Color(int PlayerID, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	Vector3 v;
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	v = x->Get_Color();
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

void Get_Object_Color(GameObject *obj, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	Vector3 v;
	Vector3 *v2 = &v;
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_DamageableGameObj(obj);
	if (!o)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,o
		mov ebx,Get_Obj_Color
		push v2
		call ebx
	}
#else
	Get_Obj_Color(v2,o);
#endif
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

void Get_Private_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue)
{
	*red = (unsigned int)(PrivateMessageColor[0]*255);
	*green = (unsigned int)(PrivateMessageColor[1]*255);
	*blue = (unsigned int)(PrivateMessageColor[2]*255);
}

void Get_Public_Message_Color(unsigned int *red, unsigned int *green, unsigned int *blue)
{
	*red = (unsigned int)(PublicMessageColor[0]*255);
	*green = (unsigned int)(PublicMessageColor[1]*255);
	*blue = (unsigned int)(PublicMessageColor[2]*255);
}

void Disarm_C4(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_C4GameObj(obj);
	if (!o)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,o
		mov ebx,C4Defuse
		call ebx
	}
#else
	C4Defuse(o);
#endif
}

void Disarm_All_Proxy_C4(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o && Get_C4_Mode(o) == 3)
		{
			if (Get_Player_ID(Get_C4_Planter(o)) == PlayerID)
			{
				Disarm_C4(o);
			}
		}
		x = x->NodeNext;
	}
}

void Disarm_All_C4(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_C4GameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o)
		{
			if (Get_Player_ID(Get_C4_Planter(o)) == PlayerID)
			{
				Disarm_C4(o);
			}
		}
		x = x->NodeNext;
	}
}

int Get_Team_Vehicle_Count(int team)
{
	GameObject *o = Find_Vehicle_Factory(team);
	if (!o)
	{
		return 0;
	}
#ifdef WIN32
	_asm {
		mov ecx, o
		mov ebx, GetVehicleCount
		call ebx
	}
#else
	return GetVehicleCount(o);
#endif
}

bool Is_Base_Powered(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->IsPowered;
	}
	return false;
}

bool Can_Generate_Vehicles(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->CanGenerateVehicles;
	}
	return false;
}

bool Can_Generate_Soliders(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->CanGenerateSoldiers;
	}
	return false;
}

void Damage_Occupants(GameObject *obj,float Damage,const char *Warhead)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if (occupants[i])
		{
			Commands->Apply_Damage(occupants[i],Damage,Warhead,0);
		}
	}
}

const char *Get_Team_Name(int Team)
{
	if (!Team)
	{
		return Get_Translated_String(7198);
	}
	else if (Team == 1)
	{
		return Get_Translated_String(7199);
	}
	return "Neutral";
}

const wchar_t *Get_Wide_Vehicle_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return L"Vehicle";
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		return L"Vehicle";
	}
#ifdef WIN32
	_asm {
		mov ecx, o
		mov ebx, Get_VehicleName
		call ebx
	}
#else
	return Get_VehicleName(o);
#endif
}

const char *Get_Vehicle_Name(GameObject *obj)
{
	return WideCharToChar(Get_Wide_Vehicle_Name(obj));
}

void Set_Current_Bullets(GameObject *obj,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		w->Vector[w->current]->InventoryBullets.Set(bullets);
	}
}

void Set_Current_Clip_Bullets(GameObject *obj,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		w->Vector[w->current]->LoadedBullets.Set(bullets);
	}
}

void Set_Position_Bullets(GameObject *obj,int position,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		w->Vector[position]->InventoryBullets.Set(bullets);
	}
}

void Set_Position_Clip_Bullets(GameObject *obj,int position,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		w->Vector[position]->LoadedBullets.Set(bullets);
	}
}

void Set_Bullets(GameObject *obj,const char *weapon,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				w->Vector[i]->InventoryBullets.Set(bullets);
			}
		}
	}
}

void Set_Clip_Bullets(GameObject *obj,const char *weapon,int bullets)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				w->Vector[i]->LoadedBullets.Set(bullets);
			}
		}
	}
}

void Disarm_Beacon(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_BeaconGameObj(obj);
	if (!o)
	{
		return;
	}
#ifdef WIN32
	_asm {
		mov ecx,o
		mov eax,0
		push eax
		mov ebx,Completly_Damaged
		call ebx
	}
#else
	Completly_Damaged(o,0);
#endif
}

void Disarm_Beacons(int PlayerID)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BeaconGameObj(As_ScriptableGameObj((GameObject *)x->NodeData));
		if (o)
		{
			if (Get_Player_ID(Get_Beacon_Planter(o)) == PlayerID)
			{
				Disarm_Beacon(o);
			}
		}
		x = x->NodeNext;
	}
}

GameObject *Find_Harvester(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	GameObject *o = 0;
	if (c)
	{
		o = c->Get_Harvester_Vehicle();
	}
	return o;
}

const char *Get_Powerup_Weapon(const char *Powerup)
{
	DefinitionClass *powerupdef = Find_Named_Definition(Powerup);
	char *c = (char *)powerupdef;
	if (!c)
	{
		return "None";
	}
#ifdef RH8
	c += 0xC0;
#else
	c += 0xC4;
#endif
	unsigned long weapondefid = (unsigned long)*(unsigned long *)c;
	if (weapondefid)
	{
		DefinitionClass *weapondef = Find_Definition(weapondefid,1);
		return weapondef->Get_Name();
	}
	return "None";
}

GameObject *Get_Vehicle_Owner(GameObject *obj)
{	
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_VehicleGameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x9E0;
	ReferenceableClass<ScriptableGameObj> *r = *(ReferenceableClass<ScriptableGameObj> **)c;
	if (r)
	{
		return (GameObject *)r->obj;
	}
	return 0;
}

TeamPurchaseSettingsDefClass *Get_Team_Purchase_Definition(unsigned long team)
{
	return TeamPurchaseSettingsDefClass::Get_Definition(team);
}

PurchaseSettingsDefClass *Get_Purchase_Definition(unsigned long type, unsigned long team)
{
	return PurchaseSettingsDefClass::Find_Definition(type,team);
}

const char *Get_Definition_Name(unsigned long id)
{
	if (!id)
	{
		return "none";
	}
	DefinitionClass *d = Find_Definition(id,1);
	if (!d)
	{
		return "none";
	}
	return d->Get_Name();
}

unsigned long Get_Definition_ID(const char *name)
{
	if (!name)
	{
		return 0;
	}
	DefinitionClass *d = Find_Named_Definition(name);
	if (!d)
	{
		return 0;
	}
	return d->Get_ID();
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
		for (unsigned int j = 0;j < 10;j++)
		{
			if ((Get_Purchase_Definition(i,team)) && (Get_Purchase_Definition(i,team)->presetids[j] == ID))
			{
				return Get_Purchase_Definition(i,team)->costs[j];
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
	t->textures[position] = texture;
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
	t->beacontexture = texture;
}

void Set_Refill(unsigned int team, unsigned int stringid, const char *texture)
{
	if (team > 1)
	{
		return;
	}
	TeamPurchaseSettingsDefClass *t = Get_Team_Purchase_Definition(team);
	t->refillstringid = stringid;
	t->refilltexture = texture;
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
	p->textures[position] = texture;
}

void Set_Alternate(unsigned int team, unsigned int type, unsigned int position, unsigned int altpos, unsigned int presetid, const char *texture)
{
	if ((team > 1) || (type > 4) || (position > 9) || (altpos > 2))
	{
		return;
	}
	PurchaseSettingsDefClass *p = Get_Purchase_Definition(type,team);
	p->altpresetids[position][altpos] = presetid;
	p->alttextures[position][altpos] = texture;
}

void Force_Occupants_Exit_Team(GameObject *obj,int team)
{
	if (!Commands->Get_ID(obj) || !obj || !As_VehicleGameObj(obj))
	{
		return;
	}
	VectorClass<GameObject *> *ptr = (VectorClass<GameObject *>*)(obj+0x9AC);
	VectorClass<GameObject *> occupants = (VectorClass<GameObject *>)*ptr;
	int x = occupants.Length();
	for (int i = 0;i < x;i++)
	{
		if ((occupants[i]) && (Commands->Get_Player_Type(occupants[i]) != team))
		{
			Check_Transitions(occupants[i],true);
		}
	}
}

void Power_Base(int team,bool powered)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Power_Base(powered);
	}
}

void Set_Can_Generate_Soldiers(int team,bool cangenerate)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Can_Generate_Soldiers(cangenerate);
	}
}

void Set_Can_Generate_Vehicles(int team,bool cangenerate)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Can_Generate_Vehicles(cangenerate);
	}
}

void Destroy_Base(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Destroy_Base();
	}
}

void Beacon_Destroyed_Base(int team, bool destroyed)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Set_Beacon_Destroyed_Base(destroyed);
	}
}

void Enable_Base_Radar(int team, bool enable)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		c->Enable_Radar(enable);
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
	p->presetids[position] = 0;
	p->costs[position] = 0;
	p->stringids[position] = 0;
	p->textures[position] = " ";
	for (unsigned int i = 0;i < 3;++i)
	{
		p->altpresetids[position][i] = 0;
		p->alttextures[position][i] = " ";
	}
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
	t->textures[position] = " ";
}

bool Is_Harvester(GameObject *obj)
{
	if (!As_VehicleGameObj(obj))
	{
		return false;
	}
	int ID = Commands->Get_ID(obj);
	if (Commands->Get_ID(Find_Harvester(0)) == ID || Commands->Get_ID(Find_Harvester(1)) == ID)
	{
		return true;
	}
	return false;
}

GameObject *Get_GameObj_By_Player_Name(const char *name)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && Commands->Is_A_Star(o))
		{
			const char *c = Get_Player_Name(o);
			if (!_stricmp(c,name))
			{
				return o;
			}
			delete c;
		}
		x = x->NodeNext;
	}
	return 0;
}

unsigned long Get_Definition_Class_ID(const char *name)
{
	if (!name)
	{
		return 0;
	}
	DefinitionClass *d = Find_Named_Definition(name);
	if (!d)
	{
		return 0;
	}
	return d->Get_Class_ID();
}

unsigned int Get_Vehicle_Definition_Mode(const char *preset)
{
	DefinitionClass *d = Find_Named_Definition(preset);
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

bool Is_Radar_Enabled(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->RadarEnabled;
	}
	return false;
}

int Building_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_BuildingGameObj(obj);
	if (!o)
	{
		return 0;
	}
	DefinitionClass *d = Get_Definition(obj);
	char *c = (char *)d;
	c += 0x8C;
	return *(int *)c;
}

bool Is_Building_Dead(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_BuildingGameObj(obj);
	if (!o)
	{
		return 0;
	}
	char *c = (char *)obj;
	c += 0x778;
	return *(bool *)c;
}

GameObject *Find_Building(int team,int type)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->Find_Building(type);
	}
	return 0;
}

GameObject *Find_Base_Defence(int team)
{
	BaseControllerClass *c = BaseControllerClass::Find_Base(team);
	if (c)
	{
		return c->Find_Building(BASE_DEFENCE);
	}
	return 0;
}

bool Purchase_Item(GameObject *obj,int cost)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return false;
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	return x->Purchase_Item(cost);
}

bool Is_Map_Flying()
{
	return *IsMapVTOL;
}

bool IsInsideZone(GameObject *zone,GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (!Commands->Get_ID(zone) || !zone)
	{
		return false;
	}
	GameObject *o = As_SmartGameObj(obj);
	GameObject *o2 = As_ScriptZoneGameObj(zone);
	if ((o) && (o2))
	{
		((ScriptZoneGameObj *)o2)->Inside_Me((SmartGameObj *)o);
	}
	return false;
}

GameObject *Find_Closest_Preset_By_Team(int Team,const Vector3 &pos,const char *Preset)
{
	float closestdist = 9999.0f;
	GameObject *closest = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				float dist = Commands->Get_Distance(Commands->Get_Position(o),pos);
				if (dist < closestdist)
				{
					closestdist = dist;
					closest = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return closest;
}

GameObject *Find_Random_Preset_By_Team(int Team,const char *Preset)
{
	SimpleDynVecClass<GameObject*> ObjList(0);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				ObjList.Add(o);
			}
		}
		x = x->NodeNext;
	}
	int len = ObjList.Count();
	if (len > 1)
	{
		return ObjList[Commands->Get_Random_Int(0,len)];
	}
	else if (!len)
	{
		return 0;
	}
	return ObjList[0];
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

int Get_Object_Count(int Team,const char *Preset)
{
	int count = 0;
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				count++;
			}
		}
		x = x->NodeNext;
	}
	return count;
}

bool Is_Valid_Preset_ID(unsigned long ID)
{
	if (Find_Definition(ID,1))
	{
		return true;
	}
	return false;
}

bool Is_Valid_Preset(const char *Preset)
{
	if (Find_Named_Definition(Preset))
	{
		return true;
	}
	return false;
}

GameObject *Find_Building_With_Script(int Team,int Type,const char *Script,GameObject *Caller)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Type == -1 || Building_Type(o) == Type) && (Get_Object_Type(o) == Team || Team == 2) && !Is_Building_Dead(o) && Is_Script_Attached(o,Script) && o != Caller)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

unsigned int Get_Vehicle_Definition_Mode_By_ID(unsigned long ID)
{
	DefinitionClass *d = Find_Definition(ID,1);
	if (!d) return 5;
	char *c = (char *)d;
	c += 0xE0;
	return *(unsigned int *)c;
}

SimpleDynVecClass<GameObject*> Get_All_Objects_By_Preset(int Team,const char *Preset)
{
	SimpleDynVecClass<GameObject*> ObjList(0);
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_ScriptableGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if ((Get_Object_Type(o) == Team || Team == 2) && !_stricmp(Commands->Get_Preset_Name(o),Preset))
			{
				ObjList.Add(o);
			}
		}
		x = x->NodeNext;
	}
	return ObjList;
}

void Damage_All_Objects_In_Zone(GameObject *Zone,float Damage,const char *Warhead,GameObject *Damager)
{
	if (!Commands->Get_ID(Zone) || !Zone)
	{
		return;
	}
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if (IsInsideZone(Zone,o))
			{
				Commands->Apply_Damage(o,Damage,Warhead,Damager);
			}
		}
		x = x->NodeNext;
	}
}

GameObject *Create_Building(const char *preset,const Vector3 & Position)
{
	DefinitionClass *d = Find_Named_Definition(preset);
	GameObject *obj = (GameObject *)d->Create();
	if (As_BuildingGameObj(obj))
	{
		char *c = (char *)obj;
		c += 0x77C;
		Vector3 *pos1 = (Vector3 *)c;
		c = (char *)obj;
		c += 0x7A4;
		Vector3 *pos2 = (Vector3 *)c;
		pos1->X = Position.X;
		pos1->Y = Position.Y;
		pos1->Z = Position.Z;
		pos2->X = Position.X;
		pos2->Y = Position.Y;
		pos2->Z = Position.Z;
#ifdef WIN32
		_asm {
			mov ecx,obj
			mov ebx,Collect_Building_Components
			call ebx
			mov ecx,obj
		}
#else
		Collect_Building_Components(obj);
#endif
		((ScriptableGameObj *)obj)->Start_Observers();
		return obj;
	}
	return 0;
}

unsigned int Get_Zone_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ScriptZoneGameObj(obj);
	if (!o)
	{
		return 0;
	}
	ScriptZoneGameObjDef *d = (ScriptZoneGameObjDef *)Get_Definition(obj);
	return d->ZoneType;
}

OBBoxClass *Get_Zone_Box(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	ScriptZoneGameObj *o = ((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
	if (!o)
	{
		return 0;
	}
	return &o->BoundingBox;
}

void Set_Zone_Box(GameObject *obj,const OBBoxClass &box)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	ScriptZoneGameObj *o = ((ScriptableGameObj *)obj)->As_ScriptZoneGameObj();
	if (!o)
	{
		return;
	}
	memcpy(&o->BoundingBox,&box,sizeof(OBBoxClass));
}

GameObject *Create_Zone(const char *preset,const OBBoxClass &box)
{
	GameObject *obj = Create_Library_Object(preset);
	Set_Zone_Box(obj,box);
	((ScriptableGameObj *)obj)->Start_Observers();
	return obj;
}

bool PointInZone(GameObject *obj,const Vector3 &v)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_ScriptZoneGameObj(obj);
	if (!o)
	{
		return false;
	}
	unsigned int x = Overlap_Test(*Get_Zone_Box(o),v);
	if (x == 2)
	{
		return true;
	}
	return false;
}

void Set_Money(int PlayerID,float amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Money(amount);
}

void Set_Score(int PlayerID,float amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Score(amount);
}

FileClass *Get_Data_File(char *file)
{
	return (*TheFileFactory)->Get_File(file);
}

void Close_Data_File(FileClass *file)
{
	(*TheFileFactory)->Return_File(file);
}

ChunkLoadClass::ChunkLoadClass(FileClass *file)
{
	File = file;
	StackIndex = 0;
	memset(HeaderStack,0,sizeof(HeaderStack));
	memset(PositionStack,0,sizeof(PositionStack));
	InMicroChunk = false;
	MicroChunkPosition = 0;
	MCHeader.ChunkType = 0;
}

bool ChunkLoadClass::Open_Chunk()
{
	if ((StackIndex <= 0) || (PositionStack[StackIndex-1] != (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF)))
	{
		if (File->Read(&HeaderStack[StackIndex],8) == 8)
		{
			PositionStack[StackIndex] = 0;
			StackIndex++;
			return true;
		}
	}
	return false;
}

bool ChunkLoadClass::Peek_Next_Chunk(unsigned int *id, unsigned int *length)
{
	ChunkHeader h;
	if ((StackIndex <= 0) || (PositionStack[StackIndex-1] != (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF)))
	{
		if (File->Read(&h,8) == 8)
		{
			File->Seek(-8,1);
			if (length)
			{
				*length = h.ChunkSize;
			}
			if (id)
			{
				*id = h.ChunkType & 0x7FFFFFFF;
			}
			return true;
		}
	}
	return false;
}

bool ChunkLoadClass::Close_Chunk()
{
	unsigned int x = HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF;
	if (PositionStack[StackIndex-1] < (x))
	{
		File->Seek((x) - PositionStack[StackIndex-1],1);
	}
	StackIndex--;
	if (StackIndex > 0)
	{
		PositionStack[StackIndex-1] += (x);
		PositionStack[StackIndex-1] += 8;
	}
	return true;
}

unsigned long ChunkLoadClass::Cur_Chunk_ID()
{
	return HeaderStack[StackIndex-1].ChunkType;
}

unsigned long ChunkLoadClass::Cur_Chunk_Length()
{
	return HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF;
}

int ChunkLoadClass::Cur_Chunk_Depth()
{
	return StackIndex;
}

int ChunkLoadClass::Contains_Chunks()
{
	return HeaderStack[StackIndex-1].ChunkSize & 0x80000000;
}

bool ChunkLoadClass::Open_Micro_Chunk()
{
	int bytesread = Read(&MCHeader,2);
	if (bytesread == 2)
	{
		MicroChunkPosition = 0;
		InMicroChunk = true;
		return true;
	}
	return false;
}

bool ChunkLoadClass::Close_Micro_Chunk()
{
	InMicroChunk = false;
	if (MicroChunkPosition < 0)
	{
		File->Seek(MCHeader.ChunkSize - MicroChunkPosition,1);
		if (StackIndex > 0)
		{
			PositionStack[StackIndex-1] += MCHeader.ChunkSize - MicroChunkPosition;
		}
	}
	return true;
}

unsigned long ChunkLoadClass::Cur_Micro_Chunk_ID()
{
	return MCHeader.ChunkType;
}

unsigned long ChunkLoadClass::Cur_Micro_Chunk_Length()
{
	return MCHeader.ChunkSize;
}

long ChunkLoadClass::Seek(unsigned long nbytes)
{
	if ((PositionStack[StackIndex-1] + nbytes) <= (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF))
	{
		if ((!InMicroChunk) || ((MicroChunkPosition + nbytes) <= MCHeader.ChunkSize))
		{
			int pos = File->Tell();
			int seek = File->Seek(nbytes,1);
			if ((seek - pos) == (int)nbytes)
			{
				PositionStack[StackIndex-1] += nbytes;
				if (InMicroChunk)
				{
					MicroChunkPosition += nbytes;
				}
				return nbytes;
			}
		}
	}
	return 0;
}

long ChunkLoadClass::Read(void *buf, unsigned long nbytes)
{
	if ((PositionStack[StackIndex-1] + nbytes) <= (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF))
	{
		if ((!InMicroChunk) || ((MicroChunkPosition + nbytes) <= MCHeader.ChunkSize))
		{
			int read = File->Read(buf,nbytes);
			if (read == (int)nbytes)
			{
				PositionStack[StackIndex-1] += nbytes;
				if (InMicroChunk)
				{
					MicroChunkPosition += nbytes;
				}
				return nbytes;
			}
		}
	}
	return 0;
}

long ChunkLoadClass::Read(IOVector2Struct *v)
{
	return Read(v,4);
}

long ChunkLoadClass::Read(IOVector3Struct *v)
{
	return Read(v,4);
}

long ChunkLoadClass::Read(IOVector4Struct *v)
{
	return Read(v,4);
}

long ChunkLoadClass::Read(IOQuaternionStruct *q)
{
	return Read(q,4);
}

ChunkSaveClass::ChunkSaveClass(FileClass *file)
{
	File = file;
	StackIndex = 0;
	memset(HeaderStack,0,sizeof(HeaderStack));
	memset(PositionStack,0,sizeof(PositionStack));
	InMicroChunk = false;
	MicroChunkPosition = 0;
	MCHeader.ChunkType = 0;
}

bool ChunkSaveClass::Begin_Chunk(unsigned long id)
{
	ChunkHeader chunkh;
	chunkh.ChunkSize = 0;
	chunkh.ChunkType = 0;
	if (StackIndex > 0)
	{
		HeaderStack[StackIndex-1].ChunkSize |= 0x80000000;
	}
	chunkh.ChunkType = id;
	chunkh.ChunkSize &= 0x80000000;
	PositionStack[StackIndex] = File->Seek(0,1);
	HeaderStack[StackIndex].ChunkType = chunkh.ChunkType;
	HeaderStack[StackIndex].ChunkSize = chunkh.ChunkSize;
	StackIndex++;
	if (File->Write(&chunkh,8) == 8)
	{
		return true;
	}
	return false;
}

bool ChunkSaveClass::End_Chunk()
{
	ChunkHeader chunkh;
	int temp = File->Seek(0,1);
	StackIndex--;
	chunkh.ChunkType = HeaderStack[StackIndex].ChunkType;
	chunkh.ChunkSize = HeaderStack[StackIndex].ChunkSize;
	File->Seek(PositionStack[StackIndex],0);
	if (File->Write(&chunkh,8) == 8)
	{
		if (StackIndex)
		{
			int temp = (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF) + (chunkh.ChunkSize & 0x7FFFFFFF) + 8;
			if (HeaderStack[StackIndex-1].ChunkSize & 0x80000000)
			{
				temp |= 0x80000000;
			}
			HeaderStack[StackIndex-1].ChunkSize = temp;
		}
		File->Seek(temp,0);
		return true;
	}
	return false;
}

int ChunkSaveClass::Cur_Chunk_Depth()
{
	return StackIndex;
}

bool ChunkSaveClass::Begin_Micro_Chunk(unsigned long id)
{
	MCHeader.ChunkType = (unsigned char)id;
	MicroChunkPosition = File->Seek(0,1);
	MCHeader.ChunkSize = 0;
	if (Write(&MCHeader,2) == 2)
	{
		InMicroChunk = true;
		return true;
	}
	return false;
}

bool ChunkSaveClass::End_Micro_Chunk()
{
	int temp = File->Seek(0,1);
	File->Seek(MicroChunkPosition,0);
	if (File->Write(&MCHeader,2) == 2)
	{
		File->Seek(temp,0);
		InMicroChunk = false;
		return true;
	}
	return false;
}

unsigned long ChunkSaveClass::Write(void* buf,unsigned long nbytes)
{
	if (File->Write(buf,nbytes) == (int)nbytes)
	{
		int temp = (HeaderStack[StackIndex-1].ChunkSize & 0x7FFFFFFF) + nbytes;
		if (HeaderStack[StackIndex-1].ChunkSize & 0x80000000)
		{
			temp |= 0x80000000;
		}
		HeaderStack[StackIndex-1].ChunkSize = temp;
		if (InMicroChunk)
		{
			MCHeader.ChunkSize = MCHeader.ChunkSize + (unsigned char)nbytes;
		}
		return nbytes;
	}
	return 0;
}

unsigned long ChunkSaveClass::Write(IOVector2Struct& v)
{
	return Write(&v,4);
}

unsigned long ChunkSaveClass::Write(IOVector3Struct& v)
{
	return Write(&v,4);
}

unsigned long ChunkSaveClass::Write(IOVector4Struct& v)
{
	return Write(&v,4);
}

unsigned long ChunkSaveClass::Write(IOQuaternionStruct& q)
{
	return Write(&q,4);
}

bool Is_Unit_In_Range(const char *preset,float range,Vector3 location,int team)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Get_Object_Type(o) == team) && (!_stricmp(Commands->Get_Preset_Name(o),preset)))
			{
				if (Commands->Get_Distance(Commands->Get_Position(o),location) <= range)
				{
					return true;
				}
			}
		}
		x = x->NodeNext;
	}
	return false;
}

void Set_Ladder_Points(int PlayerID,int amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Ladder_Points(amount);
}

void Set_Rung(int PlayerID,int amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Rung(amount);
}

int Get_Current_Weapon_Style(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[w->current];
		return wc->WeaponDef->Style;
	}
	return 0;
}

int Get_Position_Weapon_Style(GameObject *obj, int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position) && (position < w->Vector.Count()))
	{
		WeaponClass *wc = w->Vector[position];
		return wc->WeaponDef->Style;
	}
	return 0;
}

int Get_Weapon_Style(GameObject *obj,const char *weapon)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	int x = w->Vector.Count();
	for (int i = 0;i < x;i++)
	{
		if (w->Vector[i])
		{
			if (!_stricmp(w->Vector[i]->WeaponDef->Get_Name(),weapon))
			{
				WeaponClass *wc = w->Vector[i];
				return wc->WeaponDef->Style;
			}
		}
	}
	return 0;
}

StringClass::StringClass(StringClass& string,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	if (hint_temporary || string.Get_Length())
	{
		Get_String(string.Get_Length()+1,hint_temporary);
	}
	*this = string;
}

StringClass::StringClass(int initial_len,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	Get_String(initial_len,hint_temporary);
	m_Buffer[0] = *m_NullChar;
}

StringClass::~StringClass()
{
	Free_String();
}

StringClass& StringClass::operator=(const char* string)
{
	if (string)
	{
		int x = strlen(string);
		Uninitialised_Grow(x+1);
		Store_Length(x);
		memcpy(m_Buffer,string,x+1);
	}
	return *this;
}

StringClass& StringClass::operator=(StringClass& string)
{
	int x = string.Get_Length();
	Uninitialised_Grow(x+1);
	Store_Length(x);
	memcpy(m_Buffer,string.m_Buffer,x+1);
	return *this;
}

StringClass& StringClass::operator+=(const char* string)
{
	int len = Get_Length();
	int len2 = strlen(string);
	Resize(len+len2+1);
	Store_Length(len+len2);
	memcpy(Get_Buffer(len),string,len2);
	return *this;
}

StringClass& StringClass::operator+=(StringClass& string)
{
	int len = string.Get_Length();
	if (len)
	{
		int len2 = Get_Length();
		Resize(len+len2+1);
		Store_Length(len+len2);
		memcpy(Get_Buffer(len2),string,len+1);
	}
	return *this;
}

int StringClass::Get_Length()
{
	if (!Is_Empty())
	{
		if (!Get_Header()->length)
		{
			Get_Header()->length = strlen(m_Buffer);
		}
		return Get_Header()->length;
	}
	return 0;
}

int cdeclx StringClass::Format(char* format,...)
{
	va_list arg_list;
	va_start(arg_list,format);
	return Format_Args(format,arg_list);
}

int cdeclx StringClass::Format_Args(char* format,va_list& arg_list)
{
	char temp_buffer[512];
#ifdef WIN32
	int x = _vsnprintf(temp_buffer,512,format,arg_list);
#else 
	int x = vsnprintf(temp_buffer,512,format,arg_list);
#endif
	*this = (const char *)temp_buffer;
	return x;
}

void StringClass::Get_String(int length,bool is_temp)
{
	if (!is_temp && !length)
	{
		m_Buffer = *m_EmptyString;
	}
	if (is_temp && (length <= 0xF8) && (*ReservedMask != 0xFF))
	{
		char *c = 0;
		m_Mutex->Lock();
		unsigned int i;
		for (i = 0;i < 8;i++)
		{
			if (!(*ReservedMask & (1 << i)))
			{
				break;
			}
		}
		if (i < 8)
		{
			*ReservedMask |= (1 << i);
			unsigned int x = (unsigned int)&m_TempStrings[0x800];
			x &= -0x800;
			c = (char *)x + (i << 8) + 8;
			Free_String();
			Set_Buffer_And_Allocated_Length(c,0xF8);
		}
		m_Mutex->Unlock();
		if (c)
		{
			return;
		}
	}
	if (length > 0)
	{
		char *x = Allocate_Buffer(length);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,length);
	}
	else
	{
		Free_String();
	}
}

void StringClass::Resize(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		char *x = Allocate_Buffer(new_len);
		strcpy(x,m_Buffer);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void StringClass::Uninitialised_Grow(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		char *x = Allocate_Buffer(new_len);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void StringClass::Free_String()
{
	if (!Is_Empty())
	{
		int x = (int)Get_Header();
		int y = (int)&m_TempStrings[0x800];
		int z = x ^ y;
		if ((z > 0) && (z < 0x800))
		{
			m_Buffer[0] = 0;
			m_Mutex->Lock();
			int x = ((int)Get_Header()) >> 8;
			char c = (char)(x & 7);
			int y = -(1 << c);
			*ReservedMask &= y;
			m_Mutex->Unlock();
			m_Buffer = *m_EmptyString;
		}
		else
		{
			delete Get_Header();
			m_Buffer = *m_EmptyString;
		}
	}
}

void StringClass::Store_Length(int length)
{
	if (!Is_Empty())
	{
		Get_Header()->length = length;
	}
}

void StringClass::Release_Resources()
{
	Free_String();
}

bool StringClass::Copy_Wide(const wchar_t *str)
{
	if (!str)
	{
		return false;
	}
	mbstate_t ps;
	memset(&ps,0,sizeof(ps));
	int len = wcsrtombs(0,&str,0,&ps);
	if (len > 0)
	{
		Uninitialised_Grow(len+1);
		wcsrtombs(m_Buffer,&str,len,&ps);
		m_Buffer[len] = 0;
		return true;
	}
	return false;
}

const char *Get_Powerup_Weapon_By_Obj(GameObject *Powerup)
{
	DefinitionClass *powerupdef = Get_Definition(Powerup);
	char *c = (char *)powerupdef;
	if (!c)
	{
		return "None";
	}
#ifdef RH8
	c += 0xC0;
#else
	c += 0xC4;
#endif
	unsigned long weapondefid = (unsigned long)*(unsigned long *)c;
	if (weapondefid)
	{
		DefinitionClass *weapondef = Find_Definition(weapondefid,1);
		return weapondef->Get_Name();
	}
	return "None";
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

void Create_Effect_All_Of_Preset(const char *object,const char *preset,float ZAdjust,bool ZSet)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj)
		{
			if (!_stricmp(preset,Commands->Get_Preset_Name(obj)))
			{
				Vector3 ObjPosition = Commands->Get_Position(obj);
				if (ZSet)
				{
					ObjPosition.Z = ZAdjust;
				}
				else
				{
					ObjPosition.Z += ZAdjust;
				}
				GameObject *o = Commands->Create_Object(object,ObjPosition);
				Commands->Set_Facing(o,Commands->Get_Facing(obj));
			}
		}
		x = x->NodeNext;
	}
}

float Steal_Team_Credits(float percentage, int team)
{
	float theft = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{			
			if (Commands->Is_A_Star(o))
			{
				int test = Commands->Get_Player_Type(o);
				if (test == team)
				{
					float credits = Commands->Get_Money(o);
					credits = credits * percentage;
					theft += credits;
					Commands->Give_Money(o, -credits, false);
				}
			}
		}
		x = x->NodeNext;
	}
	return theft;
}

GameObject *Find_Nearest_Preset(Vector3 position, const char *preset)
{
	GameObject *object = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if (!_stricmp(Commands->Get_Preset_Name(o),preset))
			{
				if (object)
				{
					Vector3 obj_pos = Commands->Get_Position(object);
					Vector3 o_pos = Commands->Get_Position(o);
					if (Commands->Get_Distance(position, o_pos) < Commands->Get_Distance(position, obj_pos))
					{
						object = o;
					}
				}
				else
				{
					object = o;
				}
			}
		}
		x = x->NodeNext;
	}
	return object;
}

GameObject *Find_Random_Preset(const char* preset, int min, int max)
{
	int count = Commands->Get_Random_Int(min, max);
	GameObject *object = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (count > 0)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if (!_stricmp(Commands->Get_Preset_Name(o),preset))
			{
				object = o;
				count--;
			}
		}
		x = x->NodeNext;
		if (!x)
		{
			if (object)
			{
				x = BaseGameObjList->HeadNode;
			}
			else
			{
				return object;
			}
		}
	}
	return object;
}

void Ranged_Stealth_On_Team(Gap_ListNode* FirstNode)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	if (FirstNode)
	{
		while (x)
		{
			GameObject *o = (GameObject *)x->NodeData;
			if (o)
			{
				bool tested = false;
				Gap_ListNode *current = FirstNode;
				int test = Commands->Get_Player_Type(o);
				if (!(Is_Script_Attached(o, "JFW_Stealth_Generator_Ignored")))
				{
					if (Is_Vehicle(o) || Is_Soldier(o))
					{
						while (!tested)
						{
							if (current)
							{
								if (current->active)
								{
									Vector3 GenPos = Commands->Get_Position(Commands->Find_Object(current->unitID));
									Vector3 TargetPos = Commands->Get_Position(o);
									float distance = Commands->Get_Distance(GenPos, TargetPos);
									if (distance <= current->range)
									{
										if (test == current->teamID)
										{
											Commands->Enable_Stealth(o, true);
											current = NULL;
											tested = true;
										}
										else
										{
											current = current->Next;
										}
									}
									else
									{
										current = current->Next;
									}
								}
								else
								{
									current = current->Next;
								}
							}
							else
							{
								Commands->Enable_Stealth(o, false);
								current = NULL;
								tested = true;
							}
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
	else
	{
		while (x)
		{
			GameObject *o = (GameObject *)x->NodeData;
			if (o)
			{
				if (!(Is_Script_Attached(o, "JFW_Stealth_Generator_Ignored")))
				{
					if (Is_Vehicle(o) || Is_Soldier(o))
					{
						Commands->Enable_Stealth(o, false);
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

void Send_Custom_All_Players(int message,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x) 
	{
		GameObject *obj = (GameObject *)x->NodeData;
		if (obj && Commands->Is_A_Star(obj))
		{
			if ((Get_Object_Type(obj) == team) || (team == 2))
			{
				Commands->Send_Custom_Event(sender,obj,message,0,0);
			}
		}
		x = x->NodeNext;
	}
}

void Ranged_Gap_Effect(Gap_ListNode* FirstNode)
{
	GenericSLNode *x = SmartGameObjList->HeadNode;
	if (FirstNode)
	{
		while (x)
		{
			GameObject *o = (GameObject *)x->NodeData;
			if (o)
			{
				bool stealth = false;
				bool blackout = false;
				Gap_ListNode *current = FirstNode;
				int test = Commands->Get_Player_Type(o);
				if (!(Is_Script_Attached(o, "RA_Gap_Generator_Ignored")))
				{
					if (Is_Vehicle(o) || Is_Soldier(o))
					{
						while (current)
						{
							if (current->active)
							{
								Vector3 GenPos = Commands->Get_Position(Commands->Find_Object(current->unitID));
								Vector3 TargetPos = Commands->Get_Position(o);
								float distance = Commands->Get_Distance(GenPos, TargetPos);
								if (distance <= current->range)
								{
									if (test == current->teamID)
									{
										stealth = true;
									}
									else
									{
										blackout = true;
									}
								}
							}
							current = current->Next;
						}
						Commands->Enable_Stealth(o, stealth);
						if (Commands->Is_A_Star(o))
						{
							if (blackout)
							{
								Commands->Send_Custom_Event(0,o,325523,1,0);
							}
							else
							{
								Commands->Send_Custom_Event(0,o,325523,0,0);
							}
						}
						current = NULL;
					}
				}
			}
			x = x->NodeNext;
		}
	}
	else
	{
		while (x)
		{
			GameObject *o = (GameObject *)x->NodeData;
			if (o)
			{
				if (!(Is_Script_Attached(o, "RA_Gap_Generator_Ignored")))
				{
					if (Is_Vehicle(o) || Is_Soldier(o))
					{
						Commands->Enable_Stealth(o, false);
						if (Commands->Is_A_Star(o))
						{
							Commands->Send_Custom_Event(0,o,325523,0,0);
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}

AmmoDefinitionClass *Get_Weapon_Ammo_Definition(const char *weapon,bool PrimaryFire)
{
	WeaponDefinitionClass *d = (WeaponDefinitionClass *)Find_Named_Definition(weapon);
	if (d)
	{
		if (PrimaryFire)
		{
			unsigned long AmmoID = d->PrimaryAmmoDefID;
			AmmoDefinitionClass *AmmoDef = (AmmoDefinitionClass*)Find_Definition(AmmoID,1);
			return AmmoDef;
		}
		else
		{
			unsigned long AmmoID = d->SecondaryAmmoDefID;
			AmmoDefinitionClass *AmmoDef = (AmmoDefinitionClass*)Find_Definition(AmmoID,1);
			return AmmoDef;
		}
	}
	return 0;
}

AmmoDefinitionClass *GetWeapAmmoDef(WeaponClass *wc,bool PrimaryFire)
{
	if (PrimaryFire)
	{
		return wc->AmmoDef1;
	}
	else
	{
		return wc->AmmoDef2;
	}
}

AmmoDefinitionClass *Get_Current_Weapon_Ammo_Definition(GameObject *obj,bool PrimaryFire)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return GetWeapAmmoDef(w->Vector[w->current],PrimaryFire);
	}
	return 0;
}

AmmoDefinitionClass *Get_Position_Weapon_Ammo_Definition(GameObject *obj,int position,bool PrimaryFire)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position < w->Vector.Count()) && (w->Vector[w->current]))
	{
		return GetWeapAmmoDef(w->Vector[w->current],PrimaryFire);
	}
	return 0;
}

WeaponDefinitionClass *Get_Current_Weapon_Definition(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((w->current) && (w->current < w->Vector.Count()))
	{
		return *(WeaponDefinitionClass **)w->Vector[w->current];
	}
	return 0;
}

WeaponDefinitionClass *Get_Weapon_Definition(const char *weapon)
{
	return (WeaponDefinitionClass *)Find_Named_Definition(weapon);
}

WeaponDefinitionClass *Get_Position_Weapon_Definition(GameObject *obj,int position)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_ArmedGameObj(obj);
	if (!o)
	{
		return 0;
	}
	WeaponBagClass *w = *(WeaponBagClass **)(o+0x7B0);
	if ((position < w->Vector.Count()) && (w->Vector[w->current]))
	{
		return *(WeaponDefinitionClass **)w->Vector[w->current];
	}
	return 0;
}

ExplosionDefinitionClass *Get_Explosion(const char *explosion)
{
	return (ExplosionDefinitionClass *)Find_Named_Definition(explosion);
}

const char *Get_Translated_Definition_Name(const char *preset)
{
	DamageableGameObjDef *d = (DamageableGameObjDef *)Find_Named_Definition(preset);
	if (!d)
	{
		return "";
	}
	return Get_Translated_String(d->TranslatedNameID);
}

WideStringClass::WideStringClass(WideStringClass& string,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	if (hint_temporary || string.Get_Length())
	{
		Get_String(string.Get_Length()+1,hint_temporary);
	}
	*this = string;
}

WideStringClass::WideStringClass(int initial_len,bool hint_temporary)
{
	m_Buffer = *m_EmptyString;
	Get_String(initial_len,hint_temporary);
	m_Buffer[0] = *m_NullChar;
}

WideStringClass::~WideStringClass()
{
	Free_String();
}

WideStringClass& WideStringClass::operator=(const wchar_t* string)
{
	if (string)
	{
		int x = wcslen(string);
		Uninitialised_Grow(x+1);
		Store_Length(x);
		memcpy(m_Buffer,string,(x+1)*sizeof(wchar_t));
	}
	return *this;
}

WideStringClass& WideStringClass::operator=(WideStringClass& string)
{
	int x = string.Get_Length();
	Uninitialised_Grow(x+1);
	Store_Length(x);
	memcpy(m_Buffer,string.m_Buffer,(x+1)+sizeof(wchar_t));
	return *this;
}

WideStringClass& WideStringClass::operator+=(const wchar_t* string)
{
	int len = Get_Length();
	int len2 = wcslen(string);
	Resize(len+len2+1);
	Store_Length(len+len2);
	memcpy(Get_Buffer(len),string,len2*sizeof(wchar_t));
	return *this;
}

WideStringClass& WideStringClass::operator+=(WideStringClass& string)
{
	int len = string.Get_Length();
	if (len)
	{
		int len2 = Get_Length();
		Resize(len+len2+1);
		Store_Length(len+len2);
		memcpy(Get_Buffer(len2),string,(len+1)*sizeof(wchar_t));
	}
	return *this;
}

int WideStringClass::Get_Length()
{
	if (!Is_Empty())
	{
		if (!Get_Header()->length)
		{
			Get_Header()->length = wcslen(m_Buffer);
		}
		return Get_Header()->length;
	}
	return 0;
}

int cdeclx WideStringClass::Format(wchar_t* format,...)
{
	va_list arg_list;
	va_start(arg_list,format);
	return Format_Args(format,arg_list);
}

int cdeclx WideStringClass::Format_Args(wchar_t* format,va_list& arg_list)
{
	wchar_t temp_buffer[512];
	int x = vswprintf(temp_buffer,512,format,arg_list);
	*this = (const wchar_t *)temp_buffer;
	return x;
}

void WideStringClass::Get_String(int length,bool is_temp)
{
	if (!is_temp && !length)
	{
		m_Buffer = *m_EmptyString;
	}
	if (is_temp && (length <= 0xFF) && (*m_UsedTempStringCount <= 3))
	{
		m_TempMutex->Lock();
		for (unsigned int i = 0;i < 3;i++)
		{
			if (m_FreeTempPtr[i])
			{
				m_ResTempPtr[i] = m_FreeTempPtr[i];
				m_FreeTempPtr[i] = 0;
				Free_String();
				Set_Buffer_And_Allocated_Length(m_ResTempPtr[i],0x100);
				m_UsedTempStringCount++;
			}
		}
		m_TempMutex->Unlock();
	}
	else
	{
		wchar_t *x = Allocate_Buffer(length);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,length);
	}
}

void WideStringClass::Resize(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		wchar_t *x = Allocate_Buffer(new_len);
		wcscpy(x,m_Buffer);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void WideStringClass::Uninitialised_Grow(int new_len)
{
	if (new_len > Get_Allocated_Length())
	{
		wchar_t *x = Allocate_Buffer(new_len);
		Free_String();
		Set_Buffer_And_Allocated_Length(x,new_len);
	}
}

void WideStringClass::Free_String()
{
	if (!Is_Empty())
	{
		bool temp = false;
		for (int i = 0;i < 3;i++)
		{
			if (m_Buffer == m_ResTempPtr[i])
			{
				m_TempMutex->Lock();
				m_Buffer[0] = 0;
				m_FreeTempPtr[i] = m_Buffer;
				m_ResTempPtr[i] = 0;
				*m_UsedTempStringCount--;
				temp = true;
				m_TempMutex->Unlock();
				break;
			}
		}
		if (!temp)
		{
			delete Get_Header();
		}
		m_Buffer = *m_EmptyString;
	}
}

void WideStringClass::Store_Length(int length)
{
	if (!Is_Empty())
	{
		Get_Header()->length = length;
	}
}

void WideStringClass::Release_Resources()
{
}

bool WideStringClass::Convert_From(const char *str)
{
	if (!str)
	{
		return false;
	}
	mbstate_t ps;
	memset(&ps,0,sizeof(ps));
	int len = mbsrtowcs(0,&str,0,&ps);
	if (len > 0)
	{
		Uninitialised_Grow(len+1);
		mbsrtowcs(m_Buffer,&str,len,&ps);
		Get_Header()->length = len;
		m_Buffer[len] = 0;
		return true;
	}
	return false;
}

bool WideStringClass::Is_ANSI()
{
	if (m_Buffer)
	{
		if (m_Buffer[0])
		{
			wchar_t *temp = m_Buffer;
			do
			{
				if (*temp > 0xFF)
				{
					return false;
				}
			} while (*temp);
		}
	}
	return true;
}

const wchar_t *CharToWideChar(const char *str)
{
	int length = strlen(str);
	wchar_t *text = new wchar_t[length+1];
	mbstowcs(text,str,length+1);
	return text;
}

#include "enginegm.cpp"

