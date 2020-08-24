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
#include "scripts.h"
#include "engine_common.h"
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_vector.h"
#include "engine_net.h"
#include "engine_io.h"
#include "engine_script.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_game.h"
#include "engine_phys.h"

void Remove_Script(GameObject *obj,const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			((ScriptImpClass*)(*observers)[i])->Destroy_Script();
		}
	}
}

void Remove_Duplicate_Script(GameObject *obj, const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	bool Found = false;
	for (int i = 0;i < observers->Count();i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			if (!Found)
			{
				Found = true;
			}
			else
			{
				((ScriptImpClass*)(*observers)[i])->Destroy_Script();
			}
		}
	}
}

void Remove_Script_Preset(const char *script,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Remove_Script(o,script);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Remove_Script_Type(const char *script,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Remove_Script(o,script);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Remove_All_Scripts(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		((ScriptImpClass*)(*observers)[i])->Destroy_Script();
	}
}

void Attach_Script_Preset(const char *script,const char *params,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Commands->Attach_Script(o,script,params);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Type(const char *script,const char *params,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					Commands->Attach_Script(o,script,params);
				}
			}
		}
		x = x->NodeNext;
	}
}

bool Is_Script_Attached(GameObject *obj,const char *script)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	SimpleDynVecClass<GameObjObserverClass *> *observers = &((ScriptableGameObj *)obj)->Observers;
	int x = observers->Count();
	for (int i = 0;i < x;i++)
	{
		if (!_stricmp((*observers)[i]->Get_Name(),script))
		{
			return true;
		}
	}
	return false;
}

void Attach_Script_Once(GameObject *obj,const char *script,const char *params)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	if (!Is_Script_Attached(obj,script))
	{
		Commands->Attach_Script(obj,script,params);
	}
}

void Attach_Script_Preset_Once(const char *script,const char *params,const char *preset,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (!_stricmp(d->Get_Name(),preset))
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Type_Once(const char *script,const char *params,unsigned long type,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == type)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Player_Once(const char *script,const char *params,int team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			DefinitionClass *d = Get_Definition(o);
			if (d->Get_Class_ID() == Soldier)
			{
				if ((Get_Object_Type(o) == team) || (team == 2))
				{
					if (!Is_Script_Attached(o,script))
					{
						Commands->Attach_Script(o,script,params);
					}
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Building(const char *script,const char *params,int team)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if ((o) && As_BuildingGameObj(o))
		{
			if ((Get_Object_Type(o) == team) || (team == 2))
			{
				Commands->Attach_Script(o,script,params);
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_Is_Preset(GameObject *obj,const char *preset,const char *script,const char *params,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DefinitionClass *d = Get_Definition(obj);
	if (!_stricmp(d->Get_Name(),preset))
	{
		if ((Get_Object_Type(obj) == team) || (team == 2))
		{
			Commands->Attach_Script(obj,script,params);
		}
	}
}

void Attach_Script_Is_Type(GameObject *obj,unsigned long type,const char *script,const char *params,int team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	DefinitionClass *d = Get_Definition(obj);
	if (d->Get_Class_ID() == type)
	{
		if ((Get_Object_Type(obj) == team) || (team == 2))
		{
			Commands->Attach_Script(obj,script,params);
		}
	}
}

void Attach_Script_All_Buildings_Team(int Team,const char *Script,const char *Params,bool Once)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_BuildingGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Get_Object_Type(o) == Team || Team == 2)
			{
				if (Once)
				{
					Attach_Script_Once(o,Script,Params);
				}
				else
				{
					Commands->Attach_Script(o,Script,Params);
				}
			}
		}
		x = x->NodeNext;
	}
}

void Attach_Script_All_Turrets_Team(int Team,const char *Script,const char *Params,bool Once)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_VehicleGameObj((GameObject *)x->NodeData);
		if (o)
		{
			if (Is_DecorationPhys(o) && (Get_Object_Type(o) == Team || Team == 2))
			{
				if (Once)
				{
					Attach_Script_Once(o,Script,Params);
				}
				else
				{
					Commands->Attach_Script(o,Script,Params);
				}
			}
		}
		x = x->NodeNext;
	}
}

GameObject *Find_Building_With_Script(int Team,int Type,const char *Script,GameObject *Caller)
{
	GenericSLNode *x = BuildingGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o)
		{
			if ((Type == -1 || Building_Type(o) == Type) && (Get_Object_Type(o) == Team || Team == 2) && !Is_Building_Dead(o) && Is_Script_Attached(o,Script) && o != Caller)
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

GameObject *Find_Object_With_Script(const char *script)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_ScriptableGameObj(o))
		{
			if (Is_Script_Attached(o, script))
			{
				return o;
			}
		}
		x = x->NodeNext;
	}
	return NULL;
}
