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




int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, int iCmdShow)
{
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	SEye::Init();

	wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc    = SEye::MessageHandler;
	wndClass.cbClsExtra     = 0;
	wndClass.cbWndExtra     = 0;
	wndClass.hInstance      = hInstance;
	wndClass.hIcon          = 0;
	wndClass.hCursor        = LoadCursor(NULL, MAKEINTRESOURCE(32515));
	wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName   = NULL;
	wndClass.lpszClassName  = TEXT("SEye");

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow("SEye", "Smart Eye", WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	if(!hWnd)
	{
		char err[256];
		sprintf(err, "An error has occurred and the Smart Eye cannot run. %d", GetLastError());
		MessageBox(0, err, "Error!", MB_OK);

		SEye::Destroy();
		GdiplusShutdown(gdiplusToken);
		return 0;

	}
	SEye::SetWindow(hWnd);
	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
	SetTimer(hWnd, (UINT_PTR)&SEye::UpdateTimer, 1, 0);
	while(GetMessage(&msg, hWnd, 0, 0))
	{
		if(!msg.message)
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	SEye::Destroy();

	GdiplusShutdown(gdiplusToken);

	
	return (int)msg.wParam;
}
