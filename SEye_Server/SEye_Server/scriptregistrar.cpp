/*	Renegade Scripts.dll
	Script Registrar
	Copyright 2007 Jonathan Wilson

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
#include "scripts.h"
ScriptFactory *ScriptRegistrar::mScriptFactories;

void ScriptRegistrar::UnregisterScript(ScriptFactory *ptr)
{
	ScriptFactory *x = mScriptFactories;
	ScriptFactory *z = 0;
	ScriptFactory *y;
	while (x)
	{
		y = x->GetNext();
		if (x == ptr)
		{
			if (!z)
			{
				mScriptFactories = y;
			}
			else
			{
				z->SetNext(y);
			}
		}
		z = x;
		x = y;
	}
}

void ScriptRegistrar::RegisterScript(ScriptFactory *ptr)
{
	ptr->SetNext(mScriptFactories);
	mScriptFactories = ptr;
}

ScriptFactory *ScriptRegistrar::GetScriptFactory(const char *name)
{
	ScriptFactory *x = mScriptFactories;
	if (!name)
	{
		return 0;
	}
	while (x)
	{
		if (!_stricmp(x->GetName(),name))
		{
			return x;
		}
		x = x->GetNext();
	}
	return 0;
}

ScriptFactory *ScriptRegistrar::GetScriptFactory(int number)
{
	ScriptFactory *x = mScriptFactories;
	int n = 0;
	while (x)
	{
		if (n == number)
		{
			return x;
		}
		x = x->GetNext();
		n++;
	}
	return 0;
}

int ScriptRegistrar::Count()
{
	ScriptFactory *x;
	int sn = 0;
	x = mScriptFactories;
	while (x)
	{
		sn++;
		x = x->GetNext();
	}
	return sn;
}

ScriptImpClass *ScriptRegistrar::CreateScript(const char *scriptName)
{
	ScriptFactory *x = mScriptFactories;
	if (!scriptName)
	{
		return 0;
	}
	while (x)
	{
		if (!_stricmp(x->GetName(),scriptName))
		{
			return x->Create();
		}
		x = x->GetNext();
	}
	return 0;
}
