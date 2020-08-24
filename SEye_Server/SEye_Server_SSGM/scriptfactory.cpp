/*	Renegade Scripts.dll
	Script Factory
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

ScriptFactory::ScriptFactory(char *n,char *p)
{
	name = n;
	params = p;
	next = 0;
	ScriptRegistrar::RegisterScript(this);
}

ScriptFactory *ScriptFactory::GetNext()
{
	return next;
}

char *ScriptFactory::GetName()
{
	return name;
}

char *ScriptFactory::GetParamDescription()
{
	return params;
}

ScriptFactory::~ScriptFactory()
{
	ScriptRegistrar::UnregisterScript(this);
	name = 0;
	params = 0;
}

void ScriptFactory::SetNext(ScriptFactory *link)
{
	next = link;
}
