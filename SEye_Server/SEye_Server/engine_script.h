/*	Renegade Scripts.dll
	Script manipulation related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
void Remove_Script(GameObject *obj,const char *script); //removes all copies of <script> from an object
void Remove_All_Scripts(GameObject *obj); //removes all scripts from an object
void Attach_Script_Preset(const char *script,const char *params,const char *preset,int team); //attached <script> to all objects of <preset> in team <team>
void Attach_Script_Type(const char *script,const char *params,unsigned long type,int team); //attaches <script> to all objects of <type> in team <team>
void Remove_Script_Preset(const char *script,const char *preset,int team); //removes all copies of <script> from all objects of <preset> in team <team>
void Remove_Script_Type(const char *script,unsigned long type,int team); //removes all copies of <script> from all objects of <type> in team <team>
bool Is_Script_Attached(GameObject *obj,const char *script); //is the script attached
void Attach_Script_Once(GameObject *obj,const char *script,const char *params); //attach a script if its not already attached
void Attach_Script_Preset_Once(const char *script,const char *params,const char *preset,int team); //attach a script to all objects of preset if its not already attached
void Attach_Script_Type_Once(const char *script,const char *params,unsigned long type,int team); //attach a script to all objects of type if its not already attached
void Attach_Script_Building(const char *script,const char *params,int team); //attach a script to all buildings
void Attach_Script_Is_Preset(GameObject *obj,const char *preset,const char *script,const char *params,int team); //attach the script if object is of preset
void Attach_Script_Is_Type(GameObject *obj,unsigned long type,const char *script,const char *params,int team); //attach the script if object is of type
void Attach_Script_Player_Once(const char *script,const char *params,int team); //attach a script to all players if its not already attached
void Remove_Duplicate_Script(GameObject *obj, const char *script); //remove duplicate scripts from an object
void Attach_Script_All_Buildings_Team(int Team,const char *Script,const char *Params,bool Once); //attach a script to all buildings by team
void Attach_Script_All_Turrets_Team(int Team,const char *Script,const char *Params,bool Once); //attach a script to all static vehicles by team
GameObject *Find_Building_With_Script(int Team,int Type,const char *Script,GameObject *Caller); //Find a building of this type with this script attached to it
GameObject *Find_Object_With_Script(const char *script); //Find the first object with this script on it
