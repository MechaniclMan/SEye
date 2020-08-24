/*	Renegade Scripts.dll
	Soldier, Vehicle and Script Zone related engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu, Joshua "NeoSaber" Kraft

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
void InitEngineObj2(unsigned int exe);
GameObject *Get_Vehicle(GameObject *obj); //gets the vechicle that obj is driving
void Grant_Refill(GameObject *obj); //triggers the same code as the refill button on the PT
bool Change_Character(GameObject *obj,const char *Preset_Name); //will change the character of the passed in object to the passed in preset
void Create_Vehicle(const char *Preset_Name,float Delay,GameObject *Owner,int Team); //creates a vechicle,dont know what Delay is for,Owner is for the owner of the vechicle,Team says which sides factories to create it at
void Toggle_Fly_Mode(GameObject *obj); //makes a soldier fly if they arent flying or not fly if they are
int Get_Vehicle_Occupant_Count(GameObject *obj); //gets the count of occupants in a vehicle
//these next 3 may return NULL (e.g. if no-one is in the seat or if its not a vehicle)
GameObject *Get_Vehicle_Occupant(GameObject *obj,int seat); //gets the occupant in the given seat of the vehicle
GameObject *Get_Vehicle_Driver(GameObject *obj); //gets the driver of a vehicle
GameObject *Get_Vehicle_Gunner(GameObject *obj); //gets the gunner of a vehicle,if there is only one person this should be the driver as well as the gunner
void Force_Occupant_Exit(GameObject *obj,int seat); //kick the object in <seat> out of the vehicle,if anyone is in that seat
void Force_Occupants_Exit(GameObject *obj); //kick all occupants out of the vehicle
GameObject *Get_Vehicle_Return(GameObject *obj); //like Get_Vehicle but will return the soldier if its not inside a vehicle instead of NULL
bool Is_Stealth(GameObject *obj); //is this object stealth
bool Get_Fly_Mode(GameObject *obj); //is this infantry flying via Set_Fly_Mode
int Get_Vehicle_Seat_Count(GameObject *obj); //get the seat count for a vehicle
char *Get_Spawn_Char(int Team); //get the spawn character for a team
void Change_Spawn_Char(int Team,const char *Name); //change the spawn character for a team (does not reset after the map ends)
void Soldier_Transition_Vehicle(GameObject *obj); //makes the soldier exit the vehicle they are in (or if right next to a vehicle, get in)
unsigned int Get_Vehicle_Mode(GameObject *obj); //Gets the mode of a vehicle
//mode values for vehicles
#define CAR 0 //note that this list reflects the list in leveledit
#define TANK 1
#define BIKE 2
#define FLYING 3
#define TURRET 4
int Get_Team_Vehicle_Count(int team); //Gets the current vehicle count for a team
GameObject *Get_Vehicle_Owner(GameObject *obj); //Gets the owner (if any) of a vehicle. Will not work if used within the first second after the ::Created event is called
void Force_Occupants_Exit_Team(GameObject *obj,int team); //kick all occupants not of a given team out of the vehicle
unsigned int Get_Vehicle_Definition_Mode(const char *preset); //get the mode of a vehicle given its preset name
GameObject *Find_Closest_Zone(Vector3 &Location,unsigned int Type); //Find the closest zone
//type values for script zones
#define DEFAULT 0 //note that this list reflects the list in leveledit
#define CTF 1
#define VEHICLE_CONSTRUCTION 2
#define VEHICLE_REPAIR 3
#define TIBERIUM 4
#define BEACON 5
#define GDITIBERIUM 6
#define NODTIBERIUM 7
bool IsInsideZone(GameObject *zone,GameObject *obj); //is <solder/vehicle> inside <zone>. Will now work if object is inside a zone when its created (e.g. spawns inside zone or zone is moved around them with Create_Zone or Set_Zone_Box)
unsigned int Get_Vehicle_Definition_Mode_By_ID(unsigned long ID); //Get the mode of a vehicle given its preset ID
unsigned int Get_Zone_Type(GameObject *obj); //Get the type of a script zone
OBBoxClass *Get_Zone_Box(GameObject *obj); //Get the box (size/position) of a ScriptZoneGameObj
void Set_Zone_Box(GameObject *obj,const OBBoxClass &box); //Set the box (size/position) of a ScriptZoneGameObj
GameObject *Create_Zone(const char *preset,const OBBoxClass &box); //Create a script zone and set its box
bool PointInZone(GameObject *obj,const Vector3 &v); //Is a point in a zone
unsigned int Overlap_Test(const OBBoxClass &box,const Vector3 &v); //Test if a vector is inside an OBBoxClass
bool IsAvailableForPurchase(GameObject *factory); //Is it possible to purchase a vehicle from this factory
bool Check_Transitions(GameObject *obj,bool unk); //Trigger vehicle transition on an object
GameObject *Get_Vehicle_Gunner_Pos(GameObject *obj); //Get the vehicle gunner, returns zero if there is no gunner
void Set_Vehicle_Is_Visible(GameObject *obj,bool visible); //works like Set_Is_Visible but for vehicles, makes them be ignored by Enemy_Seen
void Set_Vehicle_Gunner(GameObject *obj,int seat); //set gunner for this vehicle
