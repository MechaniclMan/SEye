#include "Winsock2.h"
#include "Windows.h"
#include "Gdiplus.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"
using namespace Gdiplus;

#include "SEyeSettings.h"
#include "SEyeMain.h"


HDC SEye::hdc;
HDC SEye::hdcMem;
HBITMAP SEye::bitmap;
HDC SEye::hdcMemBG;
HBITMAP SEye::bitmapBG;
HWND SEye::hWnd;
SEye::sButton SEye::sButtons[32];
int SEye::sButton_Size = 0;
int SEye::Mouse::m_X = 0;
int SEye::Mouse::m_Y = 0;
clock_t SEye::Timer = 0;
int SEye::FPS = 0;
clock_t SEye::FPS_Timer = 0;
int SEye::Frames = 0;
int SEye::Mouse::m_Down;
TCPSocket *SEye::t_Socket;
SEye::SEyePacket SEye::sp_tempPacket;
int SEye::i_PacketBytes = 0;
SEye::GameObj *SEye::GameObjects[512];
bool SEye::Is_Running = 0;
char SEye::GameInfo::Map[256];
unsigned int SEye::GameInfo::TimeLeft = 0;
Bitmap *SEye::GameInfo::Map_Image = 0;
clock_t SEye::GameTime_Timer = 0;
bool SEye::GameInfo::Is_Marathon = 0;
unsigned int SEye::totalBytes = 0;
unsigned int SEye::BPS = 0;
UINT SEye::UpdateTimer = 0;
clock_t SEye::Animation_Timer = 0;
SEye::sExplosion *SEye::Explosions[32];
Image *SEye::sExplosion::ExplosionImages[16];
char SEye::ErrorInfo::Error[256];
unsigned char SEye::ErrorInfo::Alpha = 0;
clock_t SEye::ErrorInfo::Timer = 0;
int SEye::ErrorInfo::State = -1;
SEye::ChatText *SEye::ChatTextCont::Lines[5];
clock_t SEye::ChatTextCont::ShiftTimer = 0;
clock_t SEye::ChatTextCont::AlphaTimer = 0;
int SEye::ChatTextCont::Alpha = 255;
bool SEye::ChatTextCont::Fading = 0;
int SEye::ConnectDialog::Position_X = 50;
int SEye::ConnectDialog::Position_Y = 85;
int SEye::ConnectDialog::Width = 200;
int SEye::ConnectDialog::Height = 50;
int SEye::ConnectDialog::ActualWidth = 20;
int SEye::ConnectDialog::ActualHeight = 20;
clock_t SEye::ConnectDialog::OpenTimer = 0;
int SEye::ConnectDialog::OpenStatus = -1;
char SEye::ConnectDialog::EnteredText[128];
Point SEye::Mouse_Old_Pos;
bool SEye::Zoom_Dialog = 0;
Bitmap *SEye::Zoomed = 0;
SEye::GameObj *SEye::Zoom_Target = 0;
bool SEye::RedrawBG = 1;
clock_t SEye::PingPong = 0;
unsigned int SEye::LastHintID = 1;
unsigned int SEye::Ping = 0;
unsigned int SEye::PingData = 0;


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

void SEye::Init()
{
	Mouse_Old_Pos = Point(0, 0);
	WSADATA wsaData;
	if(WSAStartup(0x202, &wsaData))
	{
		MessageBox(hWnd, "Error: Could not open Winsock", "Error", MB_OK);
		exit(0);
	}

	CreateButton(L"Connect", SEye::Events::Connect_Button);
	CreateButton(L"Open", SEye::Events::Open_Button);
	CreateButton(L"Record", SEye::Events::Record_Button);
	CreateButton(L"Zoom", SEye::Events::Zoom_Button);

	Timer = clock();

	memset((void *)GameObjects, 0, 512*4);
	memset((void *)Explosions, 0, 32*4);
	memset((void *)GameInfo::Map, 0, 256);
	memset((void *)sExplosion::ExplosionImages, 0, 16*4);
	

	char Path[MAX_PATH];
	GetModulePath(NULL, Path, MAX_PATH);
	
	for(int i = 0; i < 16; i++)
	{
		char tmp[512];
		sprintf(tmp, "%s\\Explosions\\Exp_%.2d.png", Path, i+1);
		wchar_t wcs[256];
		SEye::mbsTowcs(wcs, tmp);	

		sExplosion::ExplosionImages[i] = new Bitmap(wcs);
		MakeTransparent(*((Bitmap *)sExplosion::ExplosionImages[i]), Color(0,0,0));
	}
}

void SEye::Destroy()
{
	WSACleanup();
}

#ifdef Calibrate
Point test[256];
int count = 0;
#endif


void SEye::MouseClicked(Point &Position)
{
	PointF p_Origin = PointF(10.0, 10.0);
	for(int i = 0; i < sButton_Size; i++)
	{
		if(Is_In(PointF((float)Mouse::m_X, (float)Mouse::m_Y), RectF(p_Origin.X-2, p_Origin.Y-2, sButtons[i]._Size.Width, sButtons[i]._Size.Height)))
		{
			sButtons[i].Callback();
		}
		p_Origin.X += sButtons[i]._Size.Width+10;
	}
#ifdef Calibrate
	bool connect_box = 0;
#endif
	if(SEye::ConnectDialog::OpenStatus != -1 && (Mouse::m_X > ConnectDialog::Position_X+160 && Mouse::m_X < ConnectDialog::Position_X+190) && (Mouse::m_Y > ConnectDialog::Position_Y+10 && Mouse::m_Y < ConnectDialog::Position_Y+40))
	{
#ifdef Calibrate
		connect_box = 1;
#endif
		SEye::ConnectDialog::ConnectClicked(SEye::ConnectDialog::EnteredText);
	}

	if(SEye::ConnectDialog::OpenStatus != -1 && (Mouse::m_X > ConnectDialog::Position_X+191 && Mouse::m_X < ConnectDialog::Position_X+198) && (Mouse::m_Y > ConnectDialog::Position_Y+1 && Mouse::m_Y < ConnectDialog::Position_Y+8))
	{
#ifdef Calibrate
		connect_box = 1;
#endif
		SEye::ConnectDialog::Close();
	}

#ifdef Calibrate

	if(Position.Y <= 35 || connect_box)
	{
		return;
	}
	test[count++] = Position;

	FILE *f = fopen("points.txt", "a");
	fprintf(f, "(%d,%d)", Position.X, Position.Y);
	fclose(f);
#endif
}

void SEye::MouseMove(Point &Position)
{
	Mouse::m_X = Position.X;
	Mouse::m_Y = Position.Y;

	float w_obj = 0;
	float offset = 0;
	for(int i = 0; i < 512; i++)
	{
		if(GameObjects[i])
		{
			if(GameObjects[i]->Type == 0)
			{
				w_obj = 6.0;
				offset = 3;
			}
			else if(GameObjects[i]->Type == 1)
			{
				w_obj = 10.0;
				offset = 5;
			}
			else
			{
				continue;
			}
			if(Is_In(PointF((float)Position.X+offset, (float)Position.Y+offset), RectF(GameObjects[i]->SEye_Position, SizeF(w_obj, w_obj))))
			{
				GameObjects[i]->MouseOver = 1;
			}
			else
			{
				GameObjects[i]->MouseOver = 0;
			}
		}
	}
	

	if(Mouse::m_Down)
	{
		if(SEye::ConnectDialog::OpenStatus != -1 && (Mouse::m_X > ConnectDialog::Position_X && Mouse::m_X < ConnectDialog::Position_X+200) && (Mouse::m_Y > ConnectDialog::Position_Y && Mouse::m_Y < ConnectDialog::Position_Y+50))
		{
			if(!((Mouse::m_X > ConnectDialog::Position_X+160 && Mouse::m_X < ConnectDialog::Position_X+190) && (Mouse::m_Y > ConnectDialog::Position_Y+10 && Mouse::m_Y < ConnectDialog::Position_Y+40)))
			{
				ConnectDialog::Position_X += Position.X-Mouse_Old_Pos.X;
				ConnectDialog::Position_Y += Position.Y-Mouse_Old_Pos.Y;
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				
			}
		}
	}
	else
	{
		if(SEye::ConnectDialog::OpenStatus != -1 && (Mouse::m_X > ConnectDialog::Position_X+10 && Mouse::m_X < ConnectDialog::Position_X+150) && (Mouse::m_Y > ConnectDialog::Position_Y+10 && Mouse::m_Y < ConnectDialog::Position_Y+40))
		{
			SetCursor(LoadCursor(NULL, IDC_IBEAM));
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
	}
	Mouse_Old_Pos = Position;
}

void SEye::MouseDown(Point &Position)
{
	Mouse::m_Down = 1;
}

void SEye::MouseUp(Point &Position)
{
	Mouse::m_Down = 0;

	float w_obj = 0;
	float offset = 0;
	for(int i = 0; i < 512; i++)
	{
		if(GameObjects[i])
		{
			if(GameObjects[i]->Type == 0)
			{
				w_obj = 6.0;
				offset = 3;
			}
			else if(GameObjects[i]->Type == 1)
			{
				w_obj = 10.0;
				offset = 5;
			}
			else if(GameObjects[i]->Type == 2)
			{
				if(PointInPolygon(Position, ((GameObj_Building *)GameObjects[i])->Border, ((GameObj_Building *)GameObjects[i])->BorderCount))
				{
					GameObjects[i]->L_MouseClicked = GameObjects[i]->L_MouseClicked ? 0 : 1;
				}
			}
			else if(GameObjects[i]->Type == 3 && ((GameObj_C4 *)GameObjects[i])->MineType <= 2)
			{
				w_obj = 6.0;
				offset = 3.0;
			}
			else
			{
				continue;
			}
			if(Is_In(PointF((float)Position.X+offset, (float)Position.Y+offset), RectF(GameObjects[i]->SEye_Position, SizeF(w_obj, w_obj))))
			{
				GameObjects[i]->L_MouseClicked = GameObjects[i]->L_MouseClicked ? 0 : 1;
			}
		}
	}
}

void SEye::R_MouseUp(Point &Position)
{
	if(Zoom_Dialog)
	{
		int w_obj = 0;
		int offset = 0;
		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->Type == 0)
				{
					w_obj = 6;
					offset = 3;
				}
				else if(GameObjects[i]->Type == 1)
				{
					w_obj = 10;
					offset = 5;
				}
				else
				{
					continue;
				}
				if(Is_In(PointF((float)Position.X+offset, (float)Position.Y+offset), RectF(GameObjects[i]->SEye_Position, SizeF((float)w_obj, (float)w_obj))))
				{
					Zoom_Target = GameObjects[i];
					return;
				}
			}
		}
		Zoom_Target = 0;
	}
}

void SEye::DrawError(HDC ScreenBuffer)
{
	if(ErrorInfo::State != -1)
	{
		Graphics gfx(ScreenBuffer);
		SolidBrush c_Red(Color::Color(ErrorInfo::Alpha, 255, 0, 0));
		Font f_Arial(L"Arial", 10);

		wchar_t err[256];
		mbsTowcs(err, ErrorInfo::Error);

		gfx.DrawString(err, (int)wcslen(err), &f_Arial, PointF(10, 50), &c_Red);
	}
}

void SEye::DrawDialog(HDC ScreenBuffer)
{
	if(ConnectDialog::OpenStatus == -1)
	{
		return;
	}
	Graphics gfx(ScreenBuffer);

	SolidBrush c_DialogBGColour(Color::LightBlue);
	SolidBrush c_TextBox(Color::Aqua);
	SolidBrush c_Text(Color::Black);
	Pen c_Cross(Color::Black);


	SolidBrush c_Button(Color::White);
	if((Mouse::m_X > ConnectDialog::Position_X+160 && Mouse::m_X < ConnectDialog::Position_X+190) && (Mouse::m_Y > ConnectDialog::Position_Y+10 && Mouse::m_Y < ConnectDialog::Position_Y+40))
	{
		if(Mouse::m_Down)
		{
			c_Button.SetColor(Color::Red);
		}
		else
		{
			c_Button.SetColor(Color::Aqua);
		}
	}


	if(ConnectDialog::OpenStatus >= 0)
	{
		gfx.FillRectangle(&c_DialogBGColour, Rect(ConnectDialog::Position_X, ConnectDialog::Position_Y, ConnectDialog::ActualWidth, ConnectDialog::ActualHeight));
	}
	if(ConnectDialog::OpenStatus == 2)
	{
		gfx.FillRectangle(&c_TextBox, Rect(ConnectDialog::Position_X+10,  ConnectDialog::Position_Y+10, 140, 30));
		gfx.FillRectangle(&c_Button, Rect(ConnectDialog::Position_X+160, ConnectDialog::Position_Y+10, 30, 30));
		
		wchar_t Text[128];
		if(strlen(ConnectDialog::EnteredText) > 16)
		{
			mbsTowcs(Text, ConnectDialog::EnteredText+strlen(ConnectDialog::EnteredText)-16);
		}
		else
		{
			mbsTowcs(Text, ConnectDialog::EnteredText);
		}
		Font f_Arial(L"Arial", 15);
		gfx.DrawString(Text, (int)wcslen(Text), &f_Arial, PointF(float(ConnectDialog::Position_X+15), float(ConnectDialog::Position_Y+15)), &c_Text);

		gfx.DrawRectangle(&c_Cross, Rect(ConnectDialog::Position_X+191, ConnectDialog::Position_Y+1, 7, 7));
		gfx.DrawLine(&c_Cross, ConnectDialog::Position_X+191, ConnectDialog::Position_Y+1, ConnectDialog::Position_X+198, ConnectDialog::Position_Y+8);
		gfx.DrawLine(&c_Cross, ConnectDialog::Position_X+198, ConnectDialog::Position_Y+1, ConnectDialog::Position_X+191, ConnectDialog::Position_Y+8);
	}
}

void SEye::Draw_Zoom(HDC ScreenBuffer)
{
	Graphics gfx(ScreenBuffer);
	Pen p_White(Color::White, 4);
	if(Is_In(PointF((float)Mouse::m_X, (float)Mouse::m_Y), RectF(WIDTH-224, 41, 208, 208)))
	{
		gfx.DrawRectangle(&p_White, Rect(WIDTH-227, HEIGHT-257, 208, 208));
	}
	else
	{
		gfx.DrawRectangle(&p_White, Rect(WIDTH-227, 39, 208, 208));
	}
}

void SEye::BG_Draw()
{
	if(RedrawBG)
	{
		RedrawBG = 0;
		RectF r_Layout(0, 0, WIDTH, 20);
		Graphics gfx(hdcMemBG);
		gfx.Clear(Color::Black);
		if(!Is_Running)
		{
			SolidBrush c_Yellow(Color::Yellow);
			SolidBrush c_YellowShadow(Color(60, 60, 0));
			RectF r_Bounds;
			Font f_SEyeLogo(L"Arial", 72);
			gfx.MeasureString(L"SEye", (int)wcslen(L"SEye"), &f_SEyeLogo, r_Layout, &r_Bounds);

			gfx.DrawString(L"SEye", (int)wcslen(L"SEye"), &f_SEyeLogo, PointF((WIDTH/2)-(r_Bounds.Width/2)+10, ((HEIGHT-35)/2)-(r_Bounds.Height/2)-70+10), &c_YellowShadow);
			gfx.DrawString(L"SEye", (int)wcslen(L"SEye"), &f_SEyeLogo, PointF((WIDTH/2)-(r_Bounds.Width/2), ((HEIGHT-35)/2)-(r_Bounds.Height/2)-70), &c_Yellow);
		}
		else
		{
			
			float Scale = 1;
			if(WIDTH / GameInfo::Map_Image->GetWidth() < HEIGHT / GameInfo::Map_Image->GetHeight())
			{
				Scale = float(WIDTH) / float(GameInfo::Map_Image->GetWidth());
			}
			else
			{
				Scale = float(HEIGHT-35) / float(GameInfo::Map_Image->GetHeight());
			}
			gfx.DrawImage(GameInfo::Map_Image, 0.0, 0.0, float(GameInfo::Map_Image->GetWidth())*Scale, float(GameInfo::Map_Image->GetHeight())*Scale);
		}
	}
}
void SEye::Draw(HDC ScreenBuffer)
{
	Frames++;
	Graphics gfx(ScreenBuffer);
	gfx.Clear(Color::Black);

	SolidBrush c_White(Color::White);
	SolidBrush c_Black(Color::Black);
	SolidBrush c_Silver(Color::Silver);
	SolidBrush c_TextShadow(Color(50, 60, 60, 60));
	
	Pen p_White(Color::White);
	Pen p_Black(Color::Black);
	Pen p_Red(Color::Red);
	Pen p_Yellow(Color::Yellow);

	Font f_Arial(L"Arial", 8);
	Font f_SmallArial(L"Arial", 6);

	
	PointF p_Origin = PointF(10.0, 10.0);
	RectF r_Layout(0, 0, WIDTH, 20);
	gfx.DrawLine(&p_White, 0, 34, WIDTH, 34);

	wchar_t FPSString[32];
	wsprintfW(FPSString, L"Ping: %.3d BPS: %.3d FPS: %.2d", Ping, BPS, FPS);

	RectF r_Bounds;
	gfx.MeasureString(FPSString, (int)wcslen(FPSString), &f_Arial, r_Layout, &r_Bounds);

	gfx.FillRectangle(&c_TextShadow, RectF(WIDTH-r_Bounds.Width-10, 10, r_Bounds.Width+4, r_Bounds.Height+4));
	gfx.DrawString(FPSString, (int)wcslen(FPSString), &f_Arial, PointF(WIDTH-r_Bounds.Width-8, 10), &c_White);
	
	for(int i = 0; i < sButton_Size; i++)
	{
		gfx.MeasureString(sButtons[i].Name, (int)wcslen(sButtons[i].Name), &f_Arial, r_Layout, &r_Bounds);
		SizeF s_StringSize(r_Bounds.Width+4, r_Bounds.Height+4);
		
		if(sButtons[i]._Size.Width == 0 && sButtons[i]._Size.Height == 0)
		{
			sButtons[i]._Size.Width = r_Bounds.Width;
			sButtons[i]._Size.Height = r_Bounds.Height;
		}

		if(Is_In(PointF((float)Mouse::m_X, (float)Mouse::m_Y), RectF(p_Origin.X-2, p_Origin.Y-2, s_StringSize.Width, s_StringSize.Height)))
		{
			if(Mouse::m_Down)
			{
				c_White.SetColor(Color::Red);
			}
			else
			{
				c_White.SetColor(Color::Aqua);
			}
			
		}

		gfx.FillRectangle(&c_White, RectF(p_Origin.X-2, p_Origin.Y-2, s_StringSize.Width, s_StringSize.Height));
		gfx.DrawString(sButtons[i].Name, (int)wcslen(sButtons[i].Name), &f_Arial, p_Origin, &c_Black);
		c_White.SetColor(Color::White);
		p_Origin.X += r_Bounds.Width+10;
	}
	
	BitBlt(hdcMem, 0, 35, WIDTH, HEIGHT-35, hdcMemBG, 0, 0, SRCCOPY);	
	if(!GameInfo::Map_Image)
	{
		return;
	}
#ifdef Calibrate
	Settings::LoadINI(GameInfo::Map);
#endif
	
	

#ifdef Calibrate
	if(count > 1)
	{
		gfx.DrawPolygon(&p_White, test, count);
	}
#endif
	for(int i = 0; i < 32; i++)
	{
		if(Explosions[i])
		{
			gfx.DrawImage(sExplosion::ExplosionImages[Explosions[i]->iNumber], RectF(Explosions[i]->Position.X-7, Explosions[i]->Position.Y-7, 14.0, 14.0));
		}
	}


	for(int i = 4; i >= 0; i--)
	{
		if(ChatTextCont::Lines[i])
		{
			wchar_t buffer[256];
			mbsTowcs(buffer, ChatTextCont::Lines[i]->Text);

			SolidBrush teamColour(Color::Color(i == 4 ? ChatTextCont::Alpha : 255, 255, 255, 255));

			if(ChatTextCont::Lines[i]->Team == 0)
			{
				teamColour.SetColor(Color::Color(i == 4 ? ChatTextCont::Alpha : 255, 255, 0, 0));
			}
			else if(ChatTextCont::Lines[i]->Team == 1)
			{
				teamColour.SetColor(Color::Color(i == 4 ? ChatTextCont::Alpha : 255, 255, 255, 0));
			}
			gfx.DrawString(buffer, (int)wcslen(buffer), &f_Arial, PointF(20, HEIGHT-((float)i*10)-60), &teamColour);
		}
	}

	
	time_t t = (time_t)GameInfo::TimeLeft;
	tm *tstr = localtime(&t);
	char TimeStr[256];
	wchar_t wcTimeStr[256];
	sprintf(TimeStr, "%.2d : %.2d : %.2d", tstr->tm_hour, tstr->tm_min, tstr->tm_sec);
	mbsTowcs(wcTimeStr, TimeStr);

	gfx.MeasureString(wcTimeStr, (int)wcslen(wcTimeStr), &f_Arial, r_Layout, &r_Bounds);

	gfx.FillRectangle(&c_TextShadow, RectF(WIDTH-(r_Bounds.Width)-10, HEIGHT-r_Bounds.Height-12, r_Bounds.Width+4, r_Bounds.Height+4));
	gfx.DrawString(wcTimeStr, (int)wcslen(wcTimeStr), &f_Arial, PointF(WIDTH-(r_Bounds.Width)-8, HEIGHT-(r_Bounds.Height)-10), &c_White);

	
	SolidBrush c_Red(Color::Red);
	SolidBrush c_Yellow(Color::Yellow);

	

	for(int i = 0; i < 512; i++)
	{
		GameObj *o = GameObjects[i];
		if(!o)
		{
			continue;
		}

		if(o->DamagerID > 0)
		{
			for(int z = 0; z < 512; z++)
			{
				if(GameObjects[z])
				{
					if(GameObjects[z]->ObjectID == o->DamagerID)
					{
						Pen _lineclr(Color::White);
						if(!o->DamageType)
						{
							_lineclr.SetColor(Color::LightSkyBlue);
						}
						else
						{
							if(GameObjects[z]->Team == 0)
							{
								_lineclr.SetColor(Color::Red);
							}
							else if(GameObjects[z]->Team == 1)
							{
								_lineclr.SetColor(Color::Yellow);
							}
						}

						PointF DrawTo;
						if(o->Type == 2)
						{
							DrawTo.X = (float)((GameObj_Building *)o)->Spot.X;
							DrawTo.Y = (float)((GameObj_Building *)o)->Spot.Y;
						}
						else
						{	
							DrawTo = o->SEye_Position;
						}		

						gfx.DrawLine(&_lineclr, DrawTo.X, DrawTo.Y, GameObjects[z]->SEye_Position.X, GameObjects[z]->SEye_Position.Y);
					}
				}
			}
			o->DamagerID = 0;
		}

		if(o->Type == 0)
		{
			PointF pos = convertTO(o->Game_Position);
			o->SEye_Position = pos;

			if(((GameObj_Player *)o)->IsIn_Vehicle)
			{
				continue;
			}

			Brush *b_TeamC = &c_White;

			if(o->Team == 0)
			{
				b_TeamC = &c_Red;
			}
			else if(o->Team == 1)
			{
				b_TeamC = &c_Yellow;
			}

			gfx.FillEllipse(b_TeamC, RectF(pos.X-3, pos.Y-3, 6, 6));

			if((o->MouseOver || o->L_MouseClicked)&& o->Max_HitPoints > 0 && o->HitPoints > 0)
			{
				gfx.DrawEllipse(&p_White, RectF(pos.X-4, pos.Y-4, 8, 8));

				pos.Y += 7;
				pos.X -= 8;
				LinearGradientBrush brush(RectF(pos.X, pos.Y, 16, 4), Color(255, 255, 0, 0), Color(255, 0, 255, 0), 0);
				Pen fill(&brush, 4);
				float GradSize = (float(o->HitPoints)/float(o->Max_HitPoints))*16;
				gfx.DrawLine(&fill, PointF(pos.X, pos.Y), PointF(pos.X+GradSize, pos.Y));
				gfx.DrawRectangle(&p_White, RectF(pos.X-1, pos.Y-3, 18, 6));
				pos.Y -= 10;
				pos.X += 20;
				wchar_t _temp[64];
				mbsTowcs(_temp, ((GameObj_Player *)o)->PlayerName);
				gfx.DrawString(_temp, (int)wcslen(_temp), &f_SmallArial, pos, b_TeamC);
				pos.Y += 8;
				mbsTowcs(_temp, o->Preset);
				gfx.DrawString(_temp, (int)wcslen(_temp), &f_SmallArial, pos, b_TeamC);

			}
			
		}
		else if(o->Type == 1)
		{
			PointF pos = convertTO(o->Game_Position);
			o->SEye_Position = pos;
			char Path[MAX_PATH];
			GetModulePath(NULL, Path, MAX_PATH);
			char tmp[512];
			sprintf(tmp, "%s\\Presets\\%s.png", Path, o->Preset);
			wchar_t wcs[256];
			SEye::mbsTowcs(wcs, tmp);		
			Bitmap icon(wcs);

			
			Graphics Vehicle_Layer(ScreenBuffer);
			float Rotation = (float)(((GameObj_Vehicle *)o)->Image_Rotation+Settings::RotationOffset);
			if(Rotation < 0)
			{
				Rotation += 360;
			}

			Rotation = 360-Rotation;

			Matrix x(1, 0, 0, 1, 0, 0);
			x.RotateAt(Rotation, PointF(pos.X, pos.Y));
			Vehicle_Layer.SetTransform(&x);

			MakeTransparent(icon, Color(255, 255, 255));
			
			if(icon.GetType() != ImageTypeBitmap)
			{
				
				if(o->Team == 0)
				{
					Vehicle_Layer.FillRectangle(&c_Red, RectF(pos.X-4, pos.Y-4, 10, 10));
				}
				else if(o->Team == 1)
				{
					Vehicle_Layer.FillRectangle(&c_Yellow, RectF(pos.X-4, pos.Y-4, 10, 10));
				}
				else
				{
					Vehicle_Layer.FillRectangle(&c_White, RectF(pos.X-4, pos.Y-4, 10, 10));
				}
				Vehicle_Layer.DrawLine(&p_Black, pos.X, pos.Y-4, pos.X, pos.Y+4);
			}
			else
			{
				Vehicle_Layer.DrawImage(&icon, RectF(PointF(pos.X-5, pos.Y-5), SizeF(10.0, 10.0)));
			}

			if(o->L_MouseClicked)
			{
				Vehicle_Layer.DrawRectangle(&p_White, RectF(pos.X-4, pos.Y-4, 10, 10));
			}

			if((o->MouseOver || o->L_MouseClicked)&& o->Max_HitPoints > 0 && o->HitPoints > 0)
			{
				Vehicle_Layer.DrawRectangle(&p_White, RectF(pos.X-4, pos.Y-4, 10, 10));

				char tmp[256];
				GameObj_Player *p = (GameObj_Player *)Find_Object(((GameObj_Vehicle *)o)->Driver);
				if(!p || p->Type != 0)
				{
					p = 0;
				}
				sprintf(tmp, "Driver: %s", p ? p->PlayerName : "None");
				wchar_t dvr[256];
				
				mbsTowcs(dvr, tmp);

				SolidBrush *teamBrush = &c_White;
				if(o->Team == 0)
				{
					teamBrush = &c_Red;
				}
				else if(o->Team == 1)
				{
					teamBrush = &c_Yellow;
				}
				gfx.DrawString(dvr, (int)wcslen(dvr), &f_SmallArial, pos, teamBrush);  

				pos.Y += 15;
				pos.X += 2;
				LinearGradientBrush brush(RectF(pos.X, pos.Y, 16, 4), Color(255, 255, 0, 0), Color(255, 0, 255, 0), 0);
				
				Pen fill(&brush, 4);
				float GradSize = (float(o->HitPoints)/float(o->Max_HitPoints))*16;
				gfx.DrawLine(&fill, PointF(pos.X, pos.Y), PointF(pos.X+GradSize, pos.Y));
				gfx.DrawRectangle(&p_White, RectF(pos.X-1, pos.Y-3, 18, 6));
			}


		}
		else if(o->Type == 2)
		{
			GameObj_Building *b = (GameObj_Building *)o;
			
			if(b->L_MouseClicked)
			{
				gfx.DrawPolygon(&p_White, b->Border, b->BorderCount);
				
				if(b->HitPoints > 0)
				{
					Point pos = b->Spot;
					pos.X -= 8;
					LinearGradientBrush brush(RectF((float)pos.X, (float)pos.Y, 16.0, 4.0), Color(255, 255, 0, 0), Color(255, 0, 255, 0), 0);	
					Pen fill(&brush, 4);
					float GradSize = (float(o->HitPoints)/float(o->Max_HitPoints))*16;
					gfx.DrawLine(&fill, PointF((float)pos.X, (float)pos.Y), PointF((float)pos.X+GradSize, (float)pos.Y));
				}
			}

			if(b->HitPoints <= 0)
			{
				SolidBrush b_RedA(Color(50, 255, 0, 0));
				gfx.FillPolygon(&b_RedA, b->Border, b->BorderCount);
			}
		}
		else if(o->Type == 3)
		{
			GameObj_C4 *c4 = (GameObj_C4 *)o;

			if(c4->MineType == 1)
			{
				PointF pos = convertTO(o->Game_Position);
				o->SEye_Position = pos;

				Pen *teamColour = &p_White;
				if(o->Team == 0)
				{
					teamColour = &p_Red;
				}
				else if(o->Team == 1)
				{
					teamColour = &p_Yellow;
				}
				gfx.DrawRectangle(teamColour, RectF(pos.X-2, pos.Y-2, 4, 4));
				if(c4->L_MouseClicked)
				{
					gfx.DrawRectangle(&p_White, RectF(pos.X-3, pos.Y-3, 6, 6));
				}
			}
			else if(c4->MineType == 2)
			{
				PointF pos = convertTO(o->Game_Position);
				o->SEye_Position = pos;

				if(c4->ShowTick)
				{
					Pen *teamColour = &p_White;
					if(o->Team == 0)
					{
						teamColour = &p_Red;
					}
					else if(o->Team == 1)
					{
						teamColour = &p_Yellow;
					}
					gfx.DrawRectangle(teamColour, RectF(pos.X-2, pos.Y-2, 4, 4));
					if(c4->L_MouseClicked)
					{
						gfx.DrawRectangle(&p_White, RectF(pos.X-3, pos.Y-3, 6, 6));
					}
				}

			}
			else if(c4->MineType == 3)
			{
				PointF pos = convertTO(o->Game_Position);
				o->SEye_Position = pos;

				Pen *teamColour = &p_White;
				if(o->Team == 0)
				{
					teamColour = &p_Red;
				}
				else if(o->Team == 1)
				{
					teamColour = &p_Yellow;
				}

				gfx.DrawLine(teamColour, pos.X-2, pos.Y-2, pos.X+2, pos.Y+2);
				gfx.DrawLine(teamColour, pos.X+2, pos.Y-2, pos.X-2, pos.Y+2);
			}
		}
	}
}

void SEye::PacketReceived(SEye::SEyePacket &Packet)
{
	PingPong = clock();
	if(Packet.GetType() == 1)
	{
		int i_TimeLeft = 0;
		char cp_map[64];
		char cs_mapimagename[64];

		Packet.Unpack<int>(i_TimeLeft);
		Packet.Unpack_String(cp_map);

		GameInfo::TimeLeft = i_TimeLeft;
		strcpy(GameInfo::Map, cp_map);
		if(!Settings::LoadINI(GameInfo::Map))
		{
			Set_Error("Map %s is not configured in SEye.ini.", GameInfo::Map);
			t_Socket->Destroy();
			delete t_Socket;
			t_Socket = 0;
			Is_Running = 0;
			return;
		}

		char path[256];
		GetModulePath(NULL, path, 256);
		strcpy(cp_map+(strlen(cp_map)-4), ".png");
		sprintf(cs_mapimagename, "%s/Maps/%s", path, cp_map);

		wchar_t mapPath[256];
		mbsTowcs(mapPath, cs_mapimagename);

		Bitmap *bmp = new Bitmap(mapPath);
		if(!bmp || bmp->GetWidth() == 0 || bmp->GetHeight() == 0)
		{
			Set_Error("%S not found.", mapPath);
			t_Socket->Destroy();
			delete t_Socket;
			t_Socket = 0;
			Is_Running = 0;
			return;
		}
		if(GameInfo::Map_Image)
		{
			delete GameInfo::Map_Image;
		}

		GameInfo::Map_Image = bmp;

		Is_Running = 1;
		RedrawBG = 1;
	}

	if(Packet.GetType() == P_CREATEPLAYER)
	{
		GameObj_Player *gp_NewPlayer = new GameObj_Player;
		memset((void *)gp_NewPlayer, 0, sizeof(GameObj_Player));

		Packet.Unpack<unsigned int>(gp_NewPlayer->ObjectID);
		Packet.Unpack<char>(gp_NewPlayer->Team);
		Packet.Unpack<unsigned int>(gp_NewPlayer->HitPoints);
		Packet.Unpack<PointF>(gp_NewPlayer->Game_Position);
		Packet.Unpack_String(gp_NewPlayer->Preset);
		Packet.Unpack_String(gp_NewPlayer->PlayerName);

		if(gp_NewPlayer->ObjectID > 0)
		{
	
			gp_NewPlayer->Future_Position = gp_NewPlayer->Game_Position;

			gp_NewPlayer->Max_HitPoints = gp_NewPlayer->HitPoints;
			gp_NewPlayer->Type = 0;
			gp_NewPlayer->Step = 0;
			gp_NewPlayer->Steps = 0;
			gp_NewPlayer->LastHint = clock();

			for(int i = 0; i < 512; i++)
			{
				if(GameObjects[i] == 0)
				{
					GameObjects[i] = gp_NewPlayer;
					break;
				}
			}
		}
		else
		{
			delete gp_NewPlayer;
		}	
	}
	if(Packet.GetType() == P_CREATEVEHICLE)
	{
		GameObj_Vehicle *gp_NewVehicle = new GameObj_Vehicle;
		memset((void *)gp_NewVehicle, 0, sizeof(GameObj_Vehicle));

		Packet.Unpack<unsigned int>(gp_NewVehicle->ObjectID);
		Packet.Unpack<char>(gp_NewVehicle->Team);
		Packet.Unpack<unsigned int>(gp_NewVehicle->HitPoints);
		Packet.Unpack<PointF>(gp_NewVehicle->Game_Position);

		gp_NewVehicle->Future_Position = gp_NewVehicle->Game_Position;

		Packet.Unpack_String(gp_NewVehicle->Preset);

		gp_NewVehicle->Max_HitPoints = gp_NewVehicle->HitPoints;
		gp_NewVehicle->Type = 1;
		gp_NewVehicle->Driver = 0;
		gp_NewVehicle->Step = 0;
		gp_NewVehicle->Steps = 0;
		memset((void *)gp_NewVehicle->Passengers, 0, 16);
		gp_NewVehicle->LastHint = clock();

		if(strcmp(gp_NewVehicle->Preset, "GDI_Harvester") == 0 || strcmp(gp_NewVehicle->Preset, "Nod_Harvester") == 0)
		{
			delete gp_NewVehicle;
			return;
		}

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i] == 0)
			{
				GameObjects[i] = gp_NewVehicle;
				break;
			}
		}
	}	
	if(Packet.GetType() == P_CREATEBUILDING)
	{
		GameObj_Building *gp_Building = new GameObj_Building;
		memset((void *)gp_Building, 0, sizeof(GameObj_Building));

		Packet.Unpack<unsigned int> (gp_Building->ObjectID);
		Packet.Unpack<char> (gp_Building->Team);
		Packet.Unpack<unsigned int> (gp_Building->HitPoints);
		Packet.Unpack<PointF> (gp_Building->Game_Position);
		Packet.Unpack_String (gp_Building->Preset);

		gp_Building->Max_HitPoints = gp_Building->HitPoints;
		gp_Building->Type = 2;
		gp_Building->LastHint = clock();

		if(!LoadBuilding(gp_Building))
		{
			Set_Error("Failed to load %s.", gp_Building->Preset);
		}
		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i] == 0)
			{
				GameObjects[i] = gp_Building;
				break;
			}
		}
	}	
	if(Packet.GetType() == P_UPDATEPLAYER)
	{
		unsigned int ObjID;
		PointF pos;
		unsigned int HP;

		Packet.Unpack<unsigned int>(ObjID);
		Packet.Unpack<PointF>(pos);
		Packet.Unpack<unsigned int>(HP);

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjID)
				{
					GameObjects[i]->LastHint = clock();
					GameObjects[i]->HitPoints = HP;
					GameObjects[i]->Future_Position = pos;
					GameObjects[i]->Rotation = Rotation(GameObjects[i]->Game_Position, GameObjects[i]->Future_Position);
					float f_Distance = Distance(GameObjects[i]->Game_Position, GameObjects[i]->Future_Position);

					if(f_Distance != 0)
					{
						GameObjects[i]->Steps = 20;
						GameObjects[i]->Step = (f_Distance / GameObjects[i]->Steps);
						 
					}
					else
					{
						GameObjects[i]->Step = 0;
						GameObjects[i]->Steps = 0;
					}
				}
			}
		}
	}
	if(Packet.GetType() == P_UPDATEVEHICLE)
	{
		unsigned int ObjID;
		PointF pos;
		unsigned int HP;
		float Image_Rotation = 0;

		Packet.Unpack<unsigned int>(ObjID);
		Packet.Unpack<PointF>(pos);
		Packet.Unpack<unsigned int>(HP);
		Packet.Unpack<float>(Image_Rotation);

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjID)
				{
					GameObjects[i]->LastHint = clock();
					GameObjects[i]->Future_Position = pos;
					GameObjects[i]->Rotation = Rotation(GameObjects[i]->Game_Position, GameObjects[i]->Future_Position);
					float f_Distance = Distance(GameObjects[i]->Game_Position, GameObjects[i]->Future_Position);

					if(f_Distance != 0)
					{
						GameObjects[i]->Steps = 20;
						GameObjects[i]->Step = (f_Distance / GameObjects[i]->Steps); 						 
					}
					else
					{
						GameObjects[i]->Step = 0;
						GameObjects[i]->Steps = 0;
					}

					GameObjects[i]->HitPoints = HP;
					((GameObj_Vehicle *)GameObjects[i])->Image_Rotation = Image_Rotation;
				}
			}
		}
	}
	if(Packet.GetType() == P_VEHICLEENTER)
	{
		unsigned int ObjID;
		unsigned int ObjIDP;

		Packet.Unpack<unsigned int>(ObjID);
		Packet.Unpack<unsigned int>(ObjIDP);

		GameObj *o = Find_Object(ObjID);
		if(!o || o->Type != 1)
		{
			return;
		}		

		GameObj_Player *p = (GameObj_Player *)Find_Object(ObjIDP);
		if(!p)
		{
			return;
		}

		p->IsIn_Vehicle = 1;
		GameObj_Vehicle *veh = (GameObj_Vehicle *)o;
		if(!veh->Driver)
		{
			veh->Driver = ObjIDP;
		}
		else
		{
			for(int g = 0; g < 4; g++)
			{
				if(!veh->Passengers[g])
				{
					veh->Passengers[g] = ObjIDP;
					break;
				}
			}
		}

	}
	if(Packet.GetType() == P_VEHICLEEXIT)
	{
		unsigned int ObjID;
		unsigned int ObjIDP;

		Packet.Unpack<unsigned int>(ObjID);
		Packet.Unpack<unsigned int>(ObjIDP);

		GameObj *o = Find_Object(ObjID);
		if(!o || o->Type != 1)
		{
			return;
		}

		GameObj_Player *p = (GameObj_Player *)Find_Object(ObjIDP);
		if(p)
		{
			p->IsIn_Vehicle = 0;
		}

		GameObj_Vehicle *veh = (GameObj_Vehicle *)o;

		if(veh->Driver == ObjIDP)
		{
			veh->Driver = 0;
		}
		else
		{
			for(int i = 0; i < 4; i++)
			{
				if(veh->Passengers[i] == ObjIDP)
				{
					veh->Passengers[i] = 0;
					break;
				}
			}
		}

	}
	if(Packet.GetType() == P_UPDATEBUILDING)
	{
		unsigned int ObjID;
		unsigned int HP;

		Packet.Unpack<unsigned int>(ObjID);
		Packet.Unpack<unsigned int>(HP);

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjID)
				{
					GameObjects[i]->LastHint = clock();
					GameObjects[i]->HitPoints = HP;
				}
			}
		}
	}

	if(Packet.GetType() == P_DESTROYED)
	{
		unsigned int ObjID;
		Packet.Unpack<unsigned int>(ObjID);

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjID)
				{
					if(GameObjects[i]->Type == 1)
					{
						CreateExplosion(GameObjects[i]->SEye_Position);
					}

					if(GameObjects[i]->Type != 2)
					{
						if(Zoom_Target)
						{
							if(Zoom_Target->ObjectID == GameObjects[i]->ObjectID)
							{
								Zoom_Target = 0;
							}
						}
						delete GameObjects[i];
						GameObjects[i] = 0; 
					}
					break;
				}
			}
		}
	}
	if(Packet.GetType() == P_DAMAGED)
	{
		unsigned int ObjectID;
		unsigned int DamagerID;
		bool Repair;

		Packet.Unpack<bool>(Repair);
		Packet.Unpack<unsigned int>(DamagerID);
		Packet.Unpack<unsigned int>(ObjectID);
		
		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjectID)
				{
					GameObjects[i]->LastHint = clock();
					GameObjects[i]->DamagerID = DamagerID;
					GameObjects[i]->DamageType = Repair;
					break;
				}
			}
		}
	}	
	
	if(Packet.GetType() == P_CREATEMINE)
	{
		GameObj_C4 *gp_Mine = new GameObj_C4;
		memset((void *)gp_Mine, 0, sizeof(GameObj_C4));

		Packet.Unpack<unsigned int>(gp_Mine->ObjectID);
		Packet.Unpack<char>(gp_Mine->Team);
		Packet.Unpack<unsigned int>(gp_Mine->HitPoints);
		Packet.Unpack<PointF>(gp_Mine->Game_Position);
		Packet.Unpack<unsigned char> (gp_Mine->MineType);

		gp_Mine->Max_HitPoints = gp_Mine->HitPoints;
		gp_Mine->Type = 3;

		gp_Mine->TickTime = 2000;
		gp_Mine->Timer = clock();
		gp_Mine->TimeLTimer = clock();
		gp_Mine->TimeLeft = 30;
		gp_Mine->ShowTick = 1;
		gp_Mine->LastHint = clock();
		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i] == 0)
			{
				GameObjects[i] = gp_Mine;
				break;
			}
		}
	}

	if(Packet.GetType() == P_MINEATTACH)
	{

	}

	if(Packet.GetType() == P_MINEUPDATE)
	{

	}

	if(Packet.GetType() == P_MINEEXPLODE)
	{
		unsigned int ObjID;
		Packet.Unpack<unsigned int>(ObjID);

		for(int i = 0; i < 512; i++)
		{
			if(GameObjects[i])
			{
				if(GameObjects[i]->ObjectID == ObjID)
				{
					if(GameObjects[i]->Type == 3)
					{
						CreateExplosion(GameObjects[i]->SEye_Position);
					}
					delete GameObjects[i];
					GameObjects[i] = 0;
				}
			}
		}
	}
	if(Packet.GetType() == P_TEXTOBJ)
	{
		char PName[256], Text[256];
		int Type, Team;

		Packet.Unpack_String(PName);
		Packet.Unpack<int> (Team);
		Packet.Unpack<int> (Type);
		Packet.Unpack_String(Text);

		if(strchr(Text, '\n') == 0)
		{		
			ChatText *Line = new ChatText;
			sprintf_s(Line->Text, 256, "%s%s: %s", Type == 1 ? "[Team]" : "", PName, Text);
			Line->Team = Team;
			Add_ChatLine(Line);
		}
	}

	if(Packet.GetType() == P_HINT)
	{
		unsigned int ObjectID;
		unsigned int HintID;
		Packet.Unpack<unsigned int>(ObjectID);
		Packet.Unpack<unsigned int>(HintID);

		for(int i = 0; i < 512; i++)
		{
			GameObj *o = GameObjects[i];
			if(o && o->HintID == HintID)
			{
				if(ObjectID == 0)
				{
					SEyePacket DestroyObj;
					DestroyObj.SetType(P_DESTROYED);
					DestroyObj.Pack<unsigned int> (o->ObjectID);
					PacketReceived(DestroyObj);
				}
				else
				{
					o->LastHint = clock();
					o->HintID = 0;
					break;
				}
			}
		}
	}

	if(Packet.GetType() == P_PINGPONG)
	{
		bool From;
		unsigned int Data;

		SEyePacket Bounce;
		memcpy((void *)&Bounce, (void *)&Packet, sizeof(SEyePacket));
		
		Packet.Unpack<bool>(From);
		Packet.Unpack<unsigned int>(Data);

		if(From) //server
		{
			t_Socket->SendData((const char *)&Bounce,Bounce.GetSize());
		}
		else //client
		{
			Ping = clock() - PingPong;
			PingPong = clock();
			PingData = 0;
		}
	}
}
void SEye::Add_ChatLine(SEye::ChatText *Line)
{
	bool tmp = 0;
	for(int i = 4; i >= 0; i--)
	{
		if(!ChatTextCont::Lines[i])
		{
			tmp = 1;
			ChatTextCont::Lines[i] = Line;
			break;
		}
	}
	if(!tmp)
	{
		delete ChatTextCont::Lines[4];
		ChatTextCont::Lines[4] = 0;

		for(int i = 3; i >= 0; i--)
		{
			ChatTextCont::Lines[i+1] = ChatTextCont::Lines[i];
		}

		ChatTextCont::Lines[0] = Line;
	}

	ChatTextCont::Alpha = 255;
	ChatTextCont::ShiftTimer = clock();
	ChatTextCont::Fading = 0;
}

inline SEye::GameObj *SEye::Find_Object(unsigned int ID)
{
	for(int i = 0; i < 512; i++)
	{
		if(GameObjects[i])
		{
			if(GameObjects[i]->ObjectID == ID)
			{
				return GameObjects[i];
			}
		}
	}
	return 0;
}

void SEye::Think()
{
	if(ErrorInfo::State == 0)
	{
		if(clock()-ErrorInfo::Timer >= 10*CLOCKS_PER_SEC)
		{
			ErrorInfo::State++;
		}
	}
	if(ErrorInfo::State == 1)
	{
		if(clock()-ErrorInfo::Timer >= 5)
		{
			ErrorInfo::Alpha--;
			ErrorInfo::Timer = clock();
			if(ErrorInfo::Alpha == 0)
			{
				ErrorInfo::State = -1;
			}

		}
	}

	for(int i = 0; i < 512; i++)
	{
		GameObj *o = GameObjects[i];
		if(o)
		{
			if(((clock() - o->LastHint > 5 * CLOCKS_PER_SEC) && o->HintID == 0) && t_Socket)
			{
				SEyePacket GetHint;
				GetHint.SetType(P_HINT);
				unsigned int HintID = NewHintID();
				GetHint.Pack<unsigned int>(HintID);
				GetHint.Pack<unsigned int>(o->ObjectID);
				t_Socket->SendData((const char *)&GetHint, GetHint.GetSize());
				o->HintID = HintID;
			}
			if(o->Type == 3)
			{
				GameObj_C4 *c4 = (GameObj_C4 *)o;

				if(c4->MineType == 2)
				{
					if(clock() - c4->Timer > c4->TickTime)
					{
						c4->ShowTick = c4->ShowTick ? 0 : 1;

						c4->Timer = clock();
						c4->TickTime -= int(c4->TickTime/14);
					}
					if(clock() - c4->TimeLTimer > CLOCKS_PER_SEC)
					{
						c4->TimeLeft--;
						c4->TimeLTimer = clock();
					}
				}
			}
		}
	}
	if(clock()-Animation_Timer >= 50)
	{
		Animation_Timer = clock();
		for(int i = 0; i < 512; i++)
		{
			GameObj *o = GameObjects[i];
			if(!o)
			{
				continue;
			}

			if(o->Type == 2)
			{
				continue;
			}


			if(o->Steps > 0)
			{
				o->Game_Position.X += (float)cos(o->Rotation)*o->Step;
				o->Game_Position.Y += (float)sin(o->Rotation)*o->Step;
				--(o->Steps);
			}
		}
	}

	for(int i = 0; i < 32; i++)
	{
		sExplosion *exp = Explosions[i];
		if(exp)
		{
			if(clock() - exp->timer >= 20)
			{
				exp->iNumber++;
				if(exp->iNumber >= 16)
				{
					delete exp;
					Explosions[i] = 0;
					continue;
				}
				exp->timer = clock();
			}
		}
	}
	
	if(clock() - Timer >= 15)
	{
		if(hWnd != NULL)
		{
			InvalidateRect(hWnd, 0, 0);
		}
		Timer = clock();
	}

	if(clock() - FPS_Timer >= CLOCKS_PER_SEC)
	{
		FPS = Frames;
		Frames = 0;
		FPS_Timer = clock();

		BPS = totalBytes;
		totalBytes = 0;
	}
		
	if(ConnectDialog::OpenStatus == 0)
	{
		if(clock() - ConnectDialog::OpenTimer >= 10)
		{
			ConnectDialog::OpenTimer = clock();
			ConnectDialog::ActualWidth += 2;
			if(ConnectDialog::ActualWidth >= ConnectDialog::Width)
			{
				ConnectDialog::OpenStatus++;
			}
		}
	}
	if(ConnectDialog::OpenStatus == 1)
	{
		if(clock() - ConnectDialog::OpenTimer >= 10)
		{
			ConnectDialog::OpenTimer = clock();
			ConnectDialog::ActualHeight += 2;
			if(ConnectDialog::ActualHeight >= ConnectDialog::Height)
			{
				ConnectDialog::OpenStatus++;
			}
		}
	}



	if((clock() - ChatTextCont::ShiftTimer >= CLOCKS_PER_SEC*5) && !ChatTextCont::Fading)
	{
		ChatTextCont::AlphaTimer = clock();
		ChatTextCont::Fading = 1;
		ChatTextCont::Alpha--;
	}
	if((clock() - ChatTextCont::AlphaTimer >= 1) && ChatTextCont::Fading)
	{
		ChatTextCont::Alpha -= 5;
		if(ChatTextCont::Alpha <= 0)
		{
			for(int i = 3; i >= 0; i--)
			{
				ChatTextCont::Lines[i+1] = ChatTextCont::Lines[i];
			}

			ChatTextCont::Lines[0] = 0;

			ChatTextCont::ShiftTimer = clock();
			ChatTextCont::Fading = 0;
			ChatTextCont::Alpha = 255;
		}
	}
	if((t_Socket && clock() - PingPong > 30 * CLOCKS_PER_SEC) && PingData == 0)
	{
		bool From = 0;
		unsigned int r = (unsigned int)rand();
		SEyePacket _Packet;
		_Packet.SetType(0);
		_Packet.Pack<unsigned int>(r);
		_Packet.Pack<bool>(From);
		t_Socket->SendData((const char *)&_Packet, _Packet.GetSize());

		PingData = r;
		PingPong = clock();
	}
	
	if(t_Socket && PingData > 0 && (clock() - PingPong > 60 * CLOCKS_PER_SEC))
	{
		t_Socket->Destroy();
		delete t_Socket;
		t_Socket = 0;
		Set_Error("Lost connection to Host (ping timout).");
		Is_Running = 0;
	}

	if(Is_Running && !GameInfo::Is_Marathon)
	{
		if(clock() - GameTime_Timer >= CLOCKS_PER_SEC)
		{
			GameInfo::TimeLeft--;
			GameTime_Timer = clock();
		}
	}
	if(Is_Running && !t_Socket)
	{
		Set_Error("Lost connection to Host (connection dropped).");
		Is_Running = 0;
	}

	if(t_Socket)
	{
		if(!t_Socket->Is_Connected())
		{
			t_Socket->Destroy();
			delete t_Socket;
			t_Socket = 0;
			return;
		}
		while(t_Socket->Is_DataAvaliable())
		{
			totalBytes++;
			t_Socket->RecviveData(((char *)&sp_tempPacket)+(i_PacketBytes), 1);
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
void SEye::CreateExplosion(PointF pos)
{
	for(int i = 0; i < 32; i++)
	{
		if(!Explosions[i])
		{
			Explosions[i] = new sExplosion;
			sExplosion *exp = Explosions[i];

			memset((void *)exp, 0, sizeof(sExplosion));

			exp->Position = pos;
			return;
		}
	}
}

unsigned int SEye::NewHintID()
{
	return LastHintID++;
}

PointF SEye::convertTO(PointF Pos)
{
	if(Settings::InvertX)
	{
		Pos.X = Pos.X * -1;
	}
	if(Settings::InvertY)
	{
		Pos.Y = Pos.Y * -1;
	}
	PointF Scale(Settings::ScaleX, Settings::ScaleY);
	PointF Offset(Settings::OffsetX, Settings::OffsetY);
	SizeF img(400, 400);
	
	PointF point(Scale.X / 2 + Pos.X * WIDTH / Scale.X - Offset.X, (Scale.Y / 2 + Pos.Y) * HEIGHT / Scale.Y - Offset.Y);

	point.Y = point.Y + 35;
	return point;
}


bool SEye::LoadBuilding(GameObj_Building *gp_Building)
{
	char ini[256];
	strcpy(ini, SEye::GameInfo::Map);
	strcpy(ini+(strlen(ini)-4), ".ini");

	char Path[MAX_PATH];
	char buffer[1024];
	GetModulePath(NULL, Path, MAX_PATH);
	sprintf(Path, "%s\\MapData\\%s", Path, ini);

	GetPrivateProfileString("Building", gp_Building->Preset, "ERR", buffer, 1024, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		int X, Y;
		while(sscanf(buffer, "(%d,%d)", &X, &Y) == 2)
		{
			gp_Building->Border[gp_Building->BorderCount++] = Point(X, Y);

			strcpy(buffer, strchr(buffer, ')')+1);
		}
	}

	GetPrivateProfileString("Building_Spot", gp_Building->Preset, "ERR", buffer, 1024, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		int X, Y;
		if(sscanf(buffer, "%d,%d", &X, &Y) == 2)
		{
			gp_Building->Spot = Point(X, Y);
		}
		else
		{
			gp_Building->Spot = Point(0, 0);
		}
	}


	return 1;
}

void SEye::MakeTransparent(Bitmap &image, Color colour)
{
	Color tmp;
	Color trans(0, 0, 0, 0);
	for(int x = 0;;x++)
	{
		for(int y = 0;;y++)
		{
			int ret = image.GetPixel(x, y, &tmp);
			if(ret != Ok)
			{
				if(y == 0)
				{
					return;
				}
				break;
			}
			else if(tmp.GetAlpha() == colour.GetAlpha() && tmp.GetRed() == colour.GetRed() && tmp.GetBlue() == colour.GetBlue() && tmp.GetGreen() == colour.GetGreen())
			{
				image.SetPixel(x, y, trans);
			}
		}
	}
}

inline float SEye::Distance(PointF pos1, PointF pos2)
{
	float x = pos1.X - pos2.X;
	float y = pos1.Y - pos2.Y;

	float distance = (float)sqrt(pow(x, 2)+pow(y, 2));
	return (distance < 0 ? distance*-1 : distance);
}

inline float SEye::Rotation(PointF pos1, PointF pos2)
{
	return (float)atan2(pos2.Y-pos1.Y, pos2.X-pos1.X);
}

bool SEye::PointInPolygon(Point p, Point *Polygon, int Count)
{
//http://sidvind.com/wiki/Point-in-polygon:_Jordan_Curve_Theorem

	int crossings = 0;
	int x1,x2;
	for (int i = 0; i < Count; i++ )
	{
		if (Polygon[i].X < Polygon[(i+1)%Count].X)
		{
			x1 = Polygon[i].X;
			x2 = Polygon[(i+1)%Count].X;
		} 
		else 
		{
			x1 = Polygon[(i+1)%Count].X;
			x2 = Polygon[i].X;
		}
		if(p.X > x1 && p.X <= x2 && ( p.Y < Polygon[i].Y || p.Y <= Polygon[(i+1)%Count].Y))
		{
			static const float eps = 0.000001f;
			float dx = (float)Polygon[(i+1)%Count].X - (float)Polygon[i].X;
			float dy = (float)Polygon[(i+1)%Count].Y - (float)Polygon[i].Y;
			float k;
			if(fabs(dx) < eps)
			{
				k = 50000;
			} 
			else 
			{
				k = dy/dx;
			}
			float m = Polygon[i].Y - k * Polygon[i].X;
			
			float y2 = k * p.X + m;
			if(p.Y <= y2)
			{
				crossings++;
			}
		}
	}
	return crossings % 2 == 1;
}

void SEye::Error(const char *fmat, ...)
{
	char buffer[256];
	va_list va;
	_crt_va_start(va, fmat);
	vsnprintf(buffer, 256, fmat, va);
	va_end(va);

	MessageBox(hWnd, buffer, "Error!", MB_OK | MB_ICONERROR);
}

bool inline SEye::Is_In(PointF Position, RectF _in)
{
	return ((Position.X > _in.X && Position.X < _in.Width+_in.X) && (Position.Y > _in.Y && Position.Y < _in.Height+_in.Y));
}

void SEye::SetWindow(HWND &hwind)
{
	hWnd = hwind;
}

void SEye::ImageCopy(Bitmap *To, Bitmap *Original, Rect Bounds)
{
	for(int x = 0; x < Bounds.Width; x++)
	{
		for(int y = 0; y < Bounds.Height; y++)
		{
			Color pixel;
			Original->GetPixel(x+Bounds.X, y+Bounds.Y, &pixel);
			To->SetPixel(x, y, pixel);
		}
	}
}

long __stdcall SEye::MessageHandler(HWND hWnd, unsigned int Message, WPARAM wParam, LPARAM lParam)
{   
	PAINTSTRUCT ps;
	if(Message == WM_PAINT)
	{
		HDC hDC = BeginPaint(hWnd, &ps);
		SEye::BG_Draw();

		SEye::Draw(hdcMem);
		SEye::DrawDialog(hdcMem);
		SEye::DrawError(hdcMem);
		
		if(Zoom_Dialog)
		{
			int pX = Mouse::m_X;
			int pY = Mouse::m_Y;
			if(Zoom_Target)
			{
				pX = (int)Zoom_Target->SEye_Position.X;
				pY = (int)Zoom_Target->SEye_Position.Y;
			}
			if(Is_In(PointF((float)Mouse::m_X, (float)Mouse::m_Y), RectF(WIDTH-224, 41, 208, 208)))
			{
				StretchBlt(hdcMem, WIDTH-224, HEIGHT-254, 200, 200, hdcMem, pX-50, pY-50, 100, 100, SRCCOPY);
			}
			else
			{
				StretchBlt(hdcMem, WIDTH-224, 41, 200, 200, hdcMem, pX-50, pY-50, 100, 100, SRCCOPY);
			}
			
			SEye::Draw_Zoom(hdcMem);
		}

		BitBlt(hDC, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	}
	else if(Message == WM_CREATE)
	{
		hdc = GetDC(hWnd); 
		hdcMem = CreateCompatibleDC(hdc); 
		bitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
		SelectObject(hdcMem, bitmap);

		hdcMemBG = CreateCompatibleDC(hdc); 
		bitmapBG = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT-35);
		SelectObject(hdcMemBG, bitmapBG);
	}
	else if(Message == WM_MOUSEMOVE)
	{
		SEye::MouseMove(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	}
	else if(Message == WM_LBUTTONDOWN)
	{
		SEye::MouseDown(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	}
	else if(Message == WM_LBUTTONUP)
	{
		SEye::MouseUp(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		SEye::MouseClicked(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	}
	else if(Message == WM_RBUTTONUP)
	{
		SEye::R_MouseUp(Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	}
	else if(Message == WM_TIMER)
	{
		SEye::Think();
	}
	else if(Message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	else if(Message == WM_KEYDOWN)
	{
		if(SEye::ConnectDialog::OpenStatus == 2)
		{
			unsigned char Keyboard_State[256];

			GetKeyboardState(Keyboard_State);

			unsigned char Result[2];
	
			int ret = ToAscii((unsigned int)wParam, MapVirtualKey((unsigned int)wParam, 0), Keyboard_State, (unsigned short *)Result, 0);
			if(ret == 1)
			{
				if(Result[0] == '\b')
				{
					SEye::ConnectDialog::EnteredText[strlen(SEye::ConnectDialog::EnteredText)-1] = 0;
				}
				else
				{
					sprintf(SEye::ConnectDialog::EnteredText, "%s%c", SEye::ConnectDialog::EnteredText, Result[0]);
				}
			}
			
		}
	}
	else
	{
		return (long)DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}

void SEye::CreateButton(const wchar_t *Name, void (*Callback)())
{
	sButton tmp;
	wcscpy(tmp.Name, Name);
	tmp.Callback = Callback;
	tmp._Size.Height = 0;
	tmp._Size.Width = 0;
	sButtons[sButton_Size++] = tmp;
}

void SEye::Events::Connect_Button()
{
	SEye::ConnectDialog::Open();
}

void SEye::ConnectDialog::Open()
{
	ActualHeight = 20;
	ActualWidth = 20;
	OpenStatus = 0;
	OpenTimer = clock();
	memset((void *)EnteredText, 0, 128);
}

void SEye::ConnectDialog::Close()
{
	SEye::ConnectDialog::OpenStatus = -1;
}

void SEye::ConnectDialog::ConnectClicked(const char *Text)
{
	if(t_Socket)
	{
		t_Socket->Destroy();
		delete t_Socket;
	}
	
	t_Socket = new TCPSocket;
	if(!t_Socket->Client(Text, 465))
	{
		Error("Unable to connect!");
		delete t_Socket;
		t_Socket = 0;
	}
}

void SEye::Events::Open_Button()
{

}

void SEye::Events::Record_Button()
{

}

void SEye::Events::Zoom_Button()
{
	Zoom_Dialog = Zoom_Dialog ? 0 : 1;
}

void SEye::mbsTowcs(wchar_t *wcts_buf, char *cstr)
{
	for(;  *cstr != 0; cstr++)
	{
		*wcts_buf = (wchar_t)*cstr;
		wcts_buf++;
	}
	*wcts_buf = 0;
}

void SEye::Set_Error(const char *Format, ...)
{
	char buffer[256];
	va_list va;
	_crt_va_start(va, Format);
	vsnprintf(buffer, 256, Format, va);
	va_end(va);

	strcpy(ErrorInfo::Error, buffer);
	ErrorInfo::Alpha = 255;
	ErrorInfo::Timer = clock();
	ErrorInfo::State = 0;
}


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