/*	Renegade Scripts.dll
	Team and player data related classes and engine calls
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
#include "engine_io.h"
#include "engine_net.h"
#include "engine_def.h"
#include "engine_math.h"
#include "engine_obj.h"
#include "engine_player.h"
#include "engine_weap.h"

typedef cPlayer *(*Find_Player) (int);
typedef char *(*FindTeam) (int team);
typedef int (*tts) (int team);
typedef void (*GetTeamColor) (Vector3 *color,int team);

Find_Player FindPlayer;
void *SetPlayerType;
void *GetPlayerCount;
FindTeam Find_Team;
tts TallyTeamSize;
GetTeamColor Get_Color_For_Team;
void *SetLadderPoints;
void *SetRung;
void *GetColor;
SList<cPlayer *> *PlayerList;

int THUNK Get_Player_Count()
IMPLEMENT_THUNK_RETURN(GetPlayerCount)
void THUNK cPlayer::Set_Player_Type(int type)
IMPLEMENT_THUNK(SetPlayerType)
void THUNK cPlayer::Set_Ladder_Points(int amount)
IMPLEMENT_THUNK(SetLadderPoints)
void THUNK cPlayer::Set_Rung(int amount)
IMPLEMENT_THUNK(SetRung)
Vector3 THUNK cPlayer::Get_Color()
IMPLEMENT_THUNK_RETURN_V(GetColor)

void InitEnginePlayer(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			GetColor = (void *)0x0040E530;
			SetLadderPoints = (void *)0x0040FC90;
			SetRung = (void *)0x00410790;
			FindPlayer = (Find_Player)0x004157E0;
			SetPlayerType = (void *)0x0040D600;
			GetPlayerCount = (void *)0x00417040;
			Get_Color_For_Team = (GetTeamColor)0x006D99E0;
			Find_Team = (FindTeam)0x0041DA10;
			TallyTeamSize = (tts)0x004170D0;
			PlayerList = (SList<cPlayer *> *)0x0081CFE8;
			break;
		case 1: //server.dat
			GetColor = (void *)0x0040E530;
			SetLadderPoints = (void *)0x0040FC90;
			SetRung = (void *)0x00410790;
			FindPlayer = (Find_Player)0x004157E0;
			SetPlayerType = (void *)0x0040D600;
			GetPlayerCount = (void *)0x00417040;
			Get_Color_For_Team = (GetTeamColor)0x006D9280;
			Find_Team = (FindTeam)0x0041DA10;
			TallyTeamSize = (tts)0x004170D0;
			PlayerList = (SList<cPlayer *> *)0x0081C1C8;
			break;
		case 2: //RH73
			GetColor = (void *)0x080A74D4;
			SetLadderPoints = (void *)0x080A84B0;
			SetRung = (void *)0x080A8560;
			FindPlayer = (Find_Player)0x080A9CDC;
			SetPlayerType = (void *)0x080A7438;
			GetPlayerCount = (void *)0x080AA7F0;
			Get_Color_For_Team = (GetTeamColor)0x08102AA8;
			Find_Team = (FindTeam)0x080BFBD4;
			TallyTeamSize = (tts)0x080AA84C;
			PlayerList = (SList<cPlayer *> *)0x08B9B0C8;
			break;
		case 3: //RH8
			GetColor = (void *)0x080A2EE6;
			SetLadderPoints = (void *)0x080A3BEE;
			SetRung = (void *)0x080A3C8E;
			FindPlayer = (Find_Player)0x080A510A;
			SetPlayerType = (void *)0x080A2E50;
			GetPlayerCount = (void *)0x080A5A62;
			Get_Color_For_Team = (GetTeamColor)0x080F5EB8;
			Find_Team = (FindTeam)0x080B82C4;
			TallyTeamSize = (tts)0x080A5AB6;
			PlayerList = (SList<cPlayer *> *)0x089A2200;
			break;
		default:
			GetColor = (void *)0;
			SetLadderPoints = (void *)0;
			SetRung = (void *)0;
			FindPlayer = (Find_Player)0;
			SetPlayerType = (void *)0;
			GetPlayerCount = (void *)0;
			Get_Color_For_Team = (GetTeamColor)0;
			Find_Team = (FindTeam)0;
			TallyTeamSize = (tts)0;
			break;
	}
}

const char *Get_Player_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return newstr("None");
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return newstr("None");
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return newstr("None");
	}
	return WideCharToChar(x->PlayerName);
}

const char *Get_Player_Name_By_ID(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return WideCharToChar(x->PlayerName);
}

void Change_Team_By_ID(int PlayerID,int Team)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Player_Type(Team);
	GameObject *obj = Get_GameObj(PlayerID);
	Commands->Destroy_Object(obj);
}

void Change_Team(GameObject *obj,int Team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return;
	}
	char *c = (char *)o;
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return;
	}
	x->Set_Player_Type(Team);
	Commands->Destroy_Object(obj);
}

void Change_Team_2(GameObject *obj,int Team)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return;
	}
	char *c = (char *)o;
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return;
	}
	x->Set_Player_Type(Team);
}

long Get_Player_ID(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return -1;
	}
	GameObject *o = As_SoldierGameObj(obj);
	if (!o)
	{
		return -1;
	}
	char *c = (char *)o;
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return -1;
	}
	return x->PlayerId;
}

GameObject *Get_GameObj(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if ((x) && (x->Owner.Reference))
	{
		return (GameObject *)x->Owner.Reference->obj;
	}
	return 0;
}

int Get_Team(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->PlayerType.Get();
}

int Get_Rank(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Rung.Get();
}

int Get_Kills(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Kills.Get();
}

int Get_Deaths(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Deaths.Get();
}

float Get_Score(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Score.Get();
}

float Get_Money(int PlayerID)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return 0;
	}
	return x->Money.Get();
}

float Get_Kill_To_Death_Ratio(int PlayerID)
{
	int kills = Get_Kills(PlayerID);
	int deaths = Get_Deaths(PlayerID);
	if (deaths <= 0)
	{
		return -1.0;
	}
	return (float)kills/(float)deaths;
}

void Get_Player_Color(int PlayerID, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	Vector3 v;
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	v = x->Get_Color();
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

bool Purchase_Item(GameObject *obj,int cost)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return false;
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	return x->Purchase_Item(cost);
}

void Set_Money(int PlayerID,float amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Money(amount);
}

void Set_Score(int PlayerID,float amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Score(amount);
}

void Set_Ladder_Points(int PlayerID,int amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Ladder_Points(amount);
}

void Set_Rung(int PlayerID,int amount)
{
	cPlayer *x = FindPlayer(PlayerID);
	if (!x)
	{
		return;
	}
	x->Set_Rung(amount);
}

int Tally_Team_Size(int team)
{
	return TallyTeamSize(team);
}

float Get_Team_Score(int team)
{
	char *teamdata = Find_Team(team);
	teamdata += 0x6C0;
	return *((float *)teamdata);
}

void Get_Team_Color(unsigned int team, unsigned int *red, unsigned int *green, unsigned int *blue)
{
	Vector3 v;
	Get_Color_For_Team(&v,team);
	*red = (unsigned int)(v.X*255);
	*green = (unsigned int)(v.Y*255);
	*blue = (unsigned int)(v.Z*255);
}

GameObject *Get_GameObj_By_Player_Name(const char *name)
{
	for (GenericSLNode* PlayerIter = PlayerList->HeadNode; (PlayerIter != NULL); PlayerIter = PlayerIter->NodeNext)
	{
		cPlayer *p = (cPlayer *)PlayerIter->NodeData;
		if (!p->IsActive)
		{
			continue;
		}
		const char *c = WideCharToChar(p->PlayerName.Peek_Buffer());
		if (!_stricmp(c,name))
		{
			delete[] c;
			return (GameObject *)p->Owner.Reference->obj;
		}
		delete[] c;
	}
	return 0;
}

GameObject *Find_First_Player(int Team)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = (GameObject *)x->NodeData;
		if (o && As_SoldierGameObj(o))
		{
			if (Commands->Is_A_Star(o))
			{
				if ((Get_Object_Type(o) == Team) || (Team == 2))
				{
					return o;
				}
			}
		}
		x = x->NodeNext;
	}
	return 0;
}

bool Change_Player_Team(GameObject *obj,bool Retain_Score,bool Retain_Money,bool Show_Host_Message)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return false;
	}
	if (!Commands->Is_A_Star(obj))
	{
		return false;
	}
	Disarm_All_C4(Get_Player_ID(obj));
	float Score = Commands->Get_Points(obj);
	float Credits = Commands->Get_Money(obj);
	Commands->Give_Points(obj,(Score*-1),false);
	if (Score < 0)
	{
		Commands->Give_Money(obj,Score,false);
	}
	Commands->Give_Money(obj,(Credits*-1),false);
	if (!Commands->Get_Player_Type(obj))
	{
		Change_Team(obj,1);
	}
	else if (Commands->Get_Player_Type(obj) == 1)
	{
		Change_Team(obj,0);
	}
	if (Retain_Score)
	{
		Commands->Give_Points(obj,Score,false);
		if (Score > 0)
		{
			Commands->Give_Money(obj,(Score*-1),false);
		}
	}
	if (Retain_Money)
	{
		Commands->Give_Money(obj,Credits,false);
	}
	if (Show_Host_Message)
	{
		char outputmsg[100];
		const char *name = Get_Player_Name(obj);
		sprintf(outputmsg,"msg %s switched teams",name);
		delete[] name;
		Console_Input(outputmsg);
	}
	return true;
}

#define LOWER(chr) ((chr >= 'A') && (chr <= 'Z') ? chr+32 : chr)

char *stristr(const char *m_pStr1, const char *m_pStr2)
{
	register char *m_pCP = (char *)m_pStr1;
	register char *m_pS1, *m_pS2;
	while (*m_pCP)
	{
		m_pS1 = m_pCP;
		m_pS2 = (char *) m_pStr2;
		while (*m_pS1 && *m_pS2 && !(LOWER(*m_pS1) - LOWER(*m_pS2)))
		{
			m_pS1++, m_pS2++;
		}
		if (!*m_pS2)
		{
			return m_pCP;
		}
		m_pCP++;
	}
	return NULL;
}

GameObject *Get_Part_Name(const char *name1)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	int count = 0;
	GameObject *current = 0;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o)
		{
			const char *name = Get_Player_Name(o);
			if (!stristr(name,name1))
			{
				current = o;
				count++;
			}
			delete[] name;
		}
		x = x->NodeNext;
	}
	if ((count == 1) && (current) && (Commands->Get_ID(current)))
	{
		return current;
	}
	else
	{
		return 0;
	}
}

int Get_Part_Names(const char *name1)
{
	GenericSLNode *x = BaseGameObjList->HeadNode;
	int count = 0;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o)
		{
			const char *name = Get_Player_Name(o);
			if (!stristr(name,name1))
			{
				count++;
			}
			delete[] name;
		}
		x = x->NodeNext;
	}
	return count;
}

int Get_Team_Player_Count(int Team)
{
	int Total = 0;
	GenericSLNode *x = BaseGameObjList->HeadNode;
	while (x)
	{
		GameObject *o = As_SoldierGameObj((GameObject *)x->NodeData);
		if (o && Get_Object_Type(o) == Team)
		{
			Total++;
		}
		x = x->NodeNext;
	}
	return Total;
}

void Send_Custom_All_Players(int message,GameObject *sender,int team)
{
	if (!Commands->Get_ID(sender) || !sender)
	{
		return;
	}
	for (GenericSLNode* PlayerIter = PlayerList->HeadNode; (PlayerIter != NULL); PlayerIter = PlayerIter->NodeNext)
	{
		cPlayer *p = (cPlayer *)PlayerIter->NodeData;
		if (!p->IsActive)
		{
			continue;
		}
		if ((p->PlayerType.Get() == team) || (team == 2))
		{
			Commands->Send_Custom_Event(sender,(GameObject *)p->Owner.Reference->obj,message,0,0);
		}
	}
}

float Steal_Team_Credits(float percentage, int team)
{
	float theft = 0;
	for (GenericSLNode* PlayerIter = PlayerList->HeadNode; (PlayerIter != NULL); PlayerIter = PlayerIter->NodeNext)
	{
		cPlayer *p = (cPlayer *)PlayerIter->NodeData;
		if (!p->IsActive)
		{
			continue;
		}
		if (Commands->Get_Player_Type((GameObject *)p->Owner.Reference->obj) == team)
		{
			float credits = p->Money.Get();
			credits = credits * percentage;
			theft += credits;
			p->Increment_Money(-credits);
		}
	}
	return theft;
}

float Get_Team_Credits(int team)
{
	float count = 0;
	for (GenericSLNode* PlayerIter = PlayerList->HeadNode; (PlayerIter != NULL); PlayerIter = PlayerIter->NodeNext)
	{
		cPlayer *p = (cPlayer *)PlayerIter->NodeData;
		if (!p->IsActive)
		{
			continue;
		}
		if (Commands->Get_Player_Type((GameObject *)p->Owner.Reference->obj) == team)
		{
			count += p->Money.Get();
		}
	}
	return count;
}

int Get_Player_Type(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return 0;
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return 0;
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return 0;
	}
	return x->PlayerType.Get();
}

const wchar_t *Get_Wide_Player_Name(GameObject *obj)
{
	if (!Commands->Get_ID(obj) || !obj)
	{
		return L"None";
	}
	GameObject *o = As_SoldierGameObj(obj);
	char *c = (char *)o;
	if (!o)
	{
		return L"None";
	}
	c += 0x960;
	cPlayer *x = (cPlayer *)*(unsigned int *)c;
	if (!x)
	{
		return L"None";
	}
	return x->PlayerName.Peek_Buffer();
}
