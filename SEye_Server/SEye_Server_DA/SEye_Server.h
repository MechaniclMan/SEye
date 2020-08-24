#pragma once


#include "general.h"
#include "da_event.h"
#include "da_gamemode.h"
#include "da_gamefeature.h"
#include "da_player.h"
#include "da_gameobj.h"
#include "scripts.h"


class SEyeServerClass : public DAEventClass, public DAGameFeatureClass {
private:
	virtual void Init();
	virtual void Shutdown();
	virtual void Object_Created_Event(GameObject *obj);
	virtual void Level_Loaded_Event();
	//virtual void Game_Over_Event();
	virtual void Settings_Loaded_Event();
	//virtual void Think();
	virtual void Player_Join_Event(cPlayer *Player);
	//virtual void Player_Leave_Event(cPlayer *Player);
	//virtual bool Chat_Command_Event(cPlayer *Player,TextMessageEnum Type,const StringClass &Command,const DATokenClass &Text,int ReceiverID);
	//virtual bool Chat_Event(cPlayer *Player,TextMessageEnum Type,const wchar_t *Message,int ReceiverID);
	//virtual bool Radio_Event(cPlayer *Player,int PlayerType,int AnnouncementID,int IconID,AnnouncementEnum AnnouncementType);
	//virtual bool Refill_Event(SoldierGameObj *Purchaser);
	//virtual bool Suicide_Event(cPlayer *Player);
	//virtual bool PowerUp_Grant_Request_Event(cPlayer *Player,const PowerUpGameObjDef *PowerUp,PowerUpGameObj *PowerUpObj);
	//virtual int Character_Purchase_Request_Event(BaseControllerClass *Base,cPlayer *Player,float &Cost,const SoldierGameObjDef *Item);
	////virtual int Vehicle_Purchase_Request_Event(BaseControllerClass *Base,cPlayer *Player,float &Cost,const VehicleGameObjDef *Item);
	//virtual int PowerUp_Purchase_Request_Event(BaseControllerClass *Base,cPlayer *Player,float &Cost,const PowerUpGameObjDef *Item);
	//bool Vehicle_Entry_Request(VehicleGameObj *Vehicle,int &Seat);
	//virtual bool Team_Change_Request_Event(cPlayer *Player);
	//virtual void Team_Change_Event(cPlayer *Player);
	//virtual void DA_Log_Event(const char *Header,const char *Output);
	//virtual void Character_Purchase_Event(cPlayer *Player,float Cost,const SoldierGameObjDef *Item);
	//virtual void Vehicle_Purchase_Event(cPlayer *Player,float Cost,const VehicleGameObjDef *Item);
	//virtual void PowerUp_Purchase_Event(cPlayer *Player,float Cost,const PowerUpGameObjDef *Item);
	//virtual bool Damage_Request_Event(DamageableGameObj *Victim,ArmedGameObj *Damager,float &Damage,unsigned int &Warhead,float Scale,DADamageType::Type Type);
	//virtual bool Stock_Client_Damage_Request_Event(DamageableGameObj *Victim,ArmedGameObj *Damager,float Damage,uint Warhead);
	//virtual bool TT_Client_Damage_Request_Event(DamageableGameObj *Victim,ArmedGameObj *Damager,const AmmoDefinitionClass *Ammo,const char *Bone);
	//virtual void Kill_Event(DamageableGameObj *Victim,ArmedGameObj *Killer,float Damage,unsigned int Warhead,float Scale,DADamageType::Type Type);
	//virtual void Object_Destroyed_Event(GameObject *obj);
	~SEyeServerClass()
	{
		Shutdown();
	}

};



class TCPSocket
{
	SOCKET Socket;
	char Host[256];
	int Port;
	bool Connected;
	int Mode;

	TCPSocket(SOCKET &_Socket, int _Mode);

public:
	
	TCPSocket();
	TCPSocket(SOCKET &_Socket);
	TCPSocket(TCPSocket &_Socket);
	TCPSocket(const char *Host, int Port);
	TCPSocket(const char *IP, int Port, int Backlog);
	~TCPSocket();
	
	bool Client(const char *Host, int Port);
	bool Server(const char *IP, int Port, int Backlog);
	bool Accept(TCPSocket *NewConnection);

	bool Is_Connected();
	bool Is_DataAvaliable();
	bool Is_ConnectionWaiting();

	bool RecviveData(char *Data, int Length);
	bool SendData(const char *Data, int Length);

	bool Destroy();
};

class SEye_Server
{
public:
	static void Load();
	static void Unload();
	static void Level_Loaded();
	static void ObjectCreated(GameObject *o);
	static void ChatHook(int ID, int Type, const wchar_t *Msg);
};

class SEye
{
public:
	class SEyePacket
	{
		unsigned char _Size;
		unsigned char _Type;
		unsigned char _Data[512];
		

	public:
		
		SEyePacket()
		{
			memset(this, 0, sizeof(SEyePacket));
		}

		void Unpack(char *Data, int Size);
		void Unpack_String(char *Data);
		void Pack(const char *Data, int Size);
		void Pack_String(const char *Data);
		void SetType(unsigned char Type);
		unsigned char GetType();
		int GetSize();

		template<class _T> void Pack(const _T Data);
		template<class _T> void Unpack(_T *Data);
		template<class _T> void Unpack(_T &Data);

		template<class _T, int _N> void Pack(const _T *Data);
		template<class _T, int _N> void Unpack(_T *Data);
	};
};