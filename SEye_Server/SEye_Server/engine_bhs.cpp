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
#include "scripts.h"
#include "engine_common.h"
#include "engine_vector.h"
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_io.h"
#include "engine_net.h"
#include "engine_math.h"
#include "engine_def.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_game.h"
#include "engine_bhsdef.h"
#include "engine_bhs.h"
#include "engine_script.h"
#include "engine_obj2.h"

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
asn AddShaderNotify;
rsn RemoveShaderNotify;
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
ssn2 Set_Shader_Number_Vector;
shn Send_HUD_Number;
sfd Set_Fog_Density;
sfdp Set_Fog_Density_Player;
ctr Change_Time_Remaining;
ctl Change_Time_Limit;
dps Display_GDI_Sidebar;
dps Display_NOD_Sidebar;
dps Display_Security_Dialog;
geo GetExplosionObj;

bool Can_Team_Build_Vehicle(int Team)
{
	if (Is_Currently_Building(Team))
	{
		return false;
	}
	GameObject *factory = Find_Vehicle_Factory(Team);
	if (factory && !Is_Building_Dead(factory))
	{
		return IsAvailableForPurchase(factory);
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
