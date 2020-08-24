/*	Renegade Scripts.dll
	Definitions and code related to functions in bhs.dll
	Copyright 2007 Jonathan Wilson, Mark Sararu, Joshua "NeoSaber" Kraft

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//start per-player script commands stuff
typedef void (*_Enable_Stealth_Player) (GameObject *obj,GameObject *obj2,bool enable);
typedef void (*_Set_Fog_Enable_Player) (GameObject *obj,bool enable);
typedef void (*_Set_Fog_Range_Player) (GameObject *obj,float Start_Distance,float End_Distance,float transition);
typedef void (*_Set_Background_Music_Player) (GameObject *obj,const char *music);
typedef void (*_Fade_Background_Music_Player) (GameObject *obj,const char *music,int unk1,int unk2);
typedef void (*_Stop_Background_Music_Player) (GameObject *obj);
typedef void (*_Enable_Radar_Player) (GameObject *obj,bool enable);
typedef void (*_Display_GDI_Player_Terminal_Player) (GameObject *obj);
typedef void (*_Display_NOD_Player_Terminal_Player) (GameObject *obj);
typedef void (*_Set_Screen_Fade_Color_Player) (GameObject *obj,float red,float green,float blue,float transition);
typedef void (*_Set_Screen_Fade_Opacity_Player) (GameObject *obj,float opacity,float transition);
typedef void (*_Force_Camera_Look_Player) (GameObject *obj,const Vector3 & look);
typedef void (*_Enable_HUD_Player) (GameObject *obj,bool enable);
typedef int (*_Create_Sound_Player) (GameObject *obj,const char *soundname,const Vector3 & position,GameObject *obj2);
typedef int (*_Create_2D_Sound_Player) (GameObject *obj,const char *soundname);
typedef int (*_Create_2D_WAV_Sound_Player) (GameObject *obj,const char *soundname);
typedef int (*_Create_3D_WAV_Sound_At_Bone_Player) (GameObject *obj,const char *soundname,GameObject *obj2,const char *bonename);
typedef int (*_Create_3D_Sound_At_Bone_Player) (GameObject *obj,const char *soundname,GameObject *obj2,const char *bonename);
typedef void (*_Set_Display_Color_Player) (GameObject *obj,unsigned char red,unsigned char green,unsigned char blue);
typedef void (*_Display_Text_Player) (GameObject *obj,int strnum);
typedef void (*_Display_Int_Player) (GameObject *obj,int num,const char *msg);
typedef void (*_Display_Float_Player) (GameObject *obj,float num,const char *msg);
typedef void (*_Set_Obj_Radar_Blip_Shape_Player) (GameObject *obj,GameObject *obj2,int shape);
typedef void (*_Set_Obj_Radar_Blip_Color_Player) (GameObject *obj,GameObject *obj2,int color);
typedef int (*aoch) (ObjectCreateHookStruct *h);
typedef void (*roch) (int pos);
typedef int (*akh) (KeyHookStruct *h);
typedef void (*rkh) (int pos);
typedef void (*ss) (GameObject *obj,int scope);
typedef void (*sh) (GameObject *obj,const char *texture);
typedef void (*ach) (ChatHook h);
typedef void (*avh) (BHSVersion h);
typedef void (*ahh) (HostHook h);
typedef void (*allh) (LoadLevelHook h);
typedef int (*aph) (PurchaseHook h,const char *data);
typedef int (*apmh) (PurchaseMonHook h,const char *data);
typedef void (*rph) (int pos);
typedef void (*apjh) (PlayerJoin h);
typedef void (*aplh) (PlayerLeave h);
typedef const char *(*gcmt) ();
typedef double (*gbhsv) ();
typedef void (*sit) (GameObject *obj,const char *texture);
typedef void (*cit) (GameObject *obj);
typedef void (*svl) (unsigned int limit);
typedef unsigned long (*gvl) ();
typedef void (*sm) (unsigned int red,unsigned int green,unsigned int blue, const char *msg);
typedef void (*smp) (GameObject *obj,unsigned int red,unsigned int green,unsigned int blue, const char *msg);
typedef void (*sw) (int mode);
typedef void (*lnhi) (GameObject *obj,const char *ini);
typedef void (*rw) (GameObject *obj,const char *weapon);
typedef void (*upd) ();
typedef void (*crm) (float scale,float offsetx,float offsety,const char *texture);
typedef float (*gbm) (int team);
typedef void (*scb) (bool building,int team);
typedef bool (*icb) (int team);
typedef void (*acoh) (ConsoleOutputHook h);
typedef void (*acrch) (CRCHook h);
typedef void (*adh) (DataHook h);
typedef void (*srt) (GameObject *obj,const char *texture);
typedef void (*sfc) (unsigned int red, unsigned int green, unsigned int blue);
typedef void (*sfcp) (GameObject *obj,unsigned int red, unsigned int green, unsigned int blue);
typedef void (*sfm) (unsigned int mode);
typedef void (*sfmp) (GameObject *obj,unsigned int mode);
typedef void (*sfd) (float density);
typedef void (*sfdp) (GameObject *obj,float density);
typedef void (*ctr) (float time);
typedef void (*ctl) (int time);
typedef void (*dps) (GameObject *obj);
typedef void (*ssn) (GameObject *obj,unsigned int number,float number2);
typedef void (*ssn2) (GameObject *obj,unsigned int number,Vector4 number2);
typedef void (*shn) (GameObject *obj,unsigned int number);
typedef GameObject *(*geo) ();
typedef int (*asn) (ShaderNotifyStruct *s);
typedef int (*rsn) (int pos);
extern asn AddShaderNotify;
extern rsn RemoveShaderNotify;
extern ach AddChatHook;
extern ahh AddHostHook;
extern ss Set_Scope;
extern sh Set_HUD_Texture;
extern aoch AddObjectCreateHook;
extern roch RemoveObjectCreateHook;
extern akh AddKeyHook;
extern rkh RemoveKeyHook;
extern gcmt GetCurrentMusicTrack;
extern allh AddLoadLevelHook;
extern allh AddGameOverHook;
extern apjh AddPlayerJoinHook;
extern aplh AddPlayerLeaveHook;
extern aph AddPowerupPurchaseHook;
extern aph AddVehiclePurchaseHook;
extern aph AddCharacterPurchaseHook;
extern apmh AddPowerupPurchaseMonHook;
extern apmh AddVehiclePurchaseMonHook;
extern apmh AddCharacterPurchaseMonHook;
extern rph RemovePowerupPurchaseHook;
extern rph RemoveVehiclePurchaseHook;
extern rph RemoveCharacterPurchaseHook;
extern rph RemovePowerupPurchaseMonHook;
extern rph RemoveVehiclePurchaseMonHook;
extern rph RemoveCharacterPurchaseMonHook;
extern sit Set_Info_Texture;
extern cit Clear_Info_Texture;
extern _Enable_Stealth_Player Enable_Stealth_Player;
extern _Set_Fog_Enable_Player Set_Fog_Enable_Player;
extern _Set_Fog_Range_Player Set_Fog_Range_Player;
extern _Set_Background_Music_Player Set_Background_Music_Player;
extern _Fade_Background_Music_Player Fade_Background_Music_Player;
extern _Stop_Background_Music_Player Stop_Background_Music_Player;
extern _Enable_Radar_Player Enable_Radar_Player;
extern _Display_GDI_Player_Terminal_Player Display_GDI_Player_Terminal_Player;
extern _Display_NOD_Player_Terminal_Player Display_NOD_Player_Terminal_Player;
extern _Set_Screen_Fade_Color_Player Set_Screen_Fade_Color_Player;
extern _Set_Screen_Fade_Opacity_Player Set_Screen_Fade_Opacity_Player;
extern _Force_Camera_Look_Player Force_Camera_Look_Player;
extern _Enable_HUD_Player Enable_HUD_Player;
extern _Create_Sound_Player Create_Sound_Player;
extern _Create_2D_Sound_Player Create_2D_Sound_Player;
extern _Create_2D_WAV_Sound_Player Create_2D_WAV_Sound_Player;
extern _Create_3D_WAV_Sound_At_Bone_Player Create_3D_WAV_Sound_At_Bone_Player;
extern _Create_3D_Sound_At_Bone_Player Create_3D_Sound_At_Bone_Player;
extern _Set_Display_Color_Player Set_Display_Color_Player;
extern _Display_Text_Player Display_Text_Player;
extern _Display_Int_Player Display_Int_Player;
extern _Display_Float_Player Display_Float_Player;
extern _Set_Obj_Radar_Blip_Shape_Player Set_Obj_Radar_Blip_Shape_Player;
extern _Set_Obj_Radar_Blip_Color_Player Set_Obj_Radar_Blip_Color_Player;
extern svl Set_Vehicle_Limit;
extern gvl Get_Vehicle_Limit;
extern sm Send_Message;
extern smp Send_Message_Player;
extern avh AddVersionHook;
extern sw Set_Wireframe_Mode;
extern lnhi Load_New_HUD_INI;
extern rw Remove_Weapon;
extern upd Update_PT_Data;
extern crm Change_Radar_Map;
extern gbm Get_Build_Time_Multiplier;
extern scb Set_Currently_Building;
extern icb Is_Currently_Building;
extern acoh AddConsoleOutputHook;
extern acrch AddCRCHook;
extern adh AddDataHook;
extern srt Set_Reticle_Texture1;
extern srt Set_Reticle_Texture2;
extern sfc Set_Fog_Color;
extern sfcp Set_Fog_Color_Player;
extern sfm Set_Fog_Mode;
extern sfmp Set_Fog_Mode_Player;
extern ssn Set_Shader_Number;
extern ssn2 Set_Shader_Number_Vector;
extern sfd Set_Fog_Density;
extern sfdp Set_Fog_Density_Player;
extern ctr Change_Time_Remaining;
extern ctl Change_Time_Limit;
extern dps Display_GDI_Sidebar;
extern dps Display_NOD_Sidebar;
extern dps Display_Security_Dialog;
extern shn Send_HUD_Number;
extern geo GetExplosionObj;

class JFW_Key_Hook_Base : public ScriptImpClass {
public:
	KeyHookStruct *k;
	int hookid;
	int is_keyhook_set;
	void Detach(GameObject *obj);
	void Destroyed(GameObject *obj);
	void InstallHook(const char *keyname,GameObject *obj);
	void RemoveHook();
	virtual void KeyHook() = 0;
	~JFW_Key_Hook_Base();
};

class JFW_Object_Created_Hook_Base : public ScriptImpClass {
public:
	int hookid;
	int is_objecthook_set;
	ObjectCreateHookStruct *h;
	void Detach(GameObject *obj);
	void Created(GameObject *obj);
	void InstallHook();
	void RemoveHook();
	virtual void ObjectCreateHook(GameObject *obj) = 0;
	~JFW_Object_Created_Hook_Base();
};

struct Gap_ListNode 
{
	Gap_ListNode* Next;
	unsigned long unitID;
	float range; 
	int teamID;
	bool active;
};

void Set_Occupants_Fade(GameObject *obj,float red,float green,float blue,float opacity); //sets the screen fade of all the occupants of a vehicle
void Enable_Team_Radar(int Team,bool Enable); //enable radar for a given team
void Create_Sound_Team(const char *soundname,const Vector3 & position,GameObject *obj,int team); //play a 3D sound for a team
void Create_2D_Sound_Team(const char *soundname,int team); //play a 2D sound for a team
void Create_2D_WAV_Sound_Team(const char *soundname,int team); //play a 2D WAV sound for a team
void Create_3D_WAV_Sound_At_Bone_Team(const char *soundname,GameObject *obj,const char *bonename,int team); //play a 3D WAV sound at a bone for a team
void Create_3D_Sound_At_Bone_Team(const char *soundname,GameObject *obj,const char *bonename,int team); //play a 3D sound at a bone for a team
void Set_Display_Color_Team(unsigned char red,unsigned char green,unsigned char blue,int team); //set the display color for a team
void Display_Text_Team(int strnum,int team); //display a text string for a team
void Display_Int_Team(int num,const char *msg,int team); //display a message with an int for a team
void Display_Float_Team(float num,const char *msg,int team); //display a message with a float for a team
void Set_Obj_Radar_Blip_Shape_Team(int Team,GameObject *obj,int shape); //set obj radar blip shape for team
void Set_Obj_Radar_Blip_Color_Team(int Team,GameObject *obj,int color); //set obj radar blip color for team 
void Send_Message_Team(int team,unsigned int red,unsigned int green,unsigned int blue,const char *msg); //send a message to a team
void Send_Message_With_Obj_Color(GameObject *obj,const char *Msg); //send a messages in a given objects color
void Send_Message_With_Team_Color(int Team,const char *Msg); //Send a message in a given teams color
void Ranged_Gap_Effect(Gap_ListNode* FirstNode); //apply gap effect to all units of a team within a range
void Ranged_Stealth_On_Team(Gap_ListNode* FirstNode); //Apply stealth to all units in the range of this on the relavent team
bool Can_Team_Build_Vehicle(int Team); //Can this team build vehicles
