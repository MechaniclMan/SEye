


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
	static void ObjectHook(GameObject *o);
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