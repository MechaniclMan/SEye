/*	Renegade Scripts.dll
	Physics,3d geometry and animation related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

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
#include "engine_io.h"
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_def.h"
#include "engine_net.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_obj2.h"

typedef const char *(*Get_Name) (char *ro);
typedef const char *(*Get_Htree) (char *ro);

void *Physical_Set_Transform;
void *Physical_Get_Transform;

void THUNK PhysicalGameObj::Set_Transform(Matrix3D *mat)
IMPLEMENT_THUNK(Physical_Set_Transform)
Matrix3D THUNK *PhysicalGameObj::Get_Transform()
IMPLEMENT_THUNK_RETURN(Physical_Get_Transform)


void InitEnginePhys(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Physical_Set_Transform = (void *)0x006A5EF0;
			Physical_Get_Transform = (void *)0x006A5F10;
			break;
		case 1: //server.dat
			Physical_Set_Transform = (void *)0x006A5790;
			Physical_Get_Transform = (void *)0x006A57B0;
			break;
		case 2: //RH73
			Physical_Set_Transform = (void *)0x0813DA90;
			Physical_Get_Transform = (void *)0x0813DAAC;
			break;
		case 3: //RH8
			Physical_Set_Transform = (void *)0x0812DA3A;
			Physical_Get_Transform = (void *)0x0812DA56;
			break;
		default:
			Physical_Set_Transform = (void *)0;
			Physical_Get_Transform = (void *)0;
			break;
	}
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
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
	DefinitionClass* definition = Get_Phys_Definition(o);
	if (!definition)
	{
		return false;
	}
	int Class_ID = definition->Get_Class_ID();
	if (Class_ID != 0x9009)
	{
		return false;
	}
	return true;
}

//doesnt work for CinematicGameObjs
float Get_Animation_Frame(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o)
	{
		return 0;
	}
	unsigned char *x = (unsigned char *)o->Animation;
	if (!x)
	{
		return 0;
	}
	float a = (float)*(float *)(x+0x14);
	return a;
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

void Copy_Transform(GameObject *in,GameObject *out)
{
	if (!Commands->Get_ID(in) || !in || !Commands->Get_ID(out) || !out)
	{
		return;
	}
	PhysicalGameObj *i2 = ((ScriptableGameObj *)in)->As_PhysicalGameObj();
	if (!i2)
	{
		return;
	}
	PhysicalGameObj *o2 = ((ScriptableGameObj *)out)->As_PhysicalGameObj();
	if (!o2)
	{
		return;
	}
	o2->Set_Transform(i2->Get_Transform());
}

float Get_Mass(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	PhysicalGameObj *o = ((ScriptableGameObj *)obj)->As_PhysicalGameObj();
	if (!o)
	{
		return 0;
	}
	char *p = (char *)o->Physics;
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
