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

#ifndef COMMANDS_H
#define COMMANDS_H

#define CHATTYPE_PUBLIC 0
#define CHATTYPE_TEAM 1
#define CHATTYPE_ALL 2

#define GAMEMODE_ALL 0
#define GAMEMODE_AOW 1
#define GAMEMODE_CTF 2
#define GAMEMODE_SNIPING 3
#define GAMEMODE_500SNIPING 4
#define GAMEMODE_INFANTRY 5

class TokenClass {
private:
	std::vector<std::string> Tokens;
	int vecsize;
	void Build(const std::string &Text,int Pos) {
		Tokens.clear();
		vecsize = 0;
		char *Tokenz = new char[Text.size()+1];
		sprintf(Tokenz,"%s",Text.c_str());
		char *p = strtok(Tokenz," ");
		std::string Temp2,All;
		if (!Pos) {
			Tokens.push_back(Text);
		}
		else {
			int i = 0;
			while (i < Pos) {
				p = strtok(0," ");
				++i;
			}
		}
		while (p) {
			Temp2 = p;
			Tokens.push_back(Temp2);
			p = strtok(0," ");
			++vecsize;
			if (Pos) {
				All += Temp2;
				if (p) All += std::string(" ");
			}
		}
		if (Pos) {
			Tokens.insert(Tokens.begin(),All);
		}
		delete[] Tokenz;
	}

	public:

	TokenClass(const TokenClass &Copy) {
		Tokens = Copy.Tokens;
		vecsize = Copy.vecsize;
	}
	TokenClass() { }
	TokenClass(const std::string &Text,int Pos = 0) {
		Build(Text,Pos);
	}

	TokenClass& operator=(const TokenClass &Copy) {
		Tokens = Copy.Tokens;
		vecsize = Copy.vecsize;
		return *this;
	}

	TokenClass& operator=(const std::string &Text) {
		Build(Text,0);
		return *this;
	}

	inline std::string operator[](int Pos) const {
		if (vecsize < Pos) {
			return "";
		}
		return Tokens[Pos];
	}

	std::string operator()(int Start,int End = 0) const {
		if (vecsize < Start || vecsize < End) {
			return "";
		}
		std::string Ret;
		if (!End) {
			End = Tokens.size();
		}
		int i = Start;
		while (i <= End && i <= vecsize) {
			Ret += Tokens[i];
			++i;
			if (i <= End) Ret += std::string(" ");
		}
		return Ret;
	}

	inline int size() const {
		return vecsize;
	}

	inline void erase(int Pos) {
		if (vecsize < Pos) return;
		Tokens.erase(Tokens.begin()+Pos);
		vecsize--;
	}

	inline void replace(int Pos,const std::string &Rep) {
		if (vecsize < Pos || !Pos) return;
		Tokens[Pos] = Rep;;
	}

	inline void eraseglobal(int Pos) {
		if (vecsize < Pos) return;
		std::string Temp = Tokens[0];
		Temp.replace(Temp.find(Tokens[Pos]),Tokens[Pos].size()+1,"");
		Tokens[0] = Temp;
		erase(Pos);
	}

	inline void Add(const std::string &Text,int Pos = 0) {
		if (!Pos) {
			Tokens.push_back(Text);
			++vecsize;
		}
		else if (vecsize < Pos) {
			return;
		}
		else {
			Tokens.insert(Tokens.begin()+Pos,Text);
			++vecsize;
		}
	}
};

struct DataStruct;
struct ChatCommandInfo;

class ChatCommandClass {
public:
	ChatCommandInfo *Info;
	virtual void Error(int ID,int ErrorType,int Param);
	virtual void Triggered(int ID,const TokenClass &Text,int ChatType) = 0;
};

struct ChatCommandInfo {
	std::string Command;
	ChatCommandClass *Ptr;
	int ChatType;
	int NumParams;
	int GameMode;
};

class ChatCommandList {
public:
	static std::vector<ChatCommandInfo*> *List;
	static void Add_Chat_Command(ChatCommandClass *Ptr,const char *Command,int ChatType,int NumParams,int GameMode);
};

template <class T> class ChatCommandRegistrant : public ChatCommandList {
public:
	ChatCommandRegistrant(const char *Command,int ChatType,int NumParams,int GameMode) {
		char *Comm = newstr(Command);
		char *p = strtok(Comm,";");
		while (p) {
			ChatCommandClass *Temp = new T;
			Add_Chat_Command(Temp,p,ChatType,NumParams,GameMode);
			p = strtok(0,";");
		}
		delete[] Comm;
	}

};

#endif
