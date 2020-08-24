/*	Renegade Scripts.dll
	Network related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//declared here because we dont have it
class BitStreamClass;
struct Update {
	unsigned int LastUpdateTime;
	short UpdateRate;
	unsigned char HintCount;
};

enum DIRTY_BIT {
	DB_CREATION = 0x0F,
	DB_RARE = 7,
	DB_OCCASIONAL = 3,
	DB_FREQUENT = 1,
};

class NetworkObjectClass {
public:
	unsigned int NetworkID;
	Update UpdateData[128];
	char DirtyBits[128];
	unsigned int ImportStateCount;
	unsigned int LastClientsideUpdateTime;
	unsigned int CreationTime;
	unsigned int ClientUpdateCount;
	unsigned int ClientUpdateFrequency;
	bool DeletePending;
	unsigned char PacketType;
	unsigned int LastDamaged;
	unsigned int LastDamager;
	unsigned char FrequentUpdateExportSize;
	float CachedPriority;
	float CachedPriority2[128];
	bool UnreliableOverride;
	virtual ~NetworkObjectClass();
	virtual unsigned int Get_Network_Class_ID();
	virtual void Import_Creation(BitStreamClass &BitStream);
	virtual void Import_Rare(BitStreamClass &BitStream);
	virtual void Import_Occasional(BitStreamClass &BitStream);
	virtual void Import_Frequent(BitStreamClass &BitStream);
	virtual void Export_Creation(BitStreamClass &BitStream);
	virtual void Export_Rare(BitStreamClass &BitStream);
	virtual void Export_Occasional(BitStreamClass &BitStream);
	virtual void Export_Frequent(BitStreamClass &BitStream);
	virtual void Network_Think();
	virtual void Set_Delete_Pending();
	virtual void Delete() = 0;
	virtual void Set_Object_Dirty_Bit(DIRTY_BIT Bit, bool Set);
	virtual void Set_Object_Dirty_Bit(int Client_ID, DIRTY_BIT Bit, bool Set);
	virtual void Clear_Object_Dirty_Bits();
	virtual bool Get_Object_Dirty_Bit(int Client_ID,DIRTY_BIT Bit);
	virtual bool Get_Object_Dirty_Bits(int Client_ID);
	virtual bool Set_Object_Dirty_Bits(int Client_ID,unsigned char Bits);
	virtual bool Is_Client_Dirty(int Client_ID);
	virtual int Get_Vis_ID();
	virtual bool Get_World_Position(Vector3 &Position);
	virtual float Get_Filter_Distance();
	virtual bool Is_Tagged();
	virtual void Get_Description(StringClass &Description);
	virtual float Get_Cached_Priority();
};

void InitEngineNet(unsigned int exe);
void Destroy_Connection(int PlayerID); //Drop a player from the game by cutting off their network link
const char *Get_IP_Address(int PlayerID); //gets the IP address for a player as a string in 1.2.3.4 format
const char *Get_IP_Port(int PlayerID); //gets the IP address and port for a player as a string in 1.2.3.4;5 format
int Get_Bandwidth(int PlayerID); //Get players current bandwidth (same as set by sbbo)
unsigned long Get_Ping(int PlayerID); //get the ping of a player
unsigned long Get_Kbits(int PlayerID); //get the Kbits/s of a player
