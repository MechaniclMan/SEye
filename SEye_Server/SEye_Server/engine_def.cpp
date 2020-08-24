/*	Renegade Scripts.dll
	General ingame data related classes and engine calls
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

typedef bool (*SetSafeDataUintRef) (void *Handle,unsigned int &Data);
typedef bool (*SetSafeDataIntRef) (void *Handle,int &Data);
typedef bool (*SetSafeDataFloatRef) (void *Handle,float &Data);
typedef DefinitionClass *(*Find_Named_Def) (const char *name,bool twiddle);
typedef DefinitionClass *(*FindDefinition) (unsigned long ID,bool b);

SetSafeDataUintRef Set_Safe_Data_Uint_Ref;
SetSafeDataIntRef Set_Safe_Data_Int_Ref;
SetSafeDataFloatRef Set_Safe_Data_Float_Ref;
void *Get_Safe_Data_Int;
void *Get_Safe_Data_Uint;
void *Get_Safe_Data_Float;
FindDefinition Find_Def;
Find_Named_Def FindNamedDef;

#ifdef WIN32
int THUNK IntDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Int)
float THUNK FloatDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Float)
unsigned int THUNK UIntDataSafeClass::Get()
IMPLEMENT_THUNK_RETURN(Get_Safe_Data_Uint)
bool IntDataSafeClass::Set(int &data)
{
	return Set_Safe_Data_Int_Ref(Data,data);
}
bool FloatDataSafeClass::Set(float &data)
{
	return Set_Safe_Data_Float_Ref(Data,data);
}
bool UIntDataSafeClass::Set(unsigned int &data)
{
	return Set_Safe_Data_Uint_Ref(Data,data);
}
#else
union un {
	float f;
	void *v;
};
int IntDataSafeClass::Get()
{
	return (int)Data;
}
float FloatDataSafeClass::Get()
{
	un u;
	u.v = Data;
	return u.f;
}
unsigned int UIntDataSafeClass::Get()
{
	return (unsigned int)Data;
}
bool IntDataSafeClass::Set(int &data)
{
	Data = (void *)data;
	return true;
}
bool FloatDataSafeClass::Set(float &data)
{
	un u;
	u.f = data;
	Data = u.v;
	return true;
}
bool UIntDataSafeClass::Set(unsigned int &data)
{
	Data = (void *)data;
	return true;
}
#endif

void InitEngineDef(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			Find_Def = (FindDefinition)0x00526760;
			FindNamedDef = (Find_Named_Def)0x00526860;
			Get_Safe_Data_Int = (void *)0x00408280;
			Get_Safe_Data_Uint = (void *)0x00408280;
			Get_Safe_Data_Float = (void *)0x00413510;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0x00694F90;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0x00696200;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0x00414350;
			break;
		case 1: //server.dat
			Find_Def = (FindDefinition)0x00526000;
			FindNamedDef = (Find_Named_Def)0x00526100;
			Get_Safe_Data_Int = (void *)0x00408280;
			Get_Safe_Data_Uint = (void *)0x00408280;
			Get_Safe_Data_Float = (void *)0x00413510;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0x00694830;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0x00695AA0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0x00414350;
			break;
		case 2: //RH73
			Find_Def = (FindDefinition)0x08365410;
			FindNamedDef = (Find_Named_Def)0x0836557C;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			break;
		case 3: //RH8
			Find_Def = (FindDefinition)0x083187AE;
			FindNamedDef = (Find_Named_Def)0x0831890A;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			break;
		default:
			Find_Def = (FindDefinition)0;
			FindNamedDef = (Find_Named_Def)0;
			Get_Safe_Data_Int = (void *)0;
			Get_Safe_Data_Uint = (void *)0;
			Get_Safe_Data_Float = (void *)0;
			Set_Safe_Data_Float_Ref = (SetSafeDataFloatRef)0;
			Set_Safe_Data_Uint_Ref = (SetSafeDataUintRef)0;
			Set_Safe_Data_Int_Ref = (SetSafeDataIntRef)0;
			break;
	}
}

DefinitionClass *Find_Definition(unsigned long id)
{
	return Find_Def(id,1);
}

const char *Get_Definition_Name(unsigned long id)
{
	if (!id)
	{
		return "none";
	}
	DefinitionClass *d = Find_Def(id,1);
	if (!d)
	{
		return "none";
	}
	return d->Get_Name();
}

unsigned long Get_Definition_ID(const char *name)
{
	if (!name)
	{
		return 0;
	}
	DefinitionClass *d = Find_Named_Definition(name);
	if (!d)
	{
		return 0;
	}
	return d->Get_ID();
}

DefinitionClass *Find_Named_Definition(const char *name)
{
	return FindNamedDef(name,1);
}

DefinitionClass *Get_Definition(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	return ((ScriptableGameObj *)obj)->definition;
}

DefinitionClass *Get_Phys_Definition(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_PhysicalGameObj(obj);
	if (!o)
	{
		return 0;
	}
	o+=0x774;
	char *p = (char *)*(unsigned int *)o;
#ifdef WIN32
	p += 0x50;
#else
	p += 0x68;
#endif
	return (DefinitionClass *)*(unsigned int *)p;
}

unsigned long Get_Definition_Class_ID(const char *name)
{
	if (!name)
	{
		return 0;
	}
	DefinitionClass *d = Find_Named_Definition(name);
	if (!d)
	{
		return 0;
	}
	return d->Get_Class_ID();
}

bool Is_Valid_Preset_ID(unsigned long ID)
{
	if (Find_Definition(ID))
	{
		return true;
	}
	return false;
}

bool Is_Valid_Preset(const char *Preset)
{
	if (Find_Named_Definition(Preset))
	{
		return true;
	}
	return false;
}
