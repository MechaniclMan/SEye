/*	Renegade Scripts.dll
	Classes and engine calls related to health, damage and repair
	Copyright 2007 Jonathan Wilson, Mark Sararu, Joshua "NeoSaber" Kraft, WhiteDragon(MDB)

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
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_vector.h"
#include "engine_io.h"
#include "engine_net.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_obj2.h"
#include "engine_phys.h"

typedef const char *(*GetArmorName) (unsigned int ID);
typedef unsigned int(*GetArmorType) (const char *name);

GetArmorName Get_Armor_Name;
GetArmorType Get_Armor_Type;

void InitEngineDmg(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Get_Armor_Name = (GetArmorName)0x006877D0;
			Get_Armor_Type = (GetArmorType)0x00687750;
			break;
		case 1: //server.dat
			Get_Armor_Name = (GetArmorName)0x00687070;
			Get_Armor_Type = (GetArmorType)0x00686FF0;
			break;
		case 2: //RH73
			Get_Armor_Name = (GetArmorName)0x0810F87C;
			Get_Armor_Type = (GetArmorType)0x0810F7B4;
			break;
		case 3: //RH8
			Get_Armor_Name = (GetArmorName)0x08101AB8;
			Get_Armor_Type = (GetArmorType)0x081019FC;
			break;
		default:
			Get_Armor_Name = (GetArmorName)0;
			Get_Armor_Type = (GetArmorType)0;
			break;
	}
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
	o->Defense.Set_Max_Health(health);
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
	o->Defense.Set_Max_Shield_Strength(shieldstrength);
	Commands->Set_Shield_Strength(obj,shieldstrength);
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
	return Get_Armor_Name(o->Defense.ShieldType.Get());
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
	return Get_Armor_Name(o->Defense.Skin.Get());
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
	o->Defense.Skin.Set(skin);
	o->Defense.Mark_Owner_Dirty();
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
	o->Defense.DamagePoints.Set(points);
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
	o->Defense.DeathPoints.Set(points);
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
	return o->Defense.DamagePoints.Get();
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
	return o->Defense.DeathPoints.Get();
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

void Ranged_Variable_Percent_Vehicle_Damage(float EnemyPercentage, float FriendPercentage, bool ForceFriendly, const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager)
{
	//This function will apply a different damage amount to friendly vehicles than it
	//does to all other vehicles. It can also force friendly fire
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
							if(Commands->Get_Player_Type(Damager) == Commands->Get_Player_Type(o)) 
							{
								float Damage = (Max_Health + Max_Shield) * FriendPercentage;
								if(ForceFriendly)
								{
									Commands->Apply_Damage(o,Damage,Warhead,0);
								}
								else
								{
									Commands->Apply_Damage(o,Damage,Warhead,Damager);
								}
							}
							else
							{
								float Damage = (Max_Health + Max_Shield) * EnemyPercentage;
								Commands->Apply_Damage(o,Damage,Warhead,Damager);
							}
						}
					}
				}
			}
			x = x->NodeNext;
		}
	}
}
