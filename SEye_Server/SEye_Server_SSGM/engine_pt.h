/*	Renegade Scripts.dll
	Classes and engine calls related to what can be bought from the PT/sidebar
	Copyright 2007 Jonathan Wilson, Mark Sararu, WhiteDragon(MDB)

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
class TeamPurchaseSettingsDefClass : public DefinitionClass {
public:
	unsigned int team;
	unsigned int presetids[4];
	unsigned int stringids[4];
	StringClass textures[4];
	unsigned int beaconcost;
	unsigned int beaconpresetid;
	unsigned int beaconstringid;
	StringClass beacontexture;
	unsigned int refillstringid;
	StringClass refilltexture;
	~TeamPurchaseSettingsDefClass();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	virtual PersistClass *Create();
	static TeamPurchaseSettingsDefClass *Get_Definition(unsigned long team);
};

class PurchaseSettingsDefClass : public DefinitionClass {
public:
	unsigned int team;
	unsigned int type;
	unsigned int costs[10];
	unsigned int presetids[10];
	unsigned int stringids[10];
	StringClass textures[10];
	unsigned int altpresetids[10][3];
	StringClass alttextures[10][3];
	~PurchaseSettingsDefClass();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	static PurchaseSettingsDefClass *Find_Definition(unsigned long type,unsigned long team);
};

void InitEnginePT(unsigned int exe);
TeamPurchaseSettingsDefClass *Get_Team_Purchase_Definition(unsigned long team); //Gets the TeamPurchaseSettingsDefClass for a team
PurchaseSettingsDefClass *Get_Purchase_Definition(unsigned long type, unsigned long team); //Gets the PurchaseSettingsDefClass for a given team and type
//type values for PurchaseSettingsDefClass
#define CHARACTERS 0 //note that this list reflects the list in leveledit
#define VEHICLES 1
#define EQUIPMENT 2
#define SECRETCHARS 3
#define SECRETVEHICLES 4
unsigned int Get_Team_Cost(const char *preset,unsigned int team); //Get the cost of a preset for a given team. Returns zero if the preset is not found in any of the purchase terminal data or if it is one of the free units.
unsigned int Get_Cost(const char *preset); //Get the cost of a preset. Returns zero if the preset is not found in any of the purchase terminal data or if it is one of the free units.
void Set_Enlisted(unsigned int team, unsigned int position, unsigned int presetid, unsigned int stringid, const char *texture); //Change an enlisted soldier for a team
void Set_Beacon(unsigned int team, unsigned int cost, unsigned int presetid, unsigned int stringid, const char *texture); //Change the beacon for a team
void Set_Refill(unsigned int team, unsigned int stringid, const char *texture); //Change the refill for a team. Setting this to zero or blank does not actually disable refill.
void Set_Preset(unsigned int team, unsigned int type, unsigned int position, unsigned int cost, unsigned int presetid, unsigned int stringid, const char *texture); //Change a preset given a type and team
void Set_Alternate(unsigned int team, unsigned int type, unsigned int position, unsigned int altpos, unsigned int presetid, const char *texture); //Change an alternate given a type and a team
void Disable_Enlisted(unsigned int team, unsigned int position); //Disable an enlisted soldier
void Disable_Preset(unsigned int team, unsigned int type, unsigned int position); //Disable a preset
void Disable_Enlisted_By_Name(unsigned int Team,const char *Name); //Disable an enlisted unit by name
void Disable_Preset_By_Name(unsigned int Team,const char *Name); //Disable a preset by name
#define PTTEAM(t) (t?0:1) //Convert a normal team into a PT team
void Disable_All_Ground_Vehicles(unsigned int team); //Removes all ground vehicles from this teams PT menu
void Disable_All_Flying_Vehicles(unsigned int team); //Removes all flying vehicles from this teams PT menu
char *Get_Team_Icon(const char *preset,unsigned int team); //Get the icon texture name for a given preset of a given team. Returns NULL if it cant find that preset in the PT data.
char *Get_Icon(const char *preset); //Get the icon texture name for a given preset. Returns NULL if it cant find that preset in the PT data.
void Hide_Preset_By_Name(unsigned int Team,const char *Name); //Hides a preset by name
