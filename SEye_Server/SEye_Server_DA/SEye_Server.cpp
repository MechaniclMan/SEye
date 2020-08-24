#include "general.h"
#include "scripts.h"
#include "engine.h"
#include "engine_da.h"
#include "da_settings.h"
#include "functions.h"
#include "GameObjManager.h"

#include "Winsock2.h"
#include <windows.h>
#include "time.h"
#include "SEye_Server.h"


#pragma warning(disable: 4127)

TCPSocket *t_Client = 0;
TCPSocket *t_Sock = 0;
clock_t PingPong = 0;

unsigned int PingData = 0;

//int i_PacketBytes = 0;
//SEye::SEyePacket sp_tempPacket;

void PacketReceived(SEye::SEyePacket &Packet)
{
	Console_Output("Packet!\n");
	//PingPong = clock();
	if(Packet.GetType() == 0)
	{
		bool From;
		unsigned int Data;

		SEye::SEyePacket Bounce;
		memcpy((void *)&Bounce, (void *)&Packet, sizeof(SEye::SEyePacket));
		
		Packet.Unpack<bool>(From);
		Packet.Unpack<unsigned int>(Data);

		if(From) //server
		{
			PingPong = clock();
			PingData = 0;
		}
		else //client
		{
			t_Client->SendData((const char *)&Bounce, Bounce.GetSize());
		}
	}

	if(Packet.GetType() == 17)
	{
		unsigned int ObjectID;
		unsigned int HintID;
		Packet.Unpack<unsigned int>(ObjectID);
		Packet.Unpack<unsigned int>(HintID);

		if(!Commands->Find_Object(ObjectID))
		{
			Packet.Pack<unsigned int>(HintID);
			Packet.Pack<unsigned int>(0);
		}
		else
		{
			Packet.Pack<unsigned int>(HintID);
			Packet.Pack<unsigned int>(ObjectID);
		}
		t_Client->SendData((const char *)&Packet, Packet.GetSize());
	}
}


class SEye_Socket : public DAGameObjObserverClass 
{
public:
	static int i_PacketBytes;
	static SEye::SEyePacket sp_tempPacket;

	virtual const char *Get_Name() {
		return "SEye_Socket";
	}

	virtual void Init()
	{
		Console_Output("SYe Socket!\n");
		Start_Timer(1, 1.0);
	}

	virtual void Timer_Expired(GameObject *o, int Number)
	{
		Start_Timer(1, 0.1f);
		if(t_Client)
		{
			if(!t_Client->Is_Connected())
			{
				t_Client->Destroy();
				delete t_Client;
				t_Client = 0;
				Console_Output("SEye client disconnected!\n");
			}
			else
			{
				if(clock() - PingPong > 30*1000 && PingData == 0)
				{
					bool From = 1;
					unsigned int r = (unsigned int)rand();
					SEye::SEyePacket _Packet;
					_Packet.SetType(0);
					_Packet.Pack<unsigned int>(r);
					_Packet.Pack<bool>(From);
					t_Client->SendData((const char *)&_Packet, _Packet.GetSize());
					PingData = r;
				}
				if(clock() - PingPong > 60 * 1000 && PingData >= 0)
				{
					t_Client->Destroy();
					delete t_Client;
					t_Client = 0;

					Console_Output("SEye client disconnected (ping timeout).\n");
					return;
				}
				while(t_Client->Is_DataAvaliable())
				{
					t_Client->RecviveData(((char *)&sp_tempPacket)+(i_PacketBytes), 1);
					if(i_PacketBytes >= 3)
					{
						if(i_PacketBytes >= sp_tempPacket.GetSize()-1)
						{
							PacketReceived(sp_tempPacket);
							memset((void *)&sp_tempPacket, 0, sizeof(sp_tempPacket));
							i_PacketBytes = 0;
							return;
						}
					}
					i_PacketBytes++;
				}
			}
		}
		if(t_Sock && (t_Sock->Is_ConnectionWaiting() && !t_Client))
		{
			t_Client = new TCPSocket;
			if(!t_Sock->Accept(t_Client))
			{
				Console_Output("New client rejected\n");
				delete t_Client;
				t_Client = 0;
				return;
			}

			Console_Output("New client accepted\n");

			PingPong = clock();
			PingData = 0;
			SEye::SEyePacket sp_Header;
			sp_Header.SetType(1);
			sp_Header.Pack_String(The_Game()->MapName);
			Console_Output("\"%s\"\n", The_Game()->MapName);
			sp_Header.Pack((const char *)&The_Game()->TimeRemaining_Seconds, 4);
			if(!t_Client->SendData((const char *)&sp_Header, sp_Header.GetSize()))
			{
				Console_Output("Unable to send packet\n");
				delete t_Client;
				t_Client = 0;
				return;
			}	
			

			for (SLNode<cPlayer>* PlayerIter = Get_Player_List()->Head(); (PlayerIter != NULL); PlayerIter = PlayerIter->Next())
			{
				cPlayer *p = PlayerIter->Data();
				if(p && p->Is_Alive_And_Kicking() )
				{
					const char *Name = WideCharToChar(p->PlayerName);
					SEye::SEyePacket PlayersUpdate;
					PlayersUpdate.SetType(2);
					PlayersUpdate.Pack_String(Name);
					PlayersUpdate.Pack_String(Commands->Get_Preset_Name(p->Get_GameObj() ));
					Vector3 pos = Commands->Get_Position(p->Get_GameObj());
					float X = pos.X;
					float Y = pos.Y;
					int HP = int(Commands->Get_Max_Health(p->Get_GameObj())+Commands->Get_Max_Shield_Strength(p->Get_GameObj()));
					int Team = p->Get_Player_Type();
					int ObjectID = Commands->Get_ID(p->Get_GameObj());

					PlayersUpdate.Pack((char *)&Y, 4);
					PlayersUpdate.Pack((char *)&X, 4);
					PlayersUpdate.Pack((char *)&HP, 4);
					PlayersUpdate.Pack((char *)&Team, 1);
					PlayersUpdate.Pack((char *)&ObjectID, 4);

					delete []Name;
					
					t_Client->SendData((const char *)&PlayersUpdate, PlayersUpdate.GetSize());
				}
			}

			for (SLNode<SmartGameObj> *z = GameObjManager::SmartGameObjList.Head();z;z = z->Next()) 
			{
				GameObject *o = (GameObject *)z->Data();
				if (o && o->As_VehicleGameObj())
				{
					if(!o)
					{
						continue;
					}

					if(Get_Vehicle_Mode(o) == 4)
					{
						continue;
					}

					Vector3 pos = Commands->Get_Position(o);
					SEye::SEyePacket VehicleUpdate;
					VehicleUpdate.SetType(3);
				
					VehicleUpdate.Pack_String(Commands->Get_Preset_Name(o));
					VehicleUpdate.Pack<float>(pos.Y);
					VehicleUpdate.Pack<float>(pos.X);
					VehicleUpdate.Pack<unsigned int>(int(Commands->Get_Max_Health(o)+Commands->Get_Max_Shield_Strength(o)));
					VehicleUpdate.Pack<char>((char)Get_Object_Type(o));
					VehicleUpdate.Pack<unsigned int>(Commands->Get_ID(o));

					t_Client->SendData((const char *)&VehicleUpdate, VehicleUpdate.GetSize());


					GameObject *driver = Get_Vehicle_Driver(o);
					if(driver)
					{
						SEye::SEyePacket VehicleEntered;
						VehicleEntered.SetType(14);
						VehicleEntered.Pack<unsigned int> (Commands->Get_ID(driver));
						VehicleEntered.Pack<unsigned int> (Commands->Get_ID(o));
						t_Client->SendData((const char *)&VehicleEntered, VehicleEntered.GetSize());
					}

					for(int y = 0; y < 4; y++)
					{
						GameObject *occ = Get_Vehicle_Occupant(o, y);
						if(occ)
						{
							SEye::SEyePacket VehicleEntered;
							VehicleEntered.SetType(14);
							VehicleEntered.Pack<unsigned int> (Commands->Get_ID(occ));
							VehicleEntered.Pack<unsigned int> (Commands->Get_ID(o));
							t_Client->SendData((const char *)&VehicleEntered, VehicleEntered.GetSize());
						}
					}
				}
			}

			for (SLNode<BuildingGameObj> *z = GameObjManager::BuildingGameObjList.Head(); z; z = z->Next())
			{
				GameObject *o = z->Data();
				if(!o)
				{
					continue;
				}
				Vector3 pos = Commands->Get_Position(o);
				unsigned int nHP = int(Commands->Get_Max_Health(o)+Commands->Get_Max_Shield_Strength(o));
				SEye::SEyePacket BuildingUpdate;
				BuildingUpdate.SetType(4);
				
				BuildingUpdate.Pack_String (Commands->Get_Preset_Name(o));
				BuildingUpdate.Pack<float>(pos.Y);
				BuildingUpdate.Pack<float>(pos.X);
				BuildingUpdate.Pack<unsigned int> (nHP);
				BuildingUpdate.Pack<char> ((char)Get_Object_Type(o));
				BuildingUpdate.Pack<unsigned int> (Commands->Get_ID(o));
				t_Client->SendData((const char *)&BuildingUpdate, BuildingUpdate.GetSize());
			}
		}
	}
};

int SEye_Socket::i_PacketBytes = 0;
SEye::SEyePacket SEye_Socket::sp_tempPacket;


class SEye_Player_Update : public DAGameObjObserverClass {
public:

	bool CanSendDamage;

	virtual const char *Get_Name() {
		return "SEye_Player_Update";
	}

	virtual void Timer_Expired(GameObject *o, int Number)
	{
		if(Number == 2)
		{
			CanSendDamage = 1;
			return;
		}
		if(t_Client)
		{
			Vector3 pos = Commands->Get_Position(o);
			float X = pos.X;
			float Y = pos.Y;
			int HP = int(Commands->Get_Health(o)+Commands->Get_Shield_Strength(o));
			int ObjectID = Commands->Get_ID(o);

			SEye::SEyePacket PlayerUpdate;
			PlayerUpdate.SetType(5);
			PlayerUpdate.Pack((char *)&HP, 4);
			PlayerUpdate.Pack((char *)&Y, 4);
			PlayerUpdate.Pack((char *)&X, 4);
			PlayerUpdate.Pack((char *)&ObjectID, 4);

			t_Client->SendData((const char *)&PlayerUpdate, PlayerUpdate.GetSize());
		}
		Start_Timer(1, 1.0);
	}
	virtual void Init(GameObject *o)
	{
		CanSendDamage = 1;
		if(t_Client)
		{
			SEye::SEyePacket PlayersUpdate;
			PlayersUpdate.SetType(2);
			PlayersUpdate.Pack_String(Get_Player_Name(o));
			PlayersUpdate.Pack_String(Commands->Get_Preset_Name(o));
			Vector3 pos = Commands->Get_Position(o);
			float X = pos.X;
			float Y = pos.Y;
			int HP = int(Commands->Get_Max_Health(o)+Commands->Get_Max_Shield_Strength(o));
			int Team = Get_Team(Get_Player_ID(o));
			int ObjectID = Commands->Get_ID(o);

			PlayersUpdate.Pack((char *)&Y, 4);
			PlayersUpdate.Pack((char *)&X, 4);
			PlayersUpdate.Pack((char *)&HP, 4);
			PlayersUpdate.Pack((char *)&Team, 1);
			PlayersUpdate.Pack((char *)&ObjectID, 4);

			t_Client->SendData((const char *)&PlayersUpdate, PlayersUpdate.GetSize());
		}

		Start_Timer(1, 1.0);
	}

	virtual void Destroyed(GameObject *o)
	{
		if(t_Client)
		{
			SEye::SEyePacket PlayerUpdate;
			PlayerUpdate.SetType(8);
			PlayerUpdate.Pack<unsigned int>(Commands->Get_ID(o));
			t_Client->SendData((const char *)&PlayerUpdate, PlayerUpdate.GetSize());
		}
	}

	virtual void Killed_Received(GameObject *o, GameObject *)
	{
		if(t_Client)
		{
			SEye::SEyePacket PlayerUpdate;
			PlayerUpdate.SetType(8);
			PlayerUpdate.Pack<unsigned int>(Commands->Get_ID(o));
			t_Client->SendData((const char *)&PlayerUpdate, PlayerUpdate.GetSize());
		}
	}

	virtual void Damaged_Received(GameObject *o, GameObject *Damager, float damage)
	{
		if(!Damager)
		{
			return;
		}
		if(damage == 0)
		{
			return;
		}

		if(Damager == o)
		{
			return;
		}

		if(!CanSendDamage)
		{
			return;
		}
		CanSendDamage = 0;
		Start_Timer(2, 1.0);


		if(t_Client)
		{
			SEye::SEyePacket PlayerDamaged;
			PlayerDamaged.SetType(9);
			PlayerDamaged.Pack<unsigned int> (Commands->Get_ID(o));
			PlayerDamaged.Pack<unsigned int> (Commands->Get_ID(Damager));
			PlayerDamaged.Pack<bool> (damage > 0 ? 1 : 0);
			t_Client->SendData((const char *)&PlayerDamaged, PlayerDamaged.GetSize());
		}
	}
};

class SEye_Vehicle_Update : public DAGameObjObserverClass {
public:

	bool CanSendDamage;

	virtual const char *Get_Name() {
		return "SEye_Vehicle_Update";
	}

	virtual void Init() {
		Start_Timer(1, 1.0);
	}

	virtual void Timer_Expired(GameObject *o, int Number)
	{
		if(Number == 2)
		{
			CanSendDamage = 1;
			return;
		}
		if(t_Client)
		{
			Vector3 pos = Commands->Get_Position(o);
			float X = pos.X;
			float Y = pos.Y;
			int HP = int(Commands->Get_Health(o)+Commands->Get_Shield_Strength(o));
			int ObjectID = Commands->Get_ID(o);

			SEye::SEyePacket VehicleUpdate;
			VehicleUpdate.SetType(6);

			VehicleUpdate.Pack<float>(Commands->Get_Facing(o));
			VehicleUpdate.Pack((char *)&HP, 4);
			VehicleUpdate.Pack((char *)&Y, 4);
			VehicleUpdate.Pack((char *)&X, 4);
			VehicleUpdate.Pack((char *)&ObjectID, 4);

			t_Client->SendData((const char *)&VehicleUpdate, VehicleUpdate.GetSize());
		}
		Start_Timer(1, 1.0);
	}
	virtual void Init(GameObject *obj)
	{
		CanSendDamage = 1;
		if(Is_Simple(obj))
		{
			Remove_Script(obj, "SEye_Vehicle_Update");
			return;
		}
		if(t_Client)
		{
			Vector3 pos = Commands->Get_Position(obj);
			SEye::SEyePacket VehicleUpdate;
			VehicleUpdate.SetType(3);
			
			VehicleUpdate.Pack_String(Commands->Get_Preset_Name(obj));
			VehicleUpdate.Pack<float>(pos.Y);
			VehicleUpdate.Pack<float>(pos.X);
			VehicleUpdate.Pack<unsigned int>(int(Commands->Get_Max_Health(obj)+Commands->Get_Max_Shield_Strength(obj)));
			VehicleUpdate.Pack<char>((char)Get_Object_Type(obj));
			VehicleUpdate.Pack<unsigned int>(Commands->Get_ID(obj));

			t_Client->SendData((const char *)&VehicleUpdate, VehicleUpdate.GetSize());
		}

		Start_Timer(1, 1.0);
	}

	virtual void Destroyed(GameObject *o)
	{
		if(t_Client)
		{
			SEye::SEyePacket VehicleUpdate;
			VehicleUpdate.SetType(8);
			VehicleUpdate.Pack<unsigned int>(Commands->Get_ID(o));
			t_Client->SendData((const char *)&VehicleUpdate, VehicleUpdate.GetSize());
		}
	}

	virtual void Damaged_Received(GameObject *o, GameObject *Damager, float damage)
	{
		if(!Damager)
		{
			return;
		}
		if(damage == 0)
		{
			return;
		}

		if(Damager == o)
		{
			return;
		}

		if(!CanSendDamage)
		{
			return;
		}
		CanSendDamage = 0;
		Start_Timer(2, 1.0);

		if(t_Client)
		{
			SEye::SEyePacket VehicleDamaged;
			VehicleDamaged.SetType(9);
			VehicleDamaged.Pack<unsigned int> (Commands->Get_ID(o));
			VehicleDamaged.Pack<unsigned int> (Commands->Get_ID(Damager));
			VehicleDamaged.Pack<bool> (damage > 0 ? 1 : 0);
			t_Client->SendData((const char *)& VehicleDamaged, VehicleDamaged.GetSize());
		}
	}
	
	virtual bool Vehicle_Entry_Request_Event(VehicleGameObj *Vehicle,cPlayer *Player,int &Seat) 
	{
		SEye::SEyePacket VehicleEntered;
		VehicleEntered.SetType(14);
		VehicleEntered.Pack<unsigned int> (Player->Get_Id());
		VehicleEntered.Pack<unsigned int> (Vehicle->Get_ID());
		t_Client->SendData((const char *)&VehicleEntered, VehicleEntered.GetSize());
		return true;
	}

	virtual void Vehicle_Exit_Event(VehicleGameObj *Vehicle,cPlayer *Player,int Seat) 
	{
		SEye::SEyePacket VehicleExit;
		VehicleExit.SetType(15);
		VehicleExit.Pack<unsigned int> (Player->Get_Id());
		VehicleExit.Pack<unsigned int> (Vehicle->Get_ID());
		t_Client->SendData((const char *)&VehicleExit, VehicleExit.GetSize());
	}
};

class SEye_C4_Update : public DAGameObjObserverClass {
public:
	unsigned int HP;
	bool Explode;

	virtual const char *Get_Name() {
		return "SEye_C4_Update";
	}

	virtual void Timer_Expired(GameObject *o, int Number)
	{
		if(Number == 1)
		{
			if(Get_C4_Attached(o))
			{
				if(t_Client)
				{
					SEye::SEyePacket UpdateMine;
					UpdateMine.SetType(11);
					UpdateMine.Pack<unsigned int> (Commands->Get_ID(Get_C4_Attached(o)));
					UpdateMine.Pack<unsigned int> (Commands->Get_ID(o));
					t_Client->SendData((const char *)&UpdateMine, UpdateMine.GetSize());
				}
			}
			Start_Timer(1, 0.5);
		}
		if(Number == 2)
		{
			unsigned int nHP = int(Commands->Get_Health(o)+Commands->Get_Shield_Strength(o));
			if(HP != nHP)
			{
				if(t_Client)
				{
					SEye::SEyePacket UpdateMine;
					UpdateMine.SetType(12);
					
					UpdateMine.Pack<unsigned int>(nHP);
					UpdateMine.Pack<unsigned int>(Commands->Get_ID(o));
					t_Client->SendData((const char *)&UpdateMine, UpdateMine.GetSize());
				}

				HP = nHP;
			}
			Start_Timer(2, 1.0);
		}
	}
	virtual void Init(GameObject *o)
	{
		Explode = 0;
		if(t_Client)
		{
			Vector3 pos = Commands->Get_Position(o);
			HP = int(Commands->Get_Max_Health(o)+Commands->Get_Max_Shield_Strength(o));
			SEye::SEyePacket NewMine;
			NewMine.SetType(10);

			NewMine.Pack<unsigned char> ((unsigned char)Get_C4_Mode(o));
			NewMine.Pack<float>(pos.Y);
			NewMine.Pack<float>(pos.X);
			NewMine.Pack<unsigned int>(HP);
			
			NewMine.Pack<char>((char)Get_Object_Type(o));
			NewMine.Pack<unsigned int>(Commands->Get_ID(o));

			t_Client->SendData((const char *)&NewMine, NewMine.GetSize());

		}
		Start_Timer(1, 0.5);
		Start_Timer(2, 1.0);
	}

	virtual void Kill_Received(GameObject *o, GameObject *Shooter)
	{
		Explode = 1;
	}

	virtual void Destroyed(GameObject *o)
	{
		if(t_Client)
		{
			SEye::SEyePacket MineKilled;
			MineKilled.SetType(Explode ? 8 : 13);
			MineKilled.Pack<unsigned int>(Commands->Get_ID(o));
			t_Client->SendData((const char *)&MineKilled, MineKilled.GetSize());
		}
	}
};

class SEye_Building_Update : public DAGameObjObserverClass {
public:
	unsigned int Last_HP;
	bool CanSendDamage;

	virtual const char *Get_Name() {
		return "SEye_Building_Update";
	}

	virtual void Timer_Expired(GameObject *o, int Number)
	{
		if(Number == 1)
		{
			unsigned int HP = unsigned int(Commands->Get_Health(o)+Commands->Get_Shield_Strength(o));
			if(HP != Last_HP)
			{
				Last_HP = HP;
				if(t_Client)
				{
					SEye::SEyePacket BuildingUpdate;
					BuildingUpdate.SetType(7);

					BuildingUpdate.Pack<unsigned int>(HP);
					BuildingUpdate.Pack<unsigned int>(Commands->Get_ID(o));

					t_Client->SendData((const char *)&BuildingUpdate, BuildingUpdate.GetSize());

				}
			}
			Start_Timer(1, 1.0);
		}
		else if(Number == 2)
		{
			CanSendDamage = 1;
		}
	}
	virtual void Init(GameObject *o)
	{
		CanSendDamage = 1;
		if(t_Client)
		{
			Vector3 pos = Commands->Get_Position(o);
			unsigned int nHP = int(Commands->Get_Max_Health(o)+Commands->Get_Max_Shield_Strength(o));
			SEye::SEyePacket BuildingUpdate;
			BuildingUpdate.SetType(4);
			
			BuildingUpdate.Pack_String (Commands->Get_Preset_Name(o));
			BuildingUpdate.Pack<float>(pos.Y);
			BuildingUpdate.Pack<float>(pos.X);
			BuildingUpdate.Pack<unsigned int> (nHP);
			BuildingUpdate.Pack<char> ((char)Get_Object_Type(o));
			BuildingUpdate.Pack<unsigned int> (Commands->Get_ID(o));
			t_Client->SendData((const char *)&BuildingUpdate, BuildingUpdate.GetSize());
		}

		Start_Timer(1, 1.0);
	}

	virtual void Kill_Received(GameObject *o, GameObject *Shooter)
	{
		if(t_Client)
		{
			SEye::SEyePacket BuildingDestroyed;
			BuildingDestroyed.SetType(9);
			BuildingDestroyed.Pack<unsigned int>(Commands->Get_ID(o));
			t_Client->SendData((const char *)&BuildingDestroyed, BuildingDestroyed.GetSize());
		}
	}
	
	virtual void Damage_Received(GameObject *o, GameObject *Attacker, float Damage)
	{
		if(!Attacker)
		{
			return;
		}
		if(Damage == 0)
		{
			return;
		}

		if(Attacker == o)
		{
			return;
		}

		if(!CanSendDamage)
		{
			return;
		}
		CanSendDamage = 0;
		Start_Timer(2, 1.0);

		if(t_Client)
		{
			SEye::SEyePacket BuildingDamaged;
			BuildingDamaged.SetType(9);
			BuildingDamaged.Pack<unsigned int> (Commands->Get_ID(o));
			BuildingDamaged.Pack<unsigned int> (Commands->Get_ID(Attacker));
			BuildingDamaged.Pack<bool> (Damage > 0 ? 1 : 0);
			t_Client->SendData((const char *)& BuildingDamaged, BuildingDamaged.GetSize());
		}
	}
};





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Plugin

void SEyeServerClass::Shutdown() 
{
	SEye_Server::Unload();
}

void SEyeServerClass::Init() 
{

	Register_Event(DAEvent::LEVELLOADED);
	Register_Event(DAEvent::SETTINGSLOADED);
	Register_Event(DAEvent::PLAYERJOIN);
	//Register_Event(DAEvent::PLAYERLEAVE);
	Register_Object_Event(DAObjectEvent::CREATED,DAObjectEvent::ALL);

	/*
	Register_Event(DAEvent::GAMEOVER);
	Register_Event(DAEvent::CHATCOMMAND, 5000 );
	Register_Event(DAEvent::CHAT, 6000);
	Register_Event(DAEvent::THINK);
	Register_Event(DAEvent::RADIO);
	Register_Event(DAEvent::REFILL, 5000);
	Register_Event(DAEvent::CHARACTERPURCHASEREQUEST, 5000);
	Register_Event(DAEvent::VEHICLEPURCHASEREQUEST, 5000);
	Register_Event(DAEvent::POWERUPPURCHASEREQUEST, 5000);
	Register_Event(DAEvent::POWERUPGRANTREQUEST, 5000);
	Register_Event(DAEvent::VEHICLEENTRYREQUEST, 5000);
	Register_Event(DAEvent::TEAMCHANGE, 9000);
	Register_Event(DAEvent::TEAMCHANGEREQUEST, 8000);
	Register_Event(DAEvent::SUICIDE, 5000);
	Register_Object_Event(DAObjectEvent::CREATED,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::DAMAGERECEIVEDREQUEST,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::TTCLIENTDAMAGEREQUEST,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::STOCKCLIENTDAMAGEREQUEST,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::DAMAGEDEALT,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::DAMAGEDEALTREQUEST,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::KILLRECEIVED,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::DESTROYED,DAObjectEvent::ALL);
	Register_Object_Event(DAObjectEvent::KILLRECEIVED, DAObjectEvent::SOLDIER );
	Register_Object_Event(DAObjectEvent::KILLRECEIVED, DAObjectEvent::PLAYER);

	*/

	WSADATA wsaData;
	if(WSAStartup(0x202, &wsaData))
	{
		MessageBox(0, "Error: SEye Could not open Winsock", "Error", MB_OK);
		exit(0);
	}

	//Console_Output("SEye Server Loading\n");

	SEye_Server::Load();
}

void SEyeServerClass::Object_Created_Event(GameObject *obj) 
{
	SEye_Server::ObjectCreated(obj);
}

void SEyeServerClass::Player_Join_Event(cPlayer *Player)
{
	Console_Output("SEye p join\n");
}

void SEyeServerClass::Settings_Loaded_Event()
{

}


void SEyeServerClass::Level_Loaded_Event()
{
	SEye_Server::Level_Loaded();
}


/*
	SEyeServer Functions
*/

void wcsTombs(char *cstr, const wchar_t *wcts_buf)
{
	for(; *wcts_buf != 0; wcts_buf++)
	{
		*cstr = (char)*wcts_buf;
		cstr++;
	}
	*cstr = 0;
}


void SEye_Server::ChatHook(int ID, int Type, const wchar_t *Msg)
{
	Console_Output("seye chat\n");
	if(t_Client)
	{
		const char *PName = Get_Player_Name_By_ID(ID);
		int Team = Get_Team(ID);
		char Text[256];
		wcsTombs(Text, Msg);

		if(strchr(Text, '\n') != 0)
		{
			delete []PName;
			return;
		}


		SEye::SEyePacket TextObj;
		TextObj.SetType(16);
		
		TextObj.Pack_String(Text);
		TextObj.Pack<int>(Type);
		TextObj.Pack<int>(Team);
		TextObj.Pack_String(PName);

		t_Client->SendData((const char *)&TextObj, TextObj.GetSize());

		delete []PName;
	}
}


void SEye_Server::ObjectCreated(GameObject *o)
{
	if(Commands->Is_A_Star(o))
	{
		o->Add_Observer(new SEye_Player_Update() );
		//Attach_Script_Once(o, "SEye_Player_Update", "");
	}
	if(o->As_VehicleGameObj() && Get_Vehicle_Mode(o) != 4)
	{
		o->Add_Observer(new SEye_Vehicle_Update() );
		//Attach_Script_Once(o, "SEye_Vehicle_Update", "");
	}
	if(Is_C4(o))
	{
		o->Add_Observer(new SEye_C4_Update() );
		//Attach_Script_Once(o, "SEye_C4_Update", "");
	}
}

DWORD GetModulePath(HINSTANCE hInst, LPTSTR pszBuffer, DWORD dwSize)
{
	DWORD dwLength = GetModuleFileName( hInst, pszBuffer, dwSize );
	if( dwLength )
	{
		while( dwLength && pszBuffer[ dwLength ] != '\\')
		{
			dwLength--;
		}

		if( dwLength )
			pszBuffer[ dwLength] = '\000';
	}
	return dwLength;
}

void SEye_Server::Load()
{
	Console_Output("SEye Server Loading\n");	
	char IP_ADDR[256];
	char Path[MAX_PATH];
	GetModulePath(NULL, Path, MAX_PATH);
	sprintf(Path, "%s\\SEye.ini ", Path);

	INIClass *ini = Get_INI(Path);
	if(!ini)
	{
		Console_Output("Failed to load SEye Server, ini file not found.\n");
		return;
	}

	ini->Get_String("SEye", "Bind_IP", "127.0.0.1", IP_ADDR, 256);

	t_Sock = new TCPSocket();
	if(!t_Sock->Server(IP_ADDR, 322, 3))
	{
		Console_Output("Failed to bind to IP: %s\n", IP_ADDR);
	}
	else
	{
		Console_Output("SEye started successfuly on IP: %s\n", IP_ADDR);
	}
}

void SEye_Server::Unload()
{
	if(t_Client)
	{
		t_Client->Destroy();
		delete t_Client;
		t_Client = 0;
	}
	if(t_Sock)
	{
		t_Sock->Destroy();
		delete t_Sock;
		t_Sock = 0;
	}
}


void SEye_Server::Level_Loaded()
{
	GameObject *Socket = Commands->Create_Object("Invisible_Object", Vector3() );
	Socket->Add_Observer(new SEye_Socket() );
	//Attach_Script_Building("SEye_Building_Update", "", 2);

	if(t_Client)
	{
		SEye::SEyePacket sp_Header;
		sp_Header.SetType(1);
		sp_Header.Pack_String(The_Game()->MapName);
		sp_Header.Pack((const char *)&The_Game()->TimeRemaining_Seconds, 4);
		t_Client->SendData((const char *)&sp_Header, sp_Header.GetSize());
	}
}


Register_Game_Feature(SEyeServerClass,"SEye Server","SEye_Server",0);




/*
ScriptRegistrant<SEye_Building_Update> SEye_Building_Update_Registrant("SEye_Building_Update", "");
ScriptRegistrant<SEye_C4_Update> SEye_C4_Update_Registrant("SEye_C4_Update", "");
ScriptRegistrant<SEye_Player_Update> SEye_Player_Update_Registrant("SEye_Player_Update", "");
ScriptRegistrant<SEye_Vehicle_Update> SEye_Vehicle_Update_Registrant("SEye_Vehicle_Update", "");
ScriptRegistrant<SEye_SOCKET>SEye_SOCKET_Registrant("SEye_SOCKET", "");
*/


void SEye::SEyePacket::Unpack(char *Data, int Size)
{
	for(int i = 0; i < Size; i++)
	{
		Data[i] = (char)_Data[(_Size--)-1];
	}
}



void SEye::SEyePacket::Unpack_String(char *Data)
{
	for(int i = _Size-1; i >= 0; i--)
	{
		if(!_Data[i])
		{
			this->Unpack(Data, _Size-i);
			break;
		}
	}
}

void SEye::SEyePacket::Pack(const char *Data, int Size)
{
	for(; Size > 0; Size--)
	{
		_Data[_Size++] = (unsigned char)Data[Size-1];
	}
}

void SEye::SEyePacket::Pack_String(const char *Data)
{
	this->Pack((const char *)Data, (int)strlen(Data)+1);
}

void SEye::SEyePacket::SetType(unsigned char Type)
{
	_Type = Type;
}

unsigned char SEye::SEyePacket::GetType()
{
	return _Type;
}

int SEye::SEyePacket::GetSize()
{
	return _Size+8;
}


template<class _T> void SEye::SEyePacket::Pack(const _T Data)
{
	this->Pack((char *)&Data, sizeof(_T));
}

template<class _T> void SEye::SEyePacket::Unpack(_T *Data)
{
	this->Unpack((char *)Data, sizeof(_T));
}

template<class _T> void SEye::SEyePacket::Unpack(_T &Data)
{
	this->Unpack((char *)&Data, sizeof(_T));
}

template<class _T, int _N> void SEye::SEyePacket::Pack(const _T *Data)
{
	this->Pack((char *)Data, sizeof(_T)*_N);
}

template<class _T, int _N> void SEye::SEyePacket::Unpack(_T *Data)
{
	this->Pack((char *)Data, sizeof(_T)*_N);
}

TCPSocket::TCPSocket()
{
	memset((void *)this, 0, sizeof(TCPSocket));
}

TCPSocket::TCPSocket(TCPSocket &_Socket)
{
	memcpy((void *)this, &_Socket, sizeof(TCPSocket));
}

TCPSocket::TCPSocket(const char *Host, int Port)
{
	memset((void *)this, 0, sizeof(TCPSocket));
	this->Client(Host, Port);
}

TCPSocket::TCPSocket(const char *IP, int Port, int Backlog)
{
	memset((void *)this, 0, sizeof(TCPSocket));
	this->Server(IP, Port, Backlog);
}

TCPSocket::TCPSocket(SOCKET &_Socket, int _Mode)
{
	memset((void *)this, 0, sizeof(TCPSocket));
	this->Socket = _Socket;
	this->Mode = _Mode;
	this->Connected = 1;
}

