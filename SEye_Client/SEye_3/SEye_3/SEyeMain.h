//#define Calibrate 1



#ifndef GET_X_LPARAM 
#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp)) 
#endif 

#ifndef GET_Y_LPARAM 
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp)) 
#endif 

#define WIDTH 600
#define HEIGHT 635

#define PI 3.14159265

#pragma warning(disable: 4996)
class TCPSocket;

//building types
#define B_NODPOWERPLANT 0
#define B_GDIPOWERPLANT 1
#define B_NODSOLDIER 2
#define B_GDISOLDIER 3
#define B_NODVEHICLE 4
#define B_GDIVEHICLE 5
#define B_NODREFINERY 6
#define B_GDIREFINERY 7

//Packet types
#define P_PINGPONG 0

#define P_CREATEPLAYER 2
#define P_CREATEVEHICLE 3
#define P_CREATEBUILDING 4

#define P_UPDATEPLAYER 5
#define P_UPDATEVEHICLE 6
#define P_UPDATEBUILDING 7

#define P_DESTROYED 8

#define P_DAMAGED 9

#define P_CREATEMINE 10
#define P_MINEATTACH 11
#define P_MINEUPDATE 12
#define P_MINEEXPLODE 13

#define P_VEHICLEENTER 14
#define P_VEHICLEEXIT 15

#define P_TEXTOBJ 16

#define P_HINT 17

class SEye
{
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

	class Events
	{
	public:
		static void Connect_Button();
		static void Open_Button();
		static void Record_Button();
		static void Zoom_Button();
	};
	
	class Mouse
	{
	public:
		static int m_X;
		static int m_Y;
		static int m_Down;
	};

	struct sButton
	{
		wchar_t Name[64];
		void (*Callback)();
		SizeF _Size;
	};
	
	struct GameObj
	{
		unsigned int ObjectID;
		char Team;
		unsigned char Type;
		unsigned int HitPoints;
		unsigned int Max_HitPoints;
		unsigned int HintID;
		clock_t LastHint;

		PointF Game_Position;
		PointF Future_Position;
		PointF SEye_Position;
		float Step;
		int Steps;
		float Rotation;

		char Preset[64];
		bool ShowPreset;
		bool ShowHealth;

		bool MouseOver;
		bool L_MouseClicked;
		bool R_MouseClicked;
		unsigned int DamagerID;
		bool DamageType;
	};

	struct GameObj_Player : public GameObj
	{
		bool ShowName;
		char PlayerName[64];
		bool IsIn_Vehicle;
	};

	struct GameObj_Vehicle : public GameObj
	{
		float Image_Rotation;
		unsigned int Driver;
		unsigned int Passengers[4];
		bool ShowPassengers;
	};

	struct GameObj_Building : public GameObj
	{
		Point Border[64];
		Point Spot;
		int BorderCount;
		int BuildingType;
	};

	struct GameObj_C4 : public GameObj
	{
		unsigned char MineType;
		unsigned int TimeLeft;
		clock_t TickTime;
		clock_t Timer;
		clock_t TimeLTimer;
		bool ShowTime;
		bool ShowTick;
	};

	struct GameInfo
	{
		static Bitmap *Map_Image;
		static char Map[256];
		static unsigned int TimeLeft;
		static bool Is_Marathon;
	};

	struct sExplosion
	{
		static Image *ExplosionImages[16];
		int iNumber;
		PointF Position;
		clock_t timer;
	};

	struct ErrorInfo
	{
		static char Error[256];
		static unsigned char Alpha;
		static clock_t Timer;
		static int State;
	};
	
	struct ChatText
	{
		char Text[256];
		int Team;
	};

	struct ChatTextCont
	{
		static ChatText *Lines[5];
		static clock_t ShiftTimer;
		static clock_t AlphaTimer;
		static int Alpha;
		static bool Fading;
	};

	class ConnectDialog
	{
	public:
		static int Position_X;
		static int Position_Y;

		static int Width;
		static int Height;

		static int ActualWidth;
		static int ActualHeight;

		static clock_t OpenTimer;
		static int OpenStatus;

		static char EnteredText[128];

		static void Open();
		static void Close();
		static void ConnectClicked(const char *Text);
	};

	static sExplosion *Explosions[32];
	static GameObj *GameObjects[512];
	static sButton sButtons[32];
	static int sButton_Size;
	static HDC hdc;
	static HDC hdcMem;
	static HBITMAP bitmap;

	static HDC hdcMemBG;
	static HBITMAP bitmapBG;
	static HWND hWnd;
	static void CreateButton(const wchar_t *Name, void (*Callback)());
	static void PacketReceived(SEyePacket &Packet);
	static clock_t Timer;
	static clock_t GameTime_Timer;
	static clock_t Animation_Timer;
	static int FPS;
	static clock_t FPS_Timer;
	static int Frames;
	static TCPSocket *t_Socket;
	static SEyePacket sp_tempPacket;
	static int i_PacketBytes;
	static unsigned int totalBytes;
	static unsigned int BPS;
	static bool Is_Running;
	static bool LoadBuilding(GameObj_Building *gp_Building);
	static bool PointInPolygon(Point p, Point *Polygon, int Count);
	static Point Mouse_Old_Pos;
	static bool Zoom_Dialog;
	static Bitmap *Zoomed;
	static GameObj *Zoom_Target;
	static bool RedrawBG;

	static clock_t PingPong;
	static unsigned int Ping;
	static unsigned int PingData;
	static unsigned int LastHintID;
public:
	
	static unsigned int UpdateTimer;
	static void Init();
	static void Destroy();
	static void MouseClicked(Point &Position);
	static void MouseMove(Point &Position);
	static void MouseDown(Point &Position);
	static void R_MouseUp(Point &Position);
	static void MouseUp(Point &Position);
	static void Draw(HDC ScreenBuffer);
	static void DrawError(HDC ScreenBuffer);
	static void Think();
	static void SetWindow(HWND &hwind);
	static bool Is_In(PointF Position, RectF _in);
	static long __stdcall MessageHandler(HWND hWnd, unsigned int Message, WPARAM wParam, LPARAM lParam);
	static void mbsTowcs(wchar_t *wcts_buf, char *cstr);
	static void Error(const char *fmat, ...);
	static PointF convertTO(PointF Pos);
	static float Distance(PointF pos1, PointF pos2);
	static float Rotation(PointF pos1, PointF pos2);
	static void MakeTransparent(Bitmap &image, Color colour);
	static void CreateExplosion(PointF pos);
	static void Set_Error(const char *Format, ...);
	static GameObj *Find_Object(unsigned int ID);
	static void Add_ChatLine(SEye::ChatText *Line);
	static void DrawDialog(HDC ScreenBuffer);
	static void Draw_Zoom(HDC ScreenBuffer);
	static void ImageCopy(Bitmap *To, Bitmap *Original, Rect Bounds);
	static void BG_Draw();
	static unsigned int NewHintID();

};


DWORD GetModulePath(HINSTANCE hInst, LPTSTR pszBuffer, DWORD dwSize);


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