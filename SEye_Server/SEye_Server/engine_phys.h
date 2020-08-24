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

void InitEnginePhys(unsigned int exe);
const char *Get_Model(GameObject *obj); //get the name of the 3d model used by an object,opposite of Set_Model
float Get_Animation_Frame(GameObject *obj); //gets the current animation frame for obj,may not work for all objects
bool Is_TrackedVehicle(GameObject *obj); //has TrackedVechicle physics
bool Is_VTOLVehicle(GameObject *obj); //has VTOLVechicle physics
bool Is_WheeledVehicle(GameObject *obj); //has WheeledVechicle physics
bool Is_Motorcycle(GameObject *obj); //has Morotcycle physics
bool Is_Door(GameObject *obj); //has Door physics
bool Is_Elevator(GameObject *obj); //has Elevator physics
bool Is_DamageableStaticPhys(GameObject *obj); //has DamageableStaticPhys physics
bool Is_AccessablePhys(GameObject *obj); //has AccessablePhys physics
bool Is_DecorationPhys(GameObject *obj); //has DecorationPhys physics
bool Is_HumanPhys(GameObject *obj); //has HumanPhys physics
bool Is_MotorVehicle(GameObject *obj); //has MotorVehicle physics
bool Is_Phys3(GameObject *obj); //has Phys3 physics
bool Is_RigidBody(GameObject *obj); //has RigidBody physics
bool Is_ShakeableStatricPhys(GameObject *obj); //has ShakeableStaticPhys physics
bool Is_StaticAnimPhys(GameObject *obj); //has StaticAnimPhys physics
bool Is_StaticPhys(GameObject *obj); //has StaticPhys physics
bool Is_TimedDecorationPhys(GameObject *obj); //has TimedDecorationPhys physics
bool Is_VehiclePhys(GameObject *obj); //has VechiclePhys physics
bool Is_DynamicAnimPhys(GameObject *obj); //has DenamicAnimPhys physics
bool Is_BuildingAggregate(GameObject *obj); //has BuildingAggregate physics
bool Is_Projectile(GameObject *obj); //has Projectile physics
const char *Get_Physics(GameObject *obj); //returns a string indicating the physics type of an object
void Copy_Transform(GameObject *in,GameObject *out); //copies the complete transform (including rotation) from one object to another
float Get_Mass(GameObject *obj); //returns the mass of an object
const char *Get_Htree_Name(GameObject *obj); //returns the Hierarchy Tree name for an object
char Get_Sex(GameObject *obj); //gets the character (e.g. "A" for male or "B" for female) for use with animations
void Create_Effect_All_Stealthed_Objects_Area(const Vector3 &Position,float Distance,const char *object,const Vector3 &offset,int team); //creates an indicator object near every stealthed object in a given area
void Create_Effect_All_Of_Preset(const char *object,const char *preset,float ZAdjust,bool ZSet); //Create an object above all objects of a given preset, also set the facing to match the object its being created over.
