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

bool Settings::LoadINI(const char *Map)
{
	char Path[MAX_PATH];
	char buffer[256];
	GetModulePath(NULL, Path, MAX_PATH);
	sprintf(Path, "%s\\SEye.ini", Path);
	GetPrivateProfileString(Map, "InvertY", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		if((stricmp(buffer, "true") == 0) || (stricmp(buffer, "1") == 0))
		{
			InvertY = 1;
		}
		else
		{
			InvertY = 0;
		}
	}
	GetPrivateProfileString(Map, "InvertX", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		if((stricmp(buffer, "true") == 0) || (stricmp(buffer, "1") == 0))
		{
			InvertX = 1;
		}
		else
		{
			InvertX = 0;
		}
	}
	GetPrivateProfileString(Map, "ScaleX", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		ScaleX = (float)atof(buffer);
	}
	GetPrivateProfileString(Map, "ScaleY", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		ScaleY = (float)atof(buffer);
	}
	GetPrivateProfileString(Map, "OffsetX", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		OffsetX = (float)atof(buffer);
	}
	GetPrivateProfileString(Map, "OffsetY", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		OffsetY = (float)atof(buffer);
	}

	GetPrivateProfileString(Map, "RotationOffset", "ERR", buffer, 256, Path); 
	if(strcmp(buffer, "ERR") == 0)
	{
		return 0;
	}
	else
	{
		RotationOffset = (float)atof(buffer);
	}
	return 1;
}

bool Settings::InvertY = 0;
bool Settings::InvertX = 0;
float Settings::OffsetX = 0;
float Settings::OffsetY = 0;
float Settings::ScaleX = 0;
float Settings::ScaleY = 0;
float Settings::RotationOffset = 0;