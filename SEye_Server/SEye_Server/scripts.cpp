/*	Renegade Scripts.dll
	Base script class
	Copyright 2007 Olaf Van Der Spek, Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#include "scripts.h"
#include "engine.h"
char *noparams = 0;
rdf ScriptImpClass::RequestDestroyScript;

ScriptImpClass::ScriptImpClass()
{
	ObserverID = 0;
	Attached = 0;
	mArgC = 0;
	mArgV = 0;
	seralizeinfo = 0;
}

char *ScriptImpClass::Get_Name()
{
	return Factory->GetName();
}

void ScriptImpClass::Attach(GameObject *newobj)
{
	Attached = newobj;
}

void ScriptImpClass::Set_Request_Destroy_Func(rdf Func)
{
	RequestDestroyScript = Func;
}

void ScriptImpClass::Destroy_Script()
{
	if (RequestDestroyScript)
	{
		(RequestDestroyScript) (this);
	}
}

void ScriptImpClass::Detach(GameObject *obj)
{
	Attached = 0;
	Destroy_Script();
}

void ScriptImpClass::Created(GameObject *obj)
{
}

void ScriptImpClass::Destroyed(GameObject *obj)
{
}

void ScriptImpClass::Damaged(GameObject *obj,GameObject *damager,float damage)
{
}

void ScriptImpClass::Killed(GameObject *obj,GameObject *shooter)
{
}

void ScriptImpClass::Sound_Heard(GameObject *obj,const CombatSound & sound)
{
}

void ScriptImpClass::Custom(GameObject *obj,int message,int param,GameObject *sender)
{
}

void ScriptImpClass::Action_Complete(GameObject *obj,int action,ActionCompleteReason reason)
{
}

void ScriptImpClass::Enemy_Seen(GameObject *obj,GameObject *seen)
{
}

void ScriptImpClass::Timer_Expired(GameObject *obj,int number)
{
}

void ScriptImpClass::Animation_Complete(GameObject *obj,const char *anim)
{
}

void ScriptImpClass::Poked(GameObject *obj,GameObject *poker)
{
}

void ScriptImpClass::Entered(GameObject *obj,GameObject *enter)
{
}

void ScriptImpClass::Exited(GameObject *obj,GameObject *exit)
{
}

GameObject *ScriptImpClass::Owner()
{
	return Attached;
}

GameObject **ScriptImpClass::Get_Owner_Ptr()
{
	return &Attached;
}

void ScriptImpClass::Set_Parameters_String(const char *params)
{
	if (!params || !*params)
		return;
	Get_Name();
	char *a = newstr(params);
	if (a[strlen(a) - 1] == '\n')
		a[strlen(a) - 1] = 0;
	int b = 1;
	{
		for (const char *r = a; *r;)
		{
			if (*r++ == ',')
				b++;
		}
	}
	Clear_Parameters();
	mArgC = b;
	mArgV = new char *[b];
	memset(mArgV,0,b << 2);
	memcpy(a,params,strlen(params));
	int i = 0;
	for (char *r = a; *r; i++)
	{
		char *r2 = r;
		while (*r2 && *r2 != ',')
			r2++;
		if (*r2)
			*r2++ = 0;
		Set_Parameter(i,r);
		r = r2;
	}
	if (mArgC != i) // never true
	{
		Set_Parameter(i,noparams);
	}
	delete[] a;
}

void ScriptImpClass::Get_Parameters_String(char *params,unsigned int size)
{
	*params = 0;
	unsigned int l = 0;
	for (int i = 0; i < mArgC; i++)
	{
		if (l >= size)
			return;
		if (i > 0)
		{
			l++;
			strcat(params,",");
		}
		const char *s = Get_Parameter(i);
		l += strlen(s);
		if (l > size)
			continue;
		strcat(params,s);
	}
}

void ScriptImpClass::Save(ScriptSaver & saver)
{
	SeralizeInfoStr *d;
	d = seralizeinfo;
	Commands->Begin_Chunk(saver,0x63736176);
	while (d)
	{
		Commands->Save_Data(saver,d->number,d->size,d->data);
		d = d->next;
	}
	Commands->End_Chunk(saver);
}

void ScriptImpClass::Load(ScriptLoader & loader)
{
	unsigned int x;
	int y;
	SeralizeInfoStr *d;
	while (Commands->Open_Chunk(loader,&x))
	{
		if (x == 0x63736176)
		{
			while (Commands->Load_Begin(loader,&y))
			{
				d = seralizeinfo;
				while (d)
				{
					if (d->number == y)
					{
						Commands->Load_Data(loader,d->size,d->data);
					}
					d = d->next;
				}
				Commands->Load_End(loader);
			}
		}
		Commands->Close_Chunk(loader);
	}
}

void ScriptImpClass::Save_Data(ScriptSaver & saver)
{
}

void ScriptImpClass::Load_Data(ScriptLoader & loader)
{
}

void ScriptImpClass::Register_Auto_Save_Variables()
{
}

int ScriptImpClass::CheckPlayerType(GameObject *obj,int type)
{
	if (type == 3)
	{
		GameObject *object = Owner();
		Vector3 pos = Commands->Get_Position(object);
		object = Commands->Get_A_Star(pos);
		if (object == obj)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	if (type == 2)
	{
		return 0;
	}
	int pltype = Commands->Get_Player_Type(obj);
	if (pltype == type)
	{
		return 0;
	}
	return 1;
}

void ScriptImpClass::Auto_Save_Variable(int num,int size,void *var)
{
	SeralizeInfoStr *d,*d2;
	if (num < 0 || num > 0xff || size > 0xfa)
		return;
	d = seralizeinfo;
	while (d)
	{
		if (d->number == num)
		{
			return;
		}
		d = d->next;
	}
	d2 = new SeralizeInfoStr;
	if (!d2)
	{
		seralizeinfo = 0;
		return;
	}
	d = seralizeinfo;
	d2->number = num;
	d2->size = size;
	d2->data = var;
	d2->next = d;
	seralizeinfo = d2;
}

ScriptImpClass::~ScriptImpClass() 
{
	while (seralizeinfo)
	{
		SeralizeInfoStr *s = seralizeinfo;
		seralizeinfo = s->next;
		delete s;
	}
	for (int i = 0;i < mArgC;i++)
	{
		delete[] mArgV[i];
	}
	delete[] mArgV;
}

GameObjObserverClass::~GameObjObserverClass() 
{
}

void ScriptImpClass::Clear_Parameters()
{
	if (mArgV)
	{
		while (mArgC--)
		{
			if (mArgV[mArgC])
				delete[] mArgV[mArgC];
		}
		delete[] mArgV;
	}
	mArgV = 0;
	mArgC = 0;
}

const char *ScriptImpClass::Get_Parameter(const char *v)
{
	return Get_Parameter(Get_Parameter_Index(v));
}

int ScriptImpClass::Get_Int_Parameter(const char *v)
{
	return atoi(Get_Parameter(Get_Parameter_Index(v)));
}

float ScriptImpClass::Get_Float_Parameter(const char *v)
{
	return (float)atof(Get_Parameter(Get_Parameter_Index(v)));
}

char *strtrim(char *v)
{
	if (v)
	{
		char *r = v;
		while (*r > 0 && *r < 0x21)
			r++;
		strcpy(v,r);
		r = v + strlen(v);
		while (r > v && r[-1] > 0 && r[-1] < 0x21)
			r--;
		*r = 0;
	}
	return v;
}

Vector3 ScriptImpClass::Get_Vector3_Parameter(const char *v)
{
	return Get_Vector3_Parameter(Get_Parameter_Index(v));
}

int ScriptImpClass::Get_Parameter_Index(const char *v)
{
	char b[0x2000];
	strncpy(b,Factory->GetParamDescription(),0x1fff);
	b[0x1fff] = 0;
	char *r = b;
	for (int i = 0; *r ; i++)
	{
		char *r2 = r;
		while (*r2 && *r2 != ',')
			r2++;
		if (*r2)
			*r2++ = 0;
		char *r3 = strpbrk(r,"=:\n");
		if (r3)
			*r3 = 0;
		strtrim(r);
		if (!_stricmp(r,v))
			return i;
		r = r2;
	}
	FILE *f = fopen("critical.txt","at");
	if (f)
	{
		fprintf(f,"Critical Scripts.dll error,parameter is %s\n",v);
		fclose(f);
	}
	return -1;
}

int ScriptImpClass::Get_Parameter_Count()
{
	return mArgC;
}

int ScriptImpClass::Get_Int_Parameter(int v)
{
	return atoi(Get_Parameter(v));
}

float ScriptImpClass::Get_Float_Parameter(int v)
{
	return (float)atof(Get_Parameter(v));
}

void ScriptImpClass::Set_Parameter(int pos,char const *v)
{
	if (mArgV[pos])
	{
		delete[] mArgV[pos];
	}
	mArgV[pos] = newstr(v);
}

const char *ScriptImpClass::Get_Parameter(int v)
{
	if ((v >= 0) && (v < mArgC))
	{
		return mArgV[v];
	}
	else
	{
		return noparams;
	}
}

Vector3 ScriptImpClass::Get_Vector3_Parameter(int v)
{
	Vector3 r;
	r.X = 0;
	r.Y = 0;
	r.Z = 0;
	if (sscanf(Get_Parameter(v),"%f %f %f",&r.X,&r.Y,&r.Z) != 3)
	{
		return Vector3(0,0,0);	
	}
	else
	{
		return r;
	}
}
