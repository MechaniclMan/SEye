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

void InitEngineDmg(unsigned int exe);
void Kill_All_Buildings_By_Team(int Team); //kill all buildings of the specified team,ending the game with the other team winning,0 = Nod,1 = GDI
void Damage_All_Buildings_By_Team(int Team,float Damage,const char *Warhead,GameObject *Damager); //damages all buildings of the specified team,the Damager is the object that will be passed to the Damaged callback for the buildings and also the one that will get the points,0 = Nod,1 = GDI,2 = both
void Repair_All_Buildings_By_Team(int Team,int ConstructionYardID,float Health); //repairs all buildings for the team except the passed in ConstructionYardID,0 = Nod,1 = GDI
void Repair_All_Static_Vehicles_By_Team(int Team,int Message); //sends a custom to all vechicles of the team with the DecorationPhys physics type (i.e. all base defense vechicles etc),0 = Nod,1 = GDI,Message is the message to send. Use with JFW_Repair_On_Custom on the vechicles you want repaired to do the actual repairing
void Set_Max_Health(GameObject *obj,float health); //set the max health of obj
void Set_Max_Shield_Strength(GameObject *obj,float shieldstrength); //set the max shield strength of obj
const char *Get_Shield_Type(GameObject *obj); //gets the shield type of obj
const char *Get_Skin(GameObject *obj); //gets the skin type of obj
void Set_Skin(GameObject *obj,const char *Skintype); //sets the skin type of obj
void Damage_All_Vehicles_Area(float Damage,const char *Warhead,const Vector3 &Position,float Distance,GameObject *Host,GameObject *Damager); //damages all vechicles in a given area except the host
void Damage_All_Objects_Area(float Damage,const char *Warhead,const Vector3 &Position,float Distance,GameObject *Host,GameObject *Damager); //damages all objects in a given area except the host
//these only do damage if the building is close enough
void Ranged_Damage_To_Buildings(float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings
void Ranged_Scale_Damage_To_Buildings(float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings based on a scale factor
void Ranged_Percentage_Damage_To_Buildings(float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings based on a percentage factor
void Ranged_Damage_To_Buildings_Team(int Team,float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings per team
void Ranged_Scale_Damage_To_Buildings_Team(int Team,float Damage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings per team based on a scale factor
void Ranged_Percentage_Damage_To_Buildings_Team(int Team,float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage buildings per team based on a percentage factor
void Damage_Objects_Half(); //damage all objects by half
void Ranged_Percentage_Damage_To_Vehicles(float Percentage,const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage vehicles based on a percentage factor
void Set_Damage_Points(GameObject *obj,float points); //Set the damage points for an object
void Set_Death_Points(GameObject *obj,float points); //Set the death points for an object
void Repair_All_Buildings_By_Team_Radius(int Team,int ConstructionYardID,float Health,float Radius); //repairs all buildings in the specified radius around the object represented by ConstructionYardID for the team except the passed in ConstructionYardID,0 = Nod,1 = GDI
void Repair_All_Turrets_By_Team(int team,float health); //repairs all vehicles that have mode = turret
void Damage_All_Objects_In_Zone(GameObject *Zone,float Damage,const char *Warhead,GameObject *Damager); //Damages all objects in this zone
float Get_Damage_Points(GameObject *obj); //get the damage points for an object
float Get_Death_Points(GameObject *obj); //get the death points for an object
void Kill_Occupants(GameObject *obj); //kill all the occupants of a vehicle
void Damage_Occupants(GameObject *obj,float Damage,const char *Warhead); //Damage all the occupants of a vehicle
void Ranged_Variable_Percent_Vehicle_Damage(float EnemyPercentage, float FriendPecentage, bool ForceFriendly, const char *Warhead,Vector3 Location,float DamageRadius,GameObject *Damager); //damage vehicles based on a percentage factor
