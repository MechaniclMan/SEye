/*	Renegade Scripts.dll
	SSGM chat command classes and functions
	Copyright 2007 Whitedragon(MDB), Jonathan Wilson

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
#include "gmmain.h"

void ChatCommandClass::Error(int ID,int ErrorType,int Param) {
	if (ID) {
		if (ErrorType == 1) {
			Console_Input(StrFormat("ppage %d Insufficient parameters. This command requires atleast %d parameter(s), you only supplied %d.",ID,Info->NumParams,Param).c_str());
		}
	}
}

std::vector<ChatCommandInfo*> *ChatCommandList::List = 0;

void ChatCommandList::Add_Chat_Command(ChatCommandClass *Ptr,const char *Command,int ChatType,int NumParams,int GameMode) {
	ChatCommandInfo *Temp = new ChatCommandInfo;
	Temp->Ptr = Ptr;
	Temp->Command = Command;
	Temp->ChatType = ChatType;
	Temp->NumParams = NumParams;
	Temp->GameMode = GameMode;
	Ptr->Info = Temp;
	if (!List) {
		List = new std::vector<ChatCommandInfo*>;
	}
	List->push_back(Temp);
	
	for(std::vector<ChatCommandInfo *>::iterator it = List->begin(); it != List->end(); it++)
	{
		if(*it = Temp)
		{

		}
	}
}