TCPSocket::~TCPSocket()
{
	shutdown(this->Socket, SD_BOTH);
	closesocket(this->Socket);
	memset((void *)this, 0, sizeof(TCPSocket));
}

bool TCPSocket::Client(const char *Host, int Port)
{
	Console_Output("SEye Client\n");
	hostent *he;
	if ((he = gethostbyname(Host)) == 0) 
	{
		return 0;
	}
	SOCKET s_ = socket(AF_INET,SOCK_STREAM,0);
	if (s_ == INVALID_SOCKET) 
	{
		return 0;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons((u_short)Port);
	addr.sin_addr = *((in_addr *)he->h_addr);
	memset(&(addr.sin_zero), 0, 8); 
	if (connect(s_, (sockaddr *) &addr, sizeof(sockaddr))) 
	{
		return 0;
	}

	this->Socket = s_;
	this->Connected = 1;
	this->Mode = 0;
	this->Port = Port;
	strcpy_s(this->Host, 256, Host);
	return 1;
}

bool TCPSocket::Server(const char *IP, int Port, int Backlog)
{
	Console_Output("SEye Server %s Port %d\n");
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET) 
	{
		return 0;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(IP == 0 ? "127.0.0.1" : IP);
	service.sin_port = htons((u_short)Port);

	if(bind(server, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) 
	{
		return 0;
	}

	if (listen(server, Backlog) == SOCKET_ERROR) 
	{
		return 0;
	}
	
	this->Socket = server;
	this->Mode = 1;
	this->Connected = 1;
	return 1;
}

bool TCPSocket::Is_Connected()
{
	//Console_Output("SEye Is_Connected\n");
	if(this->Mode == 1)
	{
		return 1;
	}

	fd_set fd;
	TIMEVAL tv;

	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	FD_ZERO(&fd);
	FD_SET(this->Socket, &fd);

	if(select((int)this->Socket, 0, &fd, 0, &tv) == -1)
	{
		return 0;
	}

	if(FD_ISSET(this->Socket, &fd))
	{
		FD_CLR(this->Socket, &fd);
		return 1;
	}
	FD_CLR(this->Socket, &fd);

	return 0;
}

bool TCPSocket::Is_DataAvaliable()
{
	Console_Output("SEye Is_Data\n");
	if(!this->Is_Connected())
	{
		return 0;
	}
	if(this->Mode != 0)
	{
		return 0;
	}
	
	fd_set fd;
	TIMEVAL tv;

	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	FD_ZERO(&fd);
	FD_SET(this->Socket, &fd);

	if(select((int)this->Socket, &fd, 0, 0, &tv) == -1)
	{
		return 0;
	}

	if(FD_ISSET(this->Socket, &fd))
	{
		FD_CLR(this->Socket, &fd);
		return 1;
	}
	FD_CLR(this->Socket, &fd);
	return 0;
}

bool TCPSocket::Is_ConnectionWaiting()
{
	if(this->Mode != 1)
	{
		return 0;
	}
	
	fd_set fd;
	TIMEVAL tv;

	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	FD_ZERO(&fd);
	FD_SET(this->Socket, &fd);

	if(select((int)this->Socket, &fd, 0, 0, &tv) == -1)
	{
		return 0;
	}

	if(FD_ISSET(this->Socket, &fd))
	{
		FD_CLR(this->Socket, &fd);
		return 1;
	}
	FD_CLR(this->Socket, &fd);
	return 0;
}

bool TCPSocket::RecviveData(char *Data, int Length)
{
	Console_Output("SEye RecviveData\n");
	if(this->Is_DataAvaliable())
	{
		int ret = recv(this->Socket, Data, Length, 0);
		if(ret <= 0)
		{
			this->Destroy();
			return 0;
		}
	}
	else
	{
		return 0;
	}
	return 1;
}

bool TCPSocket::SendData(const char *Data, int Length)
{
	if(!this->Is_Connected())
	{
		return 0;
	}

	int Send_ = send(this->Socket, Data, Length, 0);
	if(Send_ != Length)
	{
		if(Send_ == -1)
		{
			return 0;
		}
		else
		{
			this->SendData(Data+Send_, Length-Send_);
		}
	}

	return 1;
}

bool TCPSocket::Destroy()
{
	shutdown(this->Socket, SD_BOTH);
	closesocket(this->Socket);

	memset((void *)this, 0, sizeof(TCPSocket));
	return 0;
}

bool TCPSocket::Accept(TCPSocket *NewConnection)
{
	Console_Output("SEye Accept!\n");
	if(!this->Is_ConnectionWaiting())
	{
		return 0;
	}

	sockaddr_in addr;
	int s_sa = sizeof(sockaddr);
	SOCKET client = accept(this->Socket, (sockaddr *)&addr, &s_sa);
	if(client == INVALID_SOCKET) 
	{
		return 0;
	}

	NewConnection->TCPSocket::TCPSocket(client, 0);
	return 1;
}