/*	Renegade Scripts.dll
	Main loading code
	Copyright 2007 Datalore, Jonathan Wilson, Whitedragon(MDB)

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include "Winsock2.h"
#include <windows.h>
#endif
#include "scripts.h"
#include "engine.h"
#include "gmmain.h"
#include "plugin.h"
#ifndef WIN32
#include <dlfcn.h>
#include <time.h>
#endif
#ifdef WIN32
#define SCRIPTSAPI __declspec(dllexport)
#else
#define SCRIPTSAPI
#endif
ScriptCommandsClass Commands;
#ifdef WIN32
HMODULE bhs;
int __cdecl __CxxSetUnhandledExceptionFilter(void);
FARPROC GetProcAddressCheck(HMODULE hModule,LPCSTR lpProcName)
{
	FARPROC x = GetProcAddress(hModule,lpProcName);
	if (!x)
	{
		MessageBox(HWND_DESKTOP,"Error getting function address from bhs.dll",lpProcName,MB_OK|MB_ICONEXCLAMATION);
	}
	return x;
}
#define Address GetProcAddressCheck
#else
#define Address dlsym
void *bhs;
#endif

extern "C" {

#ifdef WIN32
BOOL SCRIPTSAPI __stdcall DllMain(HINSTANCE hinstDLL,
						DWORD	ul_reason_for_call,
						LPVOID	lpReserved
					)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDLL);
			if (Exe == 6)
			{
				InitEngine();
			}
			InitEngineSSGM();
			break;
		case DLL_PROCESS_DETACH:
#if DEBUG
			m_dumpMemoryReport("memreport_scripts.log",false);
#endif
			break;
	}
	return TRUE;
}
#endif

ScriptClass SCRIPTSAPI *Create_Script(const char *ScriptName)
{
	if (!ScriptName)
	{
		return 0;
	}
	return ScriptRegistrar::CreateScript(ScriptName);
}

bool SCRIPTSAPI Set_Script_Commands(ScriptCommandsClass *ScriptCommands)
{
	Commands = *ScriptCommands;
	if ((Commands->version1 != 816) || (Commands->version2 != 174)) //if these dont match it means the ScriptCommands dont match with what is expected and the DLL cant work with whatever client is trying to use it
	{
		return false;
	}
	Commands->Enable_Stealth = (_Enable_Stealth)Address(bhs,"New_Enable_Stealth");
	Commands->Create_Explosion = (_Create_Explosion)Address(bhs,"New_Create_Explosion");
	Commands->Create_Explosion_At_Bone = (_Create_Explosion_At_Bone)Address(bhs,"New_Create_Explosion_At_Bone");
	Commands->Set_Fog_Enable = (_Set_Fog_Enable)Address(bhs,"New_Set_Fog_Enable");
	Commands->Set_Fog_Range = (_Set_Fog_Range)Address(bhs,"New_Set_Fog_Range");
	Commands->Set_War_Blitz = (_Set_War_Blitz)Address(bhs,"New_Set_War_Blitz");
	Commands->Fade_Background_Music = (_Fade_Background_Music)Address(bhs,"New_Fade_Background_Music");
	Commands->Set_Background_Music = (_Set_Background_Music)Address(bhs,"New_Set_Background_Music");
	Commands->Stop_Background_Music = (_Stop_Background_Music)Address(bhs,"New_Stop_Background_Music");
	Commands->Create_Sound = (_Create_Sound)Address(bhs,"New_Create_Sound");
	Commands->Create_2D_Sound = (_Create_2D_Sound)Address(bhs,"New_Create_2D_Sound");
	Commands->Create_2D_WAV_Sound = (_Create_2D_WAV_Sound)Address(bhs,"New_Create_2D_WAV_Sound");
	Commands->Create_3D_WAV_Sound_At_Bone = (_Create_3D_WAV_Sound_At_Bone)Address(bhs,"New_Create_3D_WAV_Sound_At_Bone");
	Commands->Create_3D_Sound_At_Bone = (_Create_3D_Sound_At_Bone)Address(bhs,"New_Create_3D_Sound_At_Bone");
	Commands->Play_Building_Announcement = (_Play_Building_Announcement)Address(bhs,"New_Play_Building_Announcement");
	Commands->Clear_Weapons = (_Clear_Weapons)Address(bhs,"New_Clear_Weapons");
	Commands->Enable_Vehicle_Transitions = (_Enable_Vehicle_Transitions)Address(bhs,"New_Enable_Vehicle_Transitions");
	Commands->Set_Player_Type = (_Set_Player_Type)Address(bhs,"New_Set_Player_Type");
	Commands->Set_Screen_Fade_Color = (_Set_Screen_Fade_Color)Address(bhs,"New_Set_Screen_Fade_Color");
	Commands->Set_Screen_Fade_Opacity = (_Set_Screen_Fade_Opacity)Address(bhs,"New_Set_Screen_Fade_Opacity");
	Commands->Set_Display_Color = (_Set_Display_Color)Address(bhs,"New_Set_Display_Color");
	Commands->Display_Text = (_Display_Text)Address(bhs,"New_Display_Text");
	Commands->Display_Float = (_Display_Float)Address(bhs,"New_Display_Float");
	Commands->Display_Int = (_Display_Int)Address(bhs,"New_Display_Int");
	Commands->Select_Weapon = (_Select_Weapon)Address(bhs,"New_Select_Weapon");
	Commands->Shake_Camera = (_Shake_Camera)Address(bhs,"New_Shake_Camera");
	Commands->Set_Model = (_Set_Model)Address(bhs,"New_Set_Model");
	Enable_Stealth_Player = (_Enable_Stealth_Player)Address(bhs,"New_Enable_Stealth_Player");
	Set_Fog_Enable_Player = (_Set_Fog_Enable_Player)Address(bhs,"New_Set_Fog_Enable_Player");
	Set_Fog_Range_Player = (_Set_Fog_Range_Player)Address(bhs,"New_Set_Fog_Range_Player");
	Set_Background_Music_Player = (_Set_Background_Music_Player)Address(bhs,"New_Set_Background_Music_Player");
	Fade_Background_Music_Player = (_Fade_Background_Music_Player)Address(bhs,"New_Fade_Background_Music_Player");
	Stop_Background_Music_Player = (_Stop_Background_Music_Player)Address(bhs,"New_Stop_Background_Music_Player");
	Enable_Radar_Player = (_Enable_Radar_Player)Address(bhs,"New_Enable_Radar_Player");
	Display_GDI_Player_Terminal_Player = (_Display_GDI_Player_Terminal_Player)Address(bhs,"New_Display_GDI_Player_Terminal_Player");
	Display_NOD_Player_Terminal_Player = (_Display_NOD_Player_Terminal_Player)Address(bhs,"New_Display_NOD_Player_Terminal_Player");
	Set_Screen_Fade_Color_Player = (_Set_Screen_Fade_Color_Player)Address(bhs,"New_Set_Screen_Fade_Color_Player");
	Set_Screen_Fade_Opacity_Player = (_Set_Screen_Fade_Opacity_Player)Address(bhs,"New_Set_Screen_Fade_Opacity_Player");
	Force_Camera_Look_Player = (_Force_Camera_Look_Player)Address(bhs,"New_Force_Camera_Look_Player");
	Enable_HUD_Player = (_Enable_HUD_Player)Address(bhs,"New_Enable_HUD_Player");
	Create_Sound_Player = (_Create_Sound_Player)Address(bhs,"New_Create_Sound_Player");
	Create_2D_Sound_Player = (_Create_2D_Sound_Player)Address(bhs,"New_Create_2D_Sound_Player");
	Create_2D_WAV_Sound_Player = (_Create_2D_WAV_Sound_Player)Address(bhs,"New_Create_2D_WAV_Sound_Player");
	Create_3D_WAV_Sound_At_Bone_Player = (_Create_3D_WAV_Sound_At_Bone_Player)Address(bhs,"New_Create_3D_WAV_Sound_At_Bone_Player");
	Create_3D_Sound_At_Bone_Player = (_Create_3D_Sound_At_Bone_Player)Address(bhs,"New_Create_3D_Sound_At_Bone_Player");
	Set_Display_Color_Player = (_Set_Display_Color_Player)Address(bhs,"New_Set_Display_Color_Player");
	Display_Text_Player = (_Display_Text_Player)Address(bhs,"New_Display_Text_Player");
	Display_Int_Player = (_Display_Int_Player)Address(bhs,"New_Display_Int_Player");
	Display_Float_Player = (_Display_Float_Player)Address(bhs,"New_Display_Float_Player");
	Commands->Set_Obj_Radar_Blip_Shape = (_Set_Obj_Radar_Blip_Shape)Address(bhs,"New_Set_Obj_Radar_Blip_Shape");
	Commands->Set_Obj_Radar_Blip_Color = (_Set_Obj_Radar_Blip_Color)Address(bhs,"New_Set_Obj_Radar_Blip_Color");
	Set_Obj_Radar_Blip_Shape_Player = (_Set_Obj_Radar_Blip_Shape_Player)Address(bhs,"New_Set_Obj_Radar_Blip_Shape_Player");
	Set_Obj_Radar_Blip_Color_Player = (_Set_Obj_Radar_Blip_Color_Player)Address(bhs,"New_Set_Obj_Radar_Blip_Color_Player");
	AddObjectCreateHook = (aoch)Address(bhs,"NewAddObjectCreateHook");
	RemoveObjectCreateHook = (roch)Address(bhs,"NewRemoveObjectCreateHook");
	AddKeyHook = (akh)Address(bhs,"AddKeyHook");
	RemoveKeyHook = (rkh)Address(bhs,"RemoveKeyHook");
	Set_Scope = (ss)Address(bhs,"Set_Scope");
	Set_HUD_Texture = (sh)Address(bhs,"Set_HUD_Texture");
	AddChatHook = (ach)Address(bhs,"AddChatHook");
	AddHostHook = (ahh)Address(bhs,"AddHostHook");
	AddLoadLevelHook = (allh)Address(bhs,"AddLoadLevelHook");
	AddGameOverHook = (allh)Address(bhs,"AddGameOverHook");
	AddPlayerJoinHook = (apjh)Address(bhs,"AddPlayerJoinHook");
	GetCurrentMusicTrack = (gcmt)Address(bhs,"GetCurrentMusicTrack");
	Set_Info_Texture = (sit)Address(bhs,"Set_Info_Texture");
	Clear_Info_Texture = (cit)Address(bhs,"Clear_Info_Texture");
	Set_Vehicle_Limit = (svl)Address(bhs,"Set_Vehicle_Limit");
	Get_Vehicle_Limit = (gvl)Address(bhs,"Get_Vehicle_Limit");
	Send_Message = (sm)Address(bhs,"Send_Message");
	Send_Message_Player = (smp)Address(bhs,"Send_Message_Player");
	Commands->Display_Health_Bar = (_Display_Health_Bar)Address(bhs,"New_Display_Health_Bar");
	AddVersionHook = (avh)Address(bhs,"AddVersionHook");
	Set_Wireframe_Mode = (sw)Address(bhs,"Set_Wireframe_Mode");
	Commands->Disable_All_Collisions = (_Disable_All_Collisions)Address(bhs,"New_Disable_All_Collisions");
	Commands->Disable_Physical_Collisions = (_Disable_Physical_Collisions)Address(bhs,"New_Disable_Physical_Collisions");
	Commands->Enable_Collisions = (_Enable_Collisions)Address(bhs,"New_Enable_Collisions");
	Load_New_HUD_INI = (lnhi)Address(bhs,"Load_New_HUD_INI");
	Remove_Weapon = (rw)Address(bhs,"Remove_Weapon");
	Update_PT_Data = (upd)Address(bhs,"Update_PT_Data");
	Change_Radar_Map = (crm)Address(bhs,"Change_Radar_Map");
	AddPowerupPurchaseHook = (aph)Address(bhs,"AddPowerupPurchaseHook");
	AddVehiclePurchaseHook = (aph)Address(bhs,"AddVehiclePurchaseHook");
	AddCharacterPurchaseHook = (aph)Address(bhs,"AddCharacterPurchaseHook");
	AddPowerupPurchaseMonHook = (apmh)Address(bhs,"AddPowerupPurchaseMonHook");
	AddVehiclePurchaseMonHook = (apmh)Address(bhs,"AddVehiclePurchaseMonHook");
	AddCharacterPurchaseMonHook = (apmh)Address(bhs,"AddCharacterPurchaseMonHook");
	RemovePowerupPurchaseHook = (rph)Address(bhs,"RemovePowerupPurchaseHook");
	RemoveVehiclePurchaseHook = (rph)Address(bhs,"RemoveVehiclePurchaseHook");
	RemoveCharacterPurchaseHook = (rph)Address(bhs,"RemoveCharacterPurchaseHook");
	RemovePowerupPurchaseMonHook = (rph)Address(bhs,"RemovePowerupPurchaseMonHook");
	RemoveVehiclePurchaseMonHook = (rph)Address(bhs,"RemoveVehiclePurchaseMonHook");
	RemoveCharacterPurchaseMonHook = (rph)Address(bhs,"RemoveCharacterPurchaseMonHook");
	Get_Build_Time_Multiplier = (gbm)Address(bhs,"Get_Build_Time_Multiplier");
	Set_Currently_Building = (scb)Address(bhs,"Set_Currently_Building");
	Is_Currently_Building = (icb)Address(bhs,"Is_Currently_Building");
	AddConsoleOutputHook = (acoh)Address(bhs,"AddConsoleOutputHook");
	AddCRCHook = (acrch)Address(bhs,"AddCRCHook");
	AddDataHook = (adh)Address(bhs,"AddDataHook");
	Set_Reticle_Texture1 = (srt)Address(bhs,"Set_Reticle_Texture1");
	Set_Reticle_Texture2 = (srt)Address(bhs,"Set_Reticle_Texture2");
	Set_Fog_Color = (sfc)Address(bhs,"New_Set_Fog_Color");
	Set_Fog_Color_Player = (sfcp)Address(bhs,"Set_Fog_Color_Player");
	Set_Fog_Mode = (sfm)Address(bhs,"New_Set_Fog_Mode");
	Set_Fog_Mode_Player = (sfmp)Address(bhs,"Set_Fog_Mode_Player");
	Set_Shader_Number = (ssn)Address(bhs,"Set_Shader_Number");
	Set_Fog_Density = (sfd)Address(bhs,"New_Set_Fog_Density");
	Set_Fog_Density_Player = (sfdp)Address(bhs,"Set_Fog_Density_Player");
	Change_Time_Remaining = (ctr)Address(bhs,"New_Change_Time_Remaining");
	Change_Time_Limit = (ctl)Address(bhs,"New_Change_Time_Limit");
	Display_GDI_Sidebar = (dps)Address(bhs,"Display_GDI_Sidebar");
	Display_NOD_Sidebar = (dps)Address(bhs,"Display_NOD_Sidebar");
	Display_Security_Dialog = (dps)Address(bhs,"Display_Security_Dialog");
	AddPlayerLeaveHook = (aplh)Address(bhs,"AddPlayerLeaveHook");
	GetExplosionObj = (geo)Address(bhs,"GetExplosionObj");

	Plugin_Load();

	return true;
}

void SCRIPTSAPI Set_Request_Destroy_Func(rdf Func)
{
	ScriptImpClass::Set_Request_Destroy_Func(Func);
}


//SSGM calls this to get the version of the plugin. It then decides if the plugin should be allowed to load or not.
//You can also return false from this function to stop SSGM from loading the plugin.
//Don't initialize anything here.
SCRIPTSAPI bool SSGM_Check_Version(const char *SSGM_Version,PluginInfo *Info) {
	Info->SSGMVer = SSGMVersion; //Version of SSGM that the plugin is based off of
	Info->SSGMVerRequired = false; //Should this plugin only be allowed to work with this version of SSGM?
	return true;
}


//SSGM will call this function when it attempts to load the plugin. The handle to bhs.dll, the settings struct, the data struct, the version of SSGM, and a pointer to the struct that holds the information about the plugin will be passed to it.
//SSGM expects the Name, Version, SSGMVer, and SSGMVerRequired fields to be filled in.
#ifdef WIN32
__declspec(dllexport) void SSGM_Plugin_Load(HMODULE BHS,SettingsStruct *SSGM_Settings,DataStruct *SSGM_Data,const char *SSGM_Version,PluginInfo *Info) {
#else 
void SSGM_Plugin_Load(void *BHS,SettingsStruct *SSGM_Settings,DataStruct *SSGM_Data,const char *SSGM_Version,PluginInfo *Info) {
#ifdef RH8
	Exe = 3;
#else
	Exe = 2;
#endif
	InitEngine();
	InitEngineSSGM();
#endif

	//These are defined in plugin.h by default
	Info->Name = PluginName;
	Info->Version = PluginVersion;

	bhs = BHS;
	Settings = SSGM_Settings;
	Data = SSGM_Data;

	//Add our chat commands to the master list
	if (ChatCommandList::List) {
		Data->Copy_Chat_Commands(ChatCommandList::List);
	}
}


//Called when SSGM is unloaded. Good place to free memory.
SCRIPTSAPI void SSGM_Plugin_Unload() {
	if (ChatCommandList::List) {
		std::vector<ChatCommandInfo*>::const_iterator it;
		for (it = ChatCommandList::List->begin(); it != ChatCommandList::List->end(); ++it) {
			if (*it) {
				delete (*it)->Ptr;
				delete *it;
			}
		}
		ChatCommandList::List->clear();
		delete ChatCommandList::List;
	}
	Plugin_Unload();
}



}



