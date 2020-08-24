/*	Renegade Scripts.dll
	Base scripts header
	Copyright 2007 Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#ifdef WIN32
#ifndef _MSC_VER
#error The renegade scripts.dll requires Microsoft Visual C++ in order to work
#endif
#elif (__GNUC__ == 3)
#ifndef RH8
#error You must use GCC 2.9x for RH7
#endif
#elif (__GNUC__ == 2)
#ifdef RH8
#error You must use GCC 3.x for RH8
#endif
#else
#error Invalid GCC version, use GCC 2.9x for RH7 and 3.x for RH8
#endif

#pragma warning (disable: 4100 4800 4740 4731 4733 6054 6211 6320)
#ifndef WIN32
#define _stricmp strcasecmp
#define _wcsicmp wcscasecmp
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <errno.h>
#include <wchar.h>
#ifdef DEBUG
#include "mmgr.h"
#endif
typedef unsigned char GameObject;
typedef unsigned char ScriptSaver;
typedef unsigned char ScriptLoader;
class ScriptFactory;
class ScriptClass;
typedef void (*rdf) (ScriptClass *scr);

typedef enum {
	ACTION_COMPLETE_ATTACK_OUT_OF_RANGE = 1,
	ACTION_COMPLETE_MOVE_NO_PROGRESS_MADE = 2,
	ACTION_COMPLETE_PATH_BAD_DEST = 3,
	ACTION_COMPLETE_PATH_BAD_START = 4,
	ACTION_COMPLETE_LOW_PRIORITY = 5,
	ACTION_COMPLETE_NORMAL = 6
} ActionCompleteReason;

struct SeralizeInfoStr {
	void *data;
	int size;
	int number;
	SeralizeInfoStr *next;
};

struct Vector3 {
	float X;
	float Y;
	float Z;
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Vector3& operator *= (Vector3&);
	Vector3& operator /= (Vector3&);
	Vector3& operator += (Vector3&);
	Vector3& operator -= (Vector3&);
	Vector3& operator *= (float);
	Vector3& operator /= (float);
	Vector3 operator * (const Vector3&) const;
	Vector3 operator / (const Vector3&) const;
	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator * (float) const;
	Vector3 operator / (float) const;
	void Normalize();
	static Vector3 Normalize(Vector3);
	float Dot(Vector3);
	static float Dot(Vector3,Vector3);
	Vector3 Cross(Vector3);
	static Vector3 Cross(Vector3,Vector3);
};

struct CombatSound {
	Vector3 position; //this is passed from the position parameter of Create_Logical_Sound
	int sound; //this is passed from the sound parameter of Create_Logical_Sound
	GameObject *obj; //this is passed from the obj parameter of Create_Logical_Sound
};

class GameObjObserverClass {
protected:
	int ObserverID;
public:
	virtual ~GameObjObserverClass();
	virtual char *Get_Name() = 0;
	virtual void Attach(GameObject *newobj) = 0;
	virtual void Detach(GameObject *obj) = 0;
	virtual void Created(GameObject *obj) = 0;
	virtual void Destroyed(GameObject *obj) = 0;
	virtual void Killed(GameObject *obj,GameObject *shooter) = 0;
	virtual void Damaged(GameObject *obj,GameObject *damager,float damage) = 0;
	virtual void Custom(GameObject *obj,int message,int param,GameObject *sender) = 0;
	virtual void Sound_Heard(GameObject *obj,const CombatSound & sound) = 0;
	virtual void Enemy_Seen(GameObject *obj,GameObject *seen) = 0;
	virtual void Action_Complete(GameObject *obj,int action,ActionCompleteReason reason) = 0;
	virtual void Timer_Expired(GameObject *obj,int number) = 0;
	virtual void Animation_Complete(GameObject *obj,const char *anim) = 0;
	virtual void Poked(GameObject *obj,GameObject *poker) = 0;
	virtual void Entered(GameObject *obj,GameObject *enter) = 0;
	virtual void Exited(GameObject *obj,GameObject *exit) = 0;
	int GetID()
	{
		return ObserverID;
	}
};

class ScriptClass : public GameObjObserverClass {
};

class ScriptImpClass : public ScriptClass {
private:
	GameObject *Attached;
	int mArgC;
	char **mArgV;
	ScriptFactory *Factory;
	SeralizeInfoStr *seralizeinfo;
	static rdf RequestDestroyScript;
public:
	static void Set_Request_Destroy_Func(rdf Func);
	void SetFactory(ScriptFactory *ptr)
	{
		Factory = ptr;
	}
	ScriptImpClass();
	void Destroy_Script();
	int CheckPlayerType(GameObject *obj,int type);
	void Auto_Save_Variable(int number,int size,void *var);
	~ScriptImpClass();
	char *Get_Name();
	void Attach(GameObject *newobj);
	void Detach(GameObject *obj);
	void Created(GameObject *obj); //triggers on script creation
	void Destroyed(GameObject *obj); //triggers on script shutdown
	void Killed(GameObject *obj,GameObject *shooter); //triggers when the object script is attached to dies
	void Damaged(GameObject *obj,GameObject *damager,float damage); //triggers when the object script is attached to is damaged. The damager is always the gunner,not the vechicle.
	void Custom(GameObject *obj,int message,int param,GameObject *sender); //triggers when the script is sent a custom (aka message). Several system events are triggered by Customs as well,see the #defines below
	void Sound_Heard(GameObject *obj,const CombatSound & sound); //something to do with sound,I think it triggers when the object the script is attached to hears a sound)
	void Enemy_Seen(GameObject *obj,GameObject *seen); //triggers when the object script is attached to spots an enemy
	void Action_Complete(GameObject *obj,int action,ActionCompleteReason reason); //triggers when an action on the object the script is attached to completes
	void Timer_Expired(GameObject *obj,int number); //triggers when a timer goes off
	void Animation_Complete(GameObject *obj,const char *anim); //triggers when an animation on the object the script is attached to completes
	void Poked(GameObject *obj,GameObject *poker); //triggers when the object that this scripts is attached to is poked (i.e. player pushes the action key while this object is active),this doesnt work in MP unless you have bhs.dll
	void Entered(GameObject *obj,GameObject *enter); //triggers when the zone this script is attached to is entered
	void Exited(GameObject *obj,GameObject *exit); //triggers when the zone this script is attached to is exited
	virtual GameObject *Owner();
	virtual GameObject **Get_Owner_Ptr();
	virtual void Set_Parameters_String(const char *params);
	virtual void Get_Parameters_String(char *params,unsigned int size);
	virtual void Save(ScriptSaver &saver);
	virtual void Load(ScriptLoader &loader);
	virtual void Save_Data(ScriptSaver &saver);
	virtual void Load_Data(ScriptLoader &loader);
	virtual void Register_Auto_Save_Variables();
	void Clear_Parameters();
	const char *Get_Parameter(const char *v);
	const char *Get_Parameter(int v);
	int Get_Int_Parameter(const char *v);
	float Get_Float_Parameter(const char *v);
	Vector3 Get_Vector3_Parameter(int v);
	Vector3 Get_Vector3_Parameter(const char *v);
	int Get_Parameter_Index(const char *v);
	int Get_Parameter_Count();
	int Get_Int_Parameter(int v);
	float Get_Float_Parameter(int v);
	void Set_Parameter(int pos,char const *v);
};

class ActionParamsStruct {
public:
	unsigned long Action_Priority;
	unsigned long Action_ID;
	unsigned int Observer_ID;
	Vector3 varB8;
	GameObject *varAC;
	float varA8;
	Vector3 Move_Destination;
	GameObject *Move_Target;
	Vector3 var94;
	float Move_Speed;
	float Move_Arrive_Distance;
	bool Move_Backwards;
	bool Move_Following;
	bool Move_Crouch;
	bool Move_Pathfind;
	bool var7C;
	float Attack_Range;
	float Attack_Deviation;
	bool var70;
	GameObject *Attack_Target;
	bool Attack_Primary;
	bool Attack_Crouched;
	Vector3 Attack_Location;
	bool Hold_Action;
	bool var57;
	bool var56;
	bool var55;
	bool var54;
	bool var53;
	Vector3 Face_Location;
	float Face_Time;
	bool var40;
	unsigned long Move_Waypath_ID;
	unsigned long Move_Waypath_Start_ID;
	unsigned long Move_Waypath_End_ID;
	bool Move_Waypath_Splined;
	const char *Animation;
	bool Anim_Loop;
	unsigned int var24;
	const char *var20;
	long Soldier_AI_State; //has something to do with the soldier AI state
	Vector3 Dock_Location;
	Vector3 Dock_Entrance;
	ActionParamsStruct()
	{
		Action_Priority = 0;
		Action_ID = 0;
		Observer_ID = 0;
		varB8.X = 0;
		varB8.Y = 0;
		varB8.Z = 0;
		varAC = 0;
		varA8 = 0;
		Move_Destination.X = 0;
		Move_Destination.Y = 0;
		Move_Destination.Z = 0;
		Move_Target = 0;
		var94.X = 0;
		var94.Y = 0;
		var94.Z = 0;
		Move_Speed = 1.0;
		Move_Arrive_Distance = 1000;
		Move_Backwards = false;
		Move_Following = false;
		Move_Crouch = false;
		Move_Pathfind = true;
		var7C = false;
		Attack_Range = 20;
		Attack_Deviation = 0;
		var70 = false;
		Attack_Target = 0;
		Attack_Primary = true;
		Attack_Crouched = false;
		Attack_Location.X = 0;
		Attack_Location.Y = 0;
		Attack_Location.Z = 0;
		Hold_Action = true;
		var57 = true;
		var56 = false;
		var55 = true;
		var54 = false;
		var53 = false;
		Face_Location.X = 0;
		Face_Location.Y = 0;
		Face_Location.Z = 0;
		Face_Time = 2.0;
		var40 = false;
		Move_Waypath_ID = 0;
		Move_Waypath_Start_ID = 0;
		Move_Waypath_End_ID = 0;
		Move_Waypath_Splined = false;
		Animation = 0;
		Anim_Loop = false;
		var24 = 0;
		var20 = 0;
		Soldier_AI_State = -1;
		Dock_Location.X = 0;
		Dock_Location.Y = 0;
		Dock_Location.Z = 0;
		Dock_Entrance.X = 0;
		Dock_Entrance.Y = 0;
		Dock_Entrance.Z = 0;
	}
	void Set_Basic(ScriptClass *s,unsigned long priority,unsigned long ID)
	{
		ID = s->GetID();
		Action_Priority = priority;
		Action_ID = ID;
		Soldier_AI_State = -1;
	}
	void Set_Attack(GameObject *Target,float Range,float Deviation,bool Primary)
	{
		Attack_Target = Target;
		Attack_Range = Range;
		Attack_Deviation = Deviation;
		Attack_Primary = Primary;
	}
	void Set_Attack_Hold(GameObject *Target,float Range,float Deviation,bool Primary,bool Hold)
	{
		Attack_Target = Target;
		Attack_Range = Range;
		Attack_Deviation = Deviation;
		Attack_Primary = Primary;
		Hold_Action = Hold;
	}
	void Set_Attack_Position(const Vector3 & position,float Range,float Deviation,bool Primary)
	{
		Attack_Range = Range;
		Attack_Location.X = position.X;
		Attack_Location.Y = position.Y;
		Attack_Location.Z = position.Z;
		Attack_Deviation = Deviation;
		Attack_Primary = Primary;
	}
	void Set_Animation(const char *animation,bool loop)
	{
		Animation = animation;
		Anim_Loop = loop;
	}
	void Set_Face_Location(const Vector3 & facelocation,float Time)
	{
		Face_Location.X = facelocation.X;
		Face_Location.Y = facelocation.Y;
		Face_Location.Z = facelocation.Z;
		Face_Time = Time;
	}
	void Set_Dock(const Vector3 & docklocation,const Vector3 & dockentrance)
	{
		Dock_Location.X = docklocation.X;
		Dock_Location.Y = docklocation.Y;
		Dock_Location.Z = docklocation.Z;
		Dock_Entrance.X = dockentrance.X;
		Dock_Entrance.Y = dockentrance.Y;
		Dock_Entrance.Z = dockentrance.Z;
	}
	void Set_Goto_Location(const Vector3 & position,float speed,float arrivedistance,bool crouch)
	{
		Move_Destination.X = position.X;
		Move_Destination.Y = position.Y;
		Move_Destination.Z = position.Z;
		Move_Speed = speed;
		Move_Arrive_Distance = arrivedistance;
		Move_Crouch = crouch;
	}
	void Set_Goto_Following(GameObject *Target,float speed,float arrivedistance,bool following)
	{
		Move_Target = Target;
		Move_Speed = speed;
		Move_Arrive_Distance = arrivedistance;
		Move_Following = following;
	}
	void Set_Goto_Crouch(GameObject *Target,float speed,float arrivedistance,bool crouch)
	{
		Move_Target = Target;
		Move_Speed = speed;
		Move_Arrive_Distance = arrivedistance;
		Move_Crouch = crouch;
	}
	void Set_Goto_Crouch_Following(GameObject *Target,float speed,float arrivedistance,bool crouch,bool following)
	{
		Move_Target = Target;
		Move_Speed = speed;
		Move_Arrive_Distance = arrivedistance;
		Move_Crouch = crouch;
		Move_Following = following;
	}
	void Set_Goto(GameObject *Target,float speed,float arrivedistance)
	{
		Move_Target = Target;
		Move_Speed = speed;
		Move_Arrive_Distance = arrivedistance;
	}
	void Set_Goto_Waypath_Start(unsigned long waypathID,unsigned long waypathstartID,unsigned long waypathendID,bool splined)
	{
		Move_Waypath_ID = waypathID;
		Move_Waypath_Start_ID = waypathstartID;
		Move_Waypath_End_ID = waypathendID;
		Move_Waypath_Splined = splined;
	}
	void Set_Goto_Waypath(unsigned long waypathID,bool splined,bool v57,bool Hold)
	{
		Move_Waypath_ID = waypathID;
		Move_Waypath_Splined = splined;
		var57 = v57;
		Hold_Action = Hold;
	}
	void Set_Goto_Waypath_ID(unsigned long waypathID)
	{
		Move_Waypath_ID = waypathID;
	}
	void Set_Move_Arrive_Distance(float distance)
	{
		Move_Arrive_Distance = distance;
	}
	void Set_v54(bool v54)
	{
		var54 = v54;
	}
	void Set_Hold(bool Hold)
	{
		Hold_Action = Hold;
	}
};

#define CUSTOM_EVENT_SYSTEM_FIRST 1000000000 //this is what I believe is the marker that specifies the first system message
#define CUSTOM_EVENT_SOUND_ENDED 1000000001 //this one is sent when a sound finishes playing (if the sound was monitored with Monitor_Sound)
#define CUSTOM_EVENT_TOGGLE_POWER 1000000002 //this one is sent on toggle power
#define CUSTOM_EVENT_ARRIVED_AT_DOCK 1000000003 //this one is sent when the thing gets to the dock
#define CUSTOM_EVENT_POWERUP 1000000025 //this one is sent to an item when its collected
#define CUSTOM_EVENT_DAMAGE 1000000026 //all I know is that this one has something to do with damage
#define CUSTOM_EVENT_HEAL 1000000027 //all I know is that this one has something to do with getting health back
#define CUSTOM_EVENT_VEHICLE_ENTER 1000000028 //this one gets sent to a vechicle when something enters it
#define CUSTOM_EVENT_VEHICLE_EXIT 1000000029 //this one gets sent to a vechicle when something exits it
#define CUSTOM_EVENT_ATTACK_ARRIVE 1000000030 //this one gets sent on something to do with arriving at attack location
#define CUSTOM_EVENT_AUDIENCE 1000000031 //this one gets sent on something to do with audience for a conversation
#define CUSTOM_EVENT_NEXT_REMARK 1000000032 //this one gets sent on something to do with say next remark
#define CUSTOM_EVENT_NEXT_REMARK2 1000000033 //this one also gets sent on something to do with say next remark but a different bit of code
#define CUSTOM_EVENT_JUMP_COMPLETE 1000000035 //this one gets sent when the jump is complete
#define CUSTOM_EVENT_VEHICLE_OWNER 1000000036 //Special custom one sent by the new ownership code in bhs.dll and by the scripts in mdbevf.cpp
#define CUSTOM_EVENT_VEHICLE_DRIVER 1000000037 //Special custom one sent to vehicles where the driver/owner gets out to trigger it to find out its driver
#define CUSTOM_EVENT_VHEICLE_DRIVER_ID 1000000038 //Response to CUSTOM_EVENT_VEHICLE_DRIVER, passes the owner GameObjects ID as the param

//values for Set_Obj_Radar_Blip_Shape etc
#define BLIP_SHAPE_NONE 0 //no blip
#define BLIP_SHAPE_HUMAN 1 //circle
#define BLIP_SHAPE_VEHICLE 2 //triangle
#define BLIP_SHAPE_STATIONARY 3 //square
#define BLIP_SHAPE_OBJECTIVE 4 //star
//values for Set_Obj_Radar_Blip_Color etc
#define BLIP_COLOR_RED 0 //default value is 200 0 0
#define BLIP_COLOR_GOLD 1 //default value is 225 175 65
#define BLIP_COLOR_WHITE 2 //default value is 225 225 240
#define BLIP_COLOR_DARK_GREEN 3 //default value is 0 64 0
#define BLIP_COLOR_BLUE 4 //default value is 0 0 255
#define BLIP_COLOR_GREEN 5 //default value is 50 225 50
#define BLIP_COLOR_LIGHT_BLUE 6 //default value is 50 150 250
#define BLIP_COLOR_PURPLE 7 //default value is 150 50 150

class ScriptFactory {
private:
	ScriptFactory *next;
	char *name;
	char *params;
public:
	virtual ~ScriptFactory();
	virtual ScriptImpClass *Create() = 0;
	ScriptFactory(char *n,char *p);
	ScriptFactory *GetNext();
	void SetNext(ScriptFactory *link);
	char *GetName();
	char *GetParamDescription();
};

class ScriptRegistrar {
private:
	static ScriptFactory *mScriptFactories;
public:
	static void RegisterScript(ScriptFactory *ptr);
	static void UnregisterScript(ScriptFactory *ptr);
	static ScriptImpClass *CreateScript(const char *name);
	static ScriptFactory *GetScriptFactory(const char *name);
	static ScriptFactory *GetScriptFactory(int);
	static int Count();
};

template <class T> class ScriptRegistrant : public ScriptFactory {
	public:
	ScriptRegistrant(char *n,char *p) : ScriptFactory(n,p)
	{
	}
	ScriptImpClass *Create();
};

template <class T> ScriptImpClass *ScriptRegistrant<T>::Create()
{
	ScriptImpClass *scr = new T;
	scr->SetFactory(this);
	scr->Register_Auto_Save_Variables();
	return scr;
};

typedef void (*_Debug_Message) (const char *Message,...);
typedef void (*_Action_Reset) (GameObject *Obj,float MaxResetPriority);
typedef void (*_Action_Goto) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Attack) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Play_Animation) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Enter_Exit) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Face_Location) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Dock) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Action_Follow_Input) (GameObject *Obj,const ActionParamsStruct &Params);
typedef void (*_Modify_Action) (GameObject *Obj,int ActionID,const ActionParamsStruct &Params,bool ModifyUnk1,bool ModifyUnk2);
typedef int (*_Get_Action_ID) (GameObject *Obj);
typedef void (*_Get_Action_Params) (GameObject *Obj,ActionParamsStruct &Params);
typedef bool (*_Is_Performing_Pathfind_Action) (GameObject *Obj);
typedef void (*_Set_Position) (GameObject *Obj,const Vector3 &Position);
typedef Vector3 (*_Get_Position) (GameObject *Obj);
typedef Vector3 (*_Get_Bone_Position) (GameObject *Obj,const char *Bone);
typedef float (*_Get_Facing) (GameObject *Obj);
typedef void (*_Set_Facing) (GameObject *Obj,float Facing);
typedef void (*_Disable_All_Collisions) (GameObject *Obj);
typedef void (*_Disable_Physical_Collisions) (GameObject *Obj);
typedef void (*_Enable_Collisions) (GameObject *Obj);
typedef void (*_Destroy_Object) (GameObject *Obj);
typedef GameObject *(*_Find_Object) (int ObjectID);
typedef GameObject *(*_Create_Object) (const char *Preset,const Vector3 &Position);
typedef GameObject *(*_Create_Object_At_Bone) (GameObject *Obj,const char *Preset,const char *Bone);
typedef int (*_Get_ID) (GameObject *Obj);
typedef int (*_Get_Preset_ID) (GameObject *Obj);
typedef const char *(*_Get_Preset_Name) (GameObject *Obj);
typedef void (*_Attach_Script) (GameObject *Obj,const char *Script,const char *Parameters);
typedef void (*_Add_To_Dirty_Cull_List) (GameObject *Obj);
typedef void (*_Start_Timer) (GameObject *Obj,ScriptClass *Script,float Time,int Number);
typedef void (*_Trigger_Weapon) (GameObject *Obj,bool TriggerWeapon,const Vector3 &Location,bool Primary);
typedef void (*_Select_Weapon) (GameObject *Obj,const char *Weapon);
typedef void (*_Send_Custom_Event) (GameObject *Sender,GameObject *Reciever,int Message,int Param,float Delay);
typedef void (*_Send_Damaged_Event) (GameObject *Obj,GameObject *Damager);
typedef float (*_Get_Random) (float Min,float Max);
typedef int (*_Get_Random_Int) (int Min,int Max);
typedef void (*_Find_Random_Simple_Object) (const char *Preset);
typedef void (*_Set_Model) (GameObject *Obj,const char *Model);
typedef void (*_Set_Animation) (GameObject *Obj,const char *Animation,bool Loop,const char *SubObject,float FirstFrame,float LastFrame,bool Blended);
typedef void (*_Set_Animation_Frame) (GameObject *Obj,const char *Animation,int Frame);
typedef int (*_Create_Sound) (const char *Sound,const Vector3 &Position,GameObject *Obj);
typedef int (*_Create_2D_Sound) (const char *Sound);
typedef int (*_Create_2D_WAV_Sound) (const char *Sound);
typedef int (*_Create_3D_WAV_Sound_At_Bone) (const char *Sound,GameObject *Obj,const char *Bone);
typedef int (*_Create_3D_Sound_At_Bone) (const char *Sound,GameObject *Obj,const char *Bone);
typedef int (*_Create_Logical_Sound) (GameObject *Obj,int SoundTypeMask,const Vector3 &Position,float DropoffRadius);
typedef void (*_Start_Sound) (int SoundID);
typedef void (*_Stop_Sound) (int SoundID,bool RemoveFromScene);
typedef void (*_Monitor_Sound) (GameObject *Obj,int SoundID);
typedef void (*_Set_Background_Music) (const char *Music);
typedef void (*_Fade_Background_Music) (const char *Music,int FadeOut,int FadeIn);
typedef void (*_Stop_Background_Music) ();
typedef float (*_Get_Health) (GameObject *Obj);
typedef float (*_Get_Max_Health) (GameObject *Obj);
typedef void (*_Set_Health) (GameObject *Obj,float Health);
typedef float (*_Get_Shield_Strength) (GameObject *Obj);
typedef float (*_Get_Max_Shield_Strength) (GameObject *Obj);
typedef void (*_Set_Shield_Strength) (GameObject *Obj,float Armor);
typedef void (*_Set_Shield_Type) (GameObject *Obj,const char *ArmourType);
typedef int (*_Get_Player_Type) (GameObject *Obj);
typedef void (*_Set_Player_Type) (GameObject *Obj,int PlayerType);
typedef float (*_Get_Distance) (const Vector3 &Pos1,const Vector3 &Pos2);
typedef void (*_Set_Camera_Host) (GameObject *Obj);
typedef void (*_Force_Camera_Look) (const Vector3 &Look);
typedef GameObject *(*_Get_The_Star) ();
typedef GameObject *(*_Get_A_Star) (const Vector3 &Pos);
typedef GameObject *(*_Find_Closest_Soldier) (const Vector3 &Pos,float StartDistance,float EndDistance,bool HumanControled);
typedef bool (*_Is_A_Star) (GameObject *Obj);
typedef void (*_Control_Enable) (GameObject *Obj,bool Enable);
typedef const char *(*_Get_Damage_Bone_Name) ();
typedef float (*_Get_Damage_Bone_Direction) ();
typedef bool (*_Is_Object_Visible) (GameObject *Obj,GameObject *Visible);
typedef void (*_Enable_Enemy_Seen) (GameObject *Obj,bool Enable);
typedef void (*_Set_Display_Color) (unsigned char Red,unsigned char Green,unsigned char Blue);
typedef void (*_Display_Text) (int StringID);
typedef void (*_Display_Float) (float Number,const char *Message);
typedef void (*_Display_Int) (int Number,const char *Message);
typedef void (*_Save_Data) (ScriptSaver &Saver,int MicroChunkID,int Size,void *data);
typedef void (*_Save_Pointer) (ScriptSaver &Saver,int MicroChunkID,void *data);
typedef char (*_Load_Begin) (ScriptLoader &Loader,int *MicroChunkID);
typedef void (*_Load_Data) (ScriptLoader &Loader,int Size,void *Data);
typedef void (*_Load_Pointer) (ScriptLoader &Loader,void **Data);
typedef void (*_Load_End) (ScriptLoader &Loader);
typedef void (*_Begin_Chunk) (ScriptSaver &Saver,unsigned int ChunkID);
typedef void (*_End_Chunk) (ScriptSaver &Saver);
typedef char (*_Open_Chunk) (ScriptLoader &Loader,unsigned int *ChunkID);
typedef void (*_Close_Chunk) (ScriptLoader &Loader);
typedef void (*_Clear_Radar_Markers) ();
typedef void (*_Clear_Radar_Marker) (int Marker);
typedef void (*_Add_Radar_Marker) (int Marker,const Vector3 &Pos,int Shape,int Color);
typedef void (*_Set_Obj_Radar_Blip_Shape) (GameObject *Obj,int Shape);
typedef void (*_Set_Obj_Radar_Blip_Color) (GameObject *Obj,int Color);
typedef void (*_Enable_Radar) (bool Enable);
typedef void (*_Clear_Map_Cell) (int X,int Y);
typedef void (*_Clear_Map_Cell_By_Pos) (const Vector3 &Pos);
typedef void (*_Clear_Map_Cell_By_Pixel_Pos) (int X,int Y);
typedef void (*_Clear_Map_Region_By_Pos) (const Vector3 &Pos,int Reigon);
typedef void (*_Reveal_Map) ();
typedef void (*_Shroud_Map) ();
typedef void (*_Show_Player_Map_Marker) (bool Show);
typedef float (*_Get_Safe_Flight_Height) (float X,float Y);
typedef void (*_Create_Explosion) (const char *Explosion,const Vector3 &Pos,GameObject *Damager);
typedef void (*_Create_Explosion_At_Bone) (const char *Explosion,GameObject *Obj,const char *Bone,GameObject *Damager);
typedef void (*_Enable_HUD) (bool Enable);
typedef void (*_Mission_Complete) (bool Success);
typedef void (*_Give_Powerup) (GameObject *Obj,const char *Powerup,bool ShowOnHud);
typedef void (*_Innate_Disable) (GameObject *Obj);
typedef void (*_Innate_Enable) (GameObject *Obj);
typedef void (*_Innate_Soldier_Enable_Enemy_Seen) (GameObject *Obj,bool Enable);
typedef void (*_Innate_Soldier_Enable_Gunshot_Heard) (GameObject *Obj,bool Enable);
typedef void (*_Innate_Soldier_Enable_Footsteps_Heard) (GameObject *Obj,bool Enable);
typedef void (*_Innate_Soldier_Enable_Bullet_Heard) (GameObject *Obj,bool Enable);
typedef void (*_Innate_Soldier_Enable_Actions) (GameObject *Obj,bool Enable);
typedef void (*_Set_Innate_Soldier_Home_Location) (GameObject *Obj,const Vector3 &Pos,float Facing);
typedef void (*_Set_Innate_Aggressiveness) (GameObject *Obj,float Aggressiveness);
typedef void (*_Set_Innate_Take_Cover_Probability) (GameObject *Obj,float Probobility);
typedef void (*_Set_Innate_Is_Stationary) (GameObject *Obj,bool IsStationary);
typedef void (*_Innate_Force_State_Bullet_Heard) (GameObject *Obj,const Vector3 &Pos);
typedef void (*_Innate_Force_State_Footsteps_Heard) (GameObject *Obj,const Vector3 &Pos);
typedef void (*_Innate_Force_State_Gunshots_Heard) (GameObject *Obj,const Vector3 &Pos);
typedef void (*_Innate_Force_State_Enemy_Seen) (GameObject *Obj,GameObject *Enemy);
typedef void (*_Static_Anim_Phys_Goto_Frame) (int ObjectID,float Frame,const char *Anim);
typedef void (*_Static_Anim_Phys_Goto_Last_Frame) (int ObjectID,const char *Anim);
typedef int (*_Get_Sync_Time) ();
typedef void (*_Add_Objective) (int ObjectiveID,int Type,int ObjectiveUnk,int LongDescID,const char *Sound,int ShortDescID);
typedef void (*_Remove_Objective) (int ObjectiveID);
typedef void (*_Set_Objective_Status) (int ObjectiveID,int Status);
typedef void (*_Change_Objective_Type) (int ObjectiveID,int Type);
typedef void (*_Set_Objective_Radar_Blip) (int ObjectiveID,const Vector3 &Pos);
typedef void (*_Set_Objective_Radar_Blip_Object) (int ObjectiveID,GameObject *Obj);
typedef void (*_Set_Objective_HUD_Info) (int ObjectiveID,float Priority,const char *PogTexture,int PogTitleId);
typedef void (*_Set_Objective_HUD_Info_Position) (int ObjectiveID,float Priority,const char *PogTexture,int PogTitleId,const Vector3 &Pos);
typedef void (*_Shake_Camera) (const Vector3 &Pos,float Radius,float Intensity,float Time);
typedef void (*_Enable_Spawner) (int SpawnerID,bool Enable);
typedef void (*_Trigger_Spawner) (int SpawnerID);
typedef void (*_Enable_Engine) (GameObject *Obj,bool Enable);
typedef int (*_Get_Difficulty_Level) ();
typedef void (*_Grant_Key) (GameObject *Obj,int Key,bool Grant);
typedef bool (*_Has_Key) (GameObject *obj,int Key);
typedef void (*_Enable_Hibernation) (GameObject *Obj,bool Enable);
typedef void (*_Attach_To_Object_Bone) (GameObject *AttachObj,GameObject *BoneObj,const char *Bone);
typedef int (*_Create_Conversation) (const char *Conversation,int Priority,float MaxDist,bool IsInterruptable);
typedef void (*_Join_Conversation) (GameObject *Obj,int ConversationID,bool OratorFlag1,bool OratorFlag2,bool OratorFlag3);
typedef void (*_Join_Conversation_Facing) (GameObject *Obj,int ConversationID,int Facing);
typedef void (*_Start_Conversation) (int ConversationID,int ActionID);
typedef void (*_Monitor_Conversation) (GameObject *Obj,int ConversationID);
typedef void (*_Start_Random_Conversation) (GameObject *Obj);
typedef void (*_Stop_Conversation) (int ConversationID);
typedef void (*_Stop_All_Conversations) ();
typedef void (*_Lock_Soldier_Facing) (GameObject *Obj,GameObject *LockObj,bool Lock);
typedef void (*_Unlock_Soldier_Facing) (GameObject *Obj);
typedef void (*_Apply_Damage) (GameObject *Obj,float Damage,const char *Warhead,GameObject *Damager);
typedef void (*_Set_Loiters_Allowed) (GameObject *Obj,bool Allowed);
typedef void (*_Set_Is_Visible) (GameObject *Obj,bool Visible);
typedef void (*_Set_Is_Rendered) (GameObject *Obj,bool Rendered);
typedef float (*_Get_Points) (GameObject *Obj);
typedef void (*_Give_Points) (GameObject *Obj,float Points,bool EntireTeam);
typedef float (*_Get_Money) (GameObject *Obj);
typedef void (*_Give_Money) (GameObject *Obj,float Money,bool EntireTeam);
typedef bool (*_Get_Building_Power) (GameObject *Obj);
typedef void (*_Set_Building_Power) (GameObject *Obj,bool Powered);
typedef void (*_Play_Building_Announcement) (GameObject *Obj,int AnnouncementID);
typedef GameObject *(*_Find_Nearest_Building) (GameObject *Obj,const char *Building);
typedef GameObject *(*_Find_Nearest_Building_To_Pos) (const Vector3 &Pos,const char *Building);
typedef int (*_Team_Members_In_Zone) (GameObject *Zone,int Team);
typedef void (*_Set_Clouds) (float Cover,float Gloominess,float Transition);
typedef void (*_Set_Lightning) (float Intensity,float StartDistance,float EndDistance,float Heading,float Distribution,float Transition);
typedef void (*_Set_War_Blitz) (float Intensity,float StartDistance,float EndDistance,float Heading,float Distribution,float Transition);
typedef void (*_Set_Wind) (float Heading,float Speed,float Variability,float Transition);
typedef void (*_Set_Rain) (float Density,float Transition,bool Unused);
typedef void (*_Set_Snow) (float Density,float Transition,bool Unused);
typedef void (*_Set_Ash) (float Density,float Transition,bool Unused);
typedef void (*_Set_Fog_Enable) (bool Enable);
typedef void (*_Set_Fog_Range) (float StartDistance,float EndDistance,float Transition);
typedef void (*_Enable_Stealth) (GameObject *Obj,bool Stealth);
typedef void (*_Cinematic_Sniper_Control) (bool Enable,float Zoom);
typedef int (*_Text_File_Open) (const char *Filename);
typedef bool (*_Text_File_Get_String) (int Handle,char *Data,int Size);
typedef void (*_Text_File_Close) (int Handle);
typedef void (*_Enable_Vehicle_Transitions) (GameObject *Obj,bool Enable);
typedef void (*_Display_GDI_Player_Terminal) ();
typedef void (*_Display_NOD_Player_Terminal) ();
typedef void (*_Display_Mutant_Player_Terminal) ();
typedef bool (*_Reveal_Encyclopedia_Character) (int EncyclopediaID);
typedef bool (*_Reveal_Encyclopedia_Weapon) (int EncyclopediaID);
typedef bool (*_Reveal_Encyclopedia_Vehicle) (int EncyclopediaID);
typedef bool (*_Reveal_Encyclopedia_Building) (int EncyclopediaID);
typedef void (*_Display_Encyclopedia_Event_UI) ();
typedef void (*_Scale_AI_Awareness) (float GlobalSightRangeScale,float Unused);
typedef void (*_Enable_Cinematic_Freeze) (GameObject *Obj,bool Freeze);
typedef void (*_Expire_Powerup) (GameObject *Obj);
typedef void (*_Set_HUD_Help_Text) (int StringID,const Vector3 &Color);
typedef void (*_Enable_HUD_Pokable_Indicator) (GameObject *Obj,bool IsPokeable);
typedef void (*_Enable_Innate_Conversations) (GameObject *Obj,bool Enable);
typedef void (*_Display_Health_Bar) (GameObject *Obj,bool Display);
typedef void (*_Enable_Shadow) (GameObject *Obj,bool Enable);
typedef void (*_Clear_Weapons) (GameObject *Obj);
typedef void (*_Set_Num_Tertiary_Objectives) (int Num);
typedef void (*_Enable_Letterbox) (bool Enable,float Transition);
typedef void (*_Set_Screen_Fade_Color) (float Red,float Green,float Blue,float Transition);
typedef void (*_Set_Screen_Fade_Opacity) (float Opacity,float Transition);

//note: "tested" after a script command means that someone has actually used it in a script and we have verified that it does what we think it does and that we know how to use it.
//also "doesnt work in MP" means that it will not work for machines other than the host in standard renegade. However,some of them can be made to work in various ways via bhs.dll
struct ScriptCommands {
	unsigned int version1;
	unsigned int version2;
	_Debug_Message Debug_Message; //doesnt work in the public builds of renegade,one can always use your own calls to fopen and fwrite and etc
	_Action_Reset Action_Reset; //tested
	_Action_Goto Action_Goto; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Action_Attack Action_Attack; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Action_Play_Animation Action_Play_Animation; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do),may not work in MP
	_Action_Enter_Exit Action_Enter_Exit;
	_Action_Face_Location Action_Face_Location; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Action_Dock Action_Dock; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Action_Follow_Input Action_Follow_Input; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Modify_Action Modify_Action; //partially tested (command works but there is a lot more testing to figure out all the fields in the ActionParamsStruct to do)
	_Get_Action_ID Get_Action_ID;
	_Get_Action_Params Get_Action_Params;
	_Is_Performing_Pathfind_Action Is_Performing_Pathfind_Action;
	_Set_Position Set_Position; //tested
	_Get_Position Get_Position; //tested
	_Get_Bone_Position Get_Bone_Position; //tested
	_Get_Facing Get_Facing; //tested
	_Set_Facing Set_Facing; //tested
	_Disable_All_Collisions Disable_All_Collisions; //tested
	_Disable_Physical_Collisions Disable_Physical_Collisions; //tested
	_Enable_Collisions Enable_Collisions; //tested
	_Destroy_Object Destroy_Object; //tested
	_Find_Object Find_Object; //tested
	_Create_Object Create_Object; //tested. Dont use on objects that arent PhysicalGameObjs
	_Create_Object_At_Bone Create_Object_At_Bone; //tested
	_Get_ID Get_ID; //tested
	_Get_Preset_ID Get_Preset_ID; //tested
	_Get_Preset_Name Get_Preset_Name; //tested
	_Attach_Script Attach_Script; //tested
	_Add_To_Dirty_Cull_List Add_To_Dirty_Cull_List; //tested
	_Start_Timer Start_Timer; //tested
	_Trigger_Weapon Trigger_Weapon;
	_Select_Weapon Select_Weapon; //tested, doesnt work in MP without bhs.dll
	_Send_Custom_Event Send_Custom_Event; //tested
	_Send_Damaged_Event Send_Damaged_Event;
	_Get_Random Get_Random; //tested
	_Get_Random_Int Get_Random_Int; //tested
	_Find_Random_Simple_Object Find_Random_Simple_Object;
	_Set_Model Set_Model; //tested, doesnt work in MP for vehicles or infantry without bhs.dll
	_Set_Animation Set_Animation; //tested,doesnt work in MP unless you have bhs.dll
	_Set_Animation_Frame Set_Animation_Frame; //tested,doesnt work in MP unless you have bhs.dll
	_Create_Sound Create_Sound; //tested,this one takes a preset,doesnt work in MP unless you have bhs.dll
	_Create_2D_Sound Create_2D_Sound; //tested,this one takes a preset,doesnt work in MP unless you have bhs.dll
	_Create_2D_WAV_Sound Create_2D_WAV_Sound; //tested,doesnt work in MP unless you have bhs.dll
	_Create_3D_WAV_Sound_At_Bone Create_3D_WAV_Sound_At_Bone; //tested,doesnt work in MP unless you have bhs.dll
	_Create_3D_Sound_At_Bone Create_3D_Sound_At_Bone; //tested,doesnt work in MP unless you have bhs.dll
	_Create_Logical_Sound Create_Logical_Sound; //tested,this one takes a "logical sound",doesnt work in MP
	_Start_Sound Start_Sound; //tested,doesnt work in MP
	_Stop_Sound Stop_Sound; //tested,doesnt work in MP
	_Monitor_Sound Monitor_Sound; //tested,doesnt work in MP
	_Set_Background_Music Set_Background_Music; //tested,doesnt work in MP unless you have bhs.dll
	_Fade_Background_Music Fade_Background_Music; //tested,doesnt work in MP unless you have bhs.dll
	_Stop_Background_Music Stop_Background_Music; //tested,doesnt work in MP unless you have bhs.dll
	_Get_Health Get_Health; //tested
	_Get_Max_Health Get_Max_Health; //tested
	_Set_Health Set_Health; //tested
	_Get_Shield_Strength Get_Shield_Strength; //tested
	_Get_Max_Shield_Strength Get_Max_Shield_Strength; //tested
	_Set_Shield_Strength Set_Shield_Strength; //tested
	_Set_Shield_Type Set_Shield_Type; //tested
	_Get_Player_Type Get_Player_Type; //tested,doesnt work on Buildings or Script Zones
	_Set_Player_Type Set_Player_Type; //tested,doesnt work on Buildings or Script Zones, doesnt work 100% in MP without bhs.dll (I think)
	_Get_Distance Get_Distance; //tested
	_Set_Camera_Host Set_Camera_Host; //tested,doesnt work in MP
	_Force_Camera_Look Force_Camera_Look; //tested,doesnt work in MP unless you have bhs.dll
	_Get_The_Star Get_The_Star; //tested,not for MP
	_Get_A_Star Get_A_Star; //tested
	_Find_Closest_Soldier Find_Closest_Soldier; //tested
	_Is_A_Star Is_A_Star; //tested
	_Control_Enable Control_Enable; //tested
	_Get_Damage_Bone_Name Get_Damage_Bone_Name; //tested
	_Get_Damage_Bone_Direction Get_Damage_Bone_Direction;
	_Is_Object_Visible Is_Object_Visible;
	_Enable_Enemy_Seen Enable_Enemy_Seen; //tested
	_Set_Display_Color Set_Display_Color; //doesnt work in MP without bhs.dll
	_Display_Text Display_Text; //tested,doesnt work in MP without bhs.dll
	_Display_Float Display_Float; //tested,doesnt work in MP without bhs.dll
	_Display_Int Display_Int; //tested,doesnt work in MP without bhs.dll
	_Save_Data Save_Data; //tested,doesnt work in MP
	_Save_Pointer Save_Pointer; //doesnt work in MP
	_Load_Begin Load_Begin; //tested,doesnt work in MP
	_Load_Data Load_Data; //tested,doesnt work in MP
	_Load_Pointer Load_Pointer; //doesnt work in MP
	_Load_End Load_End; //tested,doesnt work in MP
	_Begin_Chunk Begin_Chunk; //tested,doesnt work in MP
	_End_Chunk End_Chunk; //tested,doesnt work in MP
	_Open_Chunk Open_Chunk; //tested,doesnt work in MP
	_Close_Chunk Close_Chunk; //tested,doesnt work in MP
	_Clear_Radar_Markers Clear_Radar_Markers; //doesnt work in MP
	_Clear_Radar_Marker Clear_Radar_Marker; //tested,doesnt work in MP
	_Add_Radar_Marker Add_Radar_Marker; //tested,doesnt work in MP
	_Set_Obj_Radar_Blip_Shape Set_Obj_Radar_Blip_Shape; //tested,doesnt work in MP
	_Set_Obj_Radar_Blip_Color Set_Obj_Radar_Blip_Color; //tested,doesnt work in MP
	_Enable_Radar Enable_Radar; //tested,doesnt work in MP unless you have bhs.dll
	_Clear_Map_Cell Clear_Map_Cell; //tested,doesnt work in MP
	_Clear_Map_Cell_By_Pos Clear_Map_Cell_By_Pos; //doesnt work in MP
	_Clear_Map_Cell_By_Pixel_Pos Clear_Map_Cell_By_Pixel_Pos; //doesnt work in MP
	_Clear_Map_Region_By_Pos Clear_Map_Region_By_Pos; //doesnt work in MP
	_Reveal_Map Reveal_Map; //doesnt work in MP
	_Shroud_Map Shroud_Map; //doesnt work in MP
	_Show_Player_Map_Marker Show_Player_Map_Marker; //doesnt work in MP
	_Get_Safe_Flight_Height Get_Safe_Flight_Height; //tested
	_Create_Explosion Create_Explosion; //tested,doesnt work in MP unless you have bhs.dll
	_Create_Explosion_At_Bone Create_Explosion_At_Bone; //tested,doesnt work in MP unless you have bhs.dll
	_Enable_HUD Enable_HUD; //tested,doesnt work in MP unless you have bhs.dll
	_Mission_Complete Mission_Complete; //tested,doesnt work in MP
	_Give_Powerup Give_Powerup; //tested
	_Innate_Disable Innate_Disable; //tested
	_Innate_Enable Innate_Enable; //tested
	_Innate_Soldier_Enable_Enemy_Seen Innate_Soldier_Enable_Enemy_Seen; //tested
	_Innate_Soldier_Enable_Gunshot_Heard Innate_Soldier_Enable_Gunshot_Heard; //tested
	_Innate_Soldier_Enable_Footsteps_Heard Innate_Soldier_Enable_Footsteps_Heard; //tested
	_Innate_Soldier_Enable_Bullet_Heard Innate_Soldier_Enable_Bullet_Heard; //tested
	_Innate_Soldier_Enable_Actions Innate_Soldier_Enable_Actions; //tested
	_Set_Innate_Soldier_Home_Location Set_Innate_Soldier_Home_Location;
	_Set_Innate_Aggressiveness Set_Innate_Aggressiveness; //tested
	_Set_Innate_Take_Cover_Probability Set_Innate_Take_Cover_Probability;
	_Set_Innate_Is_Stationary Set_Innate_Is_Stationary;
	_Innate_Force_State_Bullet_Heard Innate_Force_State_Bullet_Heard;
	_Innate_Force_State_Footsteps_Heard Innate_Force_State_Footsteps_Heard;
	_Innate_Force_State_Gunshots_Heard Innate_Force_State_Gunshots_Heard;
	_Innate_Force_State_Enemy_Seen Innate_Force_State_Enemy_Seen;
	_Static_Anim_Phys_Goto_Frame Static_Anim_Phys_Goto_Frame; //tested,doesnt work in MP
	_Static_Anim_Phys_Goto_Last_Frame Static_Anim_Phys_Goto_Last_Frame; //tested,doesnt work in MP
	_Get_Sync_Time Get_Sync_Time; //tested
	_Add_Objective Add_Objective; //tested,doesnt work in MP
	_Remove_Objective Remove_Objective; //tested,doesnt work in MP
	_Set_Objective_Status Set_Objective_Status; //tested,doesnt work in MP
	_Change_Objective_Type Change_Objective_Type; //tested,doesnt work in MP
	_Set_Objective_Radar_Blip Set_Objective_Radar_Blip; //tested,doesnt work in MP
	_Set_Objective_Radar_Blip_Object Set_Objective_Radar_Blip_Object; //tested,doesnt work in MP
	_Set_Objective_HUD_Info Set_Objective_HUD_Info; //tested,doesnt work in MP
	_Set_Objective_HUD_Info_Position Set_Objective_HUD_Info_Position; //tested,doesnt work in MP
	_Shake_Camera Shake_Camera; //tested, doesnt work in MP without bhs.dll
	_Enable_Spawner Enable_Spawner; //tested
	_Trigger_Spawner Trigger_Spawner;
	_Enable_Engine Enable_Engine; //tested,does something to vehicle sounds and possibly something else
	_Get_Difficulty_Level Get_Difficulty_Level; //tested
	_Grant_Key Grant_Key; //tested
	_Has_Key Has_Key; //tested
	_Enable_Hibernation Enable_Hibernation; //tested
	_Attach_To_Object_Bone Attach_To_Object_Bone; //tested
	_Create_Conversation Create_Conversation; // doesnt work in MP
	_Join_Conversation Join_Conversation; // doesnt work in MP
	_Join_Conversation_Facing Join_Conversation_Facing; // doesnt work in MP
	_Start_Conversation Start_Conversation; // doesnt work in MP
	_Monitor_Conversation Monitor_Conversation; // doesnt work in MP
	_Start_Random_Conversation Start_Random_Conversation; // doesnt work in MP
	_Stop_Conversation Stop_Conversation; // doesnt work in MP
	_Stop_All_Conversations Stop_All_Conversations; // doesnt work in MP
	_Lock_Soldier_Facing Lock_Soldier_Facing; //tested
	_Unlock_Soldier_Facing Unlock_Soldier_Facing; //tested
	_Apply_Damage Apply_Damage; //tested,the "damager" is the object that should be treated as doing the damage (for the purposes of the Damaged event and probobly also points)
	_Set_Loiters_Allowed Set_Loiters_Allowed; //tested
	_Set_Is_Visible Set_Is_Visible; //tested (only affects the Is_Object_Visible command and also I think Enemy_Seen logic)
	_Set_Is_Rendered Set_Is_Rendered; //tested
	_Get_Points Get_Points; //tested
	_Give_Points Give_Points; //tested,negative numbers work
	_Get_Money Get_Money; //tested
	_Give_Money Give_Money; //tested,negative numbers work
	_Get_Building_Power Get_Building_Power; //tested
	_Set_Building_Power Set_Building_Power; //tested (only the base defenses seem to actually power down)
	_Play_Building_Announcement Play_Building_Announcement; //doesnt work in mp without bhs.dll
	_Find_Nearest_Building Find_Nearest_Building;
	_Find_Nearest_Building_To_Pos Find_Nearest_Building_To_Pos;
	_Team_Members_In_Zone Team_Members_In_Zone;
	_Set_Clouds Set_Clouds; //tested
	_Set_Lightning Set_Lightning; //tested
	_Set_War_Blitz Set_War_Blitz; //tested,doesnt work in mp unless you have bhs.dll
	_Set_Wind Set_Wind; //tested
	_Set_Rain Set_Rain; //tested
	_Set_Snow Set_Snow; //tested
	_Set_Ash Set_Ash; //tested
	_Set_Fog_Enable Set_Fog_Enable; //tested,doesnt work in MP unless you have bhs.dll
	_Set_Fog_Range Set_Fog_Range; //tested,doesnt work in MP unless you have bhs.dll
	_Enable_Stealth Enable_Stealth; //tested,doesnt work in MP unless you have bhs.dll
	_Cinematic_Sniper_Control Cinematic_Sniper_Control; //tested (the sniper effect probobly only happens if you call other commands first or something,more work needed),doesnt work in MP
	_Text_File_Open Text_File_Open; //tested
	_Text_File_Get_String Text_File_Get_String; //tested
	_Text_File_Close Text_File_Close; //tested
	_Enable_Vehicle_Transitions Enable_Vehicle_Transitions; //tested,doesnt stop you from getting out,only in (I think), doesnt work 100% in MP without bhs.dll
	_Display_GDI_Player_Terminal Display_GDI_Player_Terminal; //tested,doesnt work in MP unless you have bhs.dll
	_Display_NOD_Player_Terminal Display_NOD_Player_Terminal; //tested,doesnt work in MP unless you have bhs.dll
	_Display_Mutant_Player_Terminal Display_Mutant_Player_Terminal; //crashes renegade if you use it
	_Reveal_Encyclopedia_Character Reveal_Encyclopedia_Character; //tested,doesnt work in MP
	_Reveal_Encyclopedia_Weapon Reveal_Encyclopedia_Weapon; //tested,doesnt work in MP
	_Reveal_Encyclopedia_Vehicle Reveal_Encyclopedia_Vehicle; //tested,doesnt work in MP
	_Reveal_Encyclopedia_Building Reveal_Encyclopedia_Building; //tested,doesnt work in MP
	_Display_Encyclopedia_Event_UI Display_Encyclopedia_Event_UI; //tested,doesnt work in MP
	_Scale_AI_Awareness Scale_AI_Awareness;
	_Enable_Cinematic_Freeze Enable_Cinematic_Freeze;
	_Expire_Powerup Expire_Powerup; //tested
	_Set_HUD_Help_Text Set_HUD_Help_Text; //tested,doesnt work in MP
	_Enable_HUD_Pokable_Indicator Enable_HUD_Pokable_Indicator; //tested
	_Enable_Innate_Conversations Enable_Innate_Conversations; //tested
	_Display_Health_Bar Display_Health_Bar; //tested
	_Enable_Shadow Enable_Shadow; //tested
	_Clear_Weapons Clear_Weapons; //tested, doesnt work in MP for vehicles without bhs.dll
	_Set_Num_Tertiary_Objectives Set_Num_Tertiary_Objectives; //tested,doesnt work in MP
	_Enable_Letterbox Enable_Letterbox; //tested,doesnt work in MP
	_Set_Screen_Fade_Color Set_Screen_Fade_Color; //tested,doesnt work in MP unless you have bhs.dll
	_Set_Screen_Fade_Opacity Set_Screen_Fade_Opacity; //tested,doesnt work in MP unless you have bhs.dll
};

typedef ScriptCommands *ScriptCommandsClass;
extern ScriptCommandsClass Commands;
