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
#include "scripts.h"
#include "engine_common.h"
#include "engine_threading.h"
#include "engine_string.h"
#include "engine_net.h"
#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

#ifdef WIN32
typedef char *(*GetRemoteHost) (int player);
typedef sockaddr_in *(*GetAddress) ();
typedef int (*BandwidthOut) (sockaddr_in *addr);
#else
typedef char *(*GetRemoteHost) (char *connection,int player);
typedef sockaddr_in *(*GetAddress) (void *host);
typedef int (*BandwidthOut) (void *packetmgr,sockaddr_in *addr);
#endif

char **ServerConnection;
GetRemoteHost Get_Remote_Host;
BandwidthOut Bandwidth_Out;
void *PacketManager;
GetAddress Get_Address;
void *ServerKillConnection;

void THUNK Destroy_Connection(int PlayerID)
IMPLEMENT_THUNK(ServerKillConnection)

void InitEngineNet(unsigned int exe)
{
	switch(exe)
	{
		case 0: //game.exe
			PacketManager = (void *)0x00854708;
			Bandwidth_Out = (BandwidthOut)0x0061D310;
			Get_Address = (GetAddress)0x0061DAF0;
			Get_Remote_Host = (GetRemoteHost)0x0061A840;
			ServerConnection = (char **)0x00820D9C;
			ServerKillConnection = (void *)0x00462190;
			break;
		case 1: //server.dat
			PacketManager = (void *)0x008538F0;
			Bandwidth_Out = (BandwidthOut)0x0061CBB0;
			Get_Address = (GetAddress)0x0061D390;
			Get_Remote_Host = (GetRemoteHost)0x0061A0E0;
			ServerConnection = (char **)0x0081FF84;
			ServerKillConnection = (void *)0x00461AC0;
			break;
		case 2: //RH73
			ServerKillConnection = (void *)0x08094DF0;
			PacketManager = (void *)0x08BB6420;
			Bandwidth_Out = (BandwidthOut)0x08370754;
			Get_Address = (GetAddress)0x08371194;
			Get_Remote_Host = (GetRemoteHost)0x0836B438;
			ServerConnection = (char **)0x086C0EDC;
			break;
		case 3: //RH8
			ServerKillConnection = (void *)0x08090D84;
			PacketManager = (void *)0x089D20E0;
			Bandwidth_Out = (BandwidthOut)0x083238EA;
			Get_Address = (GetAddress)0x08324566;
			Get_Remote_Host = (GetRemoteHost)0x0831E694;
			ServerConnection = (char **)0x085E7C2C;
			break;
		default:
			ServerKillConnection = (void *)0;
			PacketManager = (void *)0;
			Bandwidth_Out = (BandwidthOut)0;
			Get_Address = (GetAddress)0;
			Get_Remote_Host = (GetRemoteHost)0;
			ServerConnection = (char **)0;
			break;
	}
}

const char *Get_IP_Address(int PlayerID)
{
	sockaddr_in *addr = 0;
	bool noaddr = false;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov addr,eax
		jmp loc2
loc1:
		mov noaddr,1
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		addr = Get_Address(RemoteHost);
	}
	else
	{
		noaddr = true;
	}
#endif
	char *temp;
	temp = new char[40];
	int ip1,ip2,ip3,ip4;
	if (!noaddr && addr)
	{
		ip1 = addr->sin_addr.s_addr&0x000000FF;
		ip2 = (addr->sin_addr.s_addr&0x0000FF00)>>8;
		ip3 = (addr->sin_addr.s_addr&0x00FF0000)>>16;
		ip4 = (addr->sin_addr.s_addr&0xFF000000)>>24;
	}
	else
	{
		ip1 = 0;
		ip2 = 0;
		ip3 = 0;
		ip4 = 0;
	}
	sprintf(temp,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
	return temp;
}

unsigned long Get_Ping(int PlayerID)
{
	int ping;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov eax,[eax+0x2A4]
		mov ping,eax
		jmp loc2
loc1:
		mov ping, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		RemoteHost += 0x29C;
		ping = *(int *)RemoteHost;
	}
	else
	{
		ping = 0;
	}
#endif
	return ping;
}

unsigned long Get_Kbits(int PlayerID)
{
	int kbits;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov ecx, PacketManager
		push eax
		call Bandwidth_Out
		mov kbits, eax
		jmp loc2
loc1:
		mov kbits, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		sockaddr_in *addr = Get_Address(RemoteHost);
		kbits = Bandwidth_Out(PacketManager,addr);
	}
	else
	{
		kbits = 0;
	}
#endif
	return kbits >> 0x0A;
}

int Get_Bandwidth(int PlayerID)
{
	int bandwidth;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov eax,[eax+0x338]
		mov bandwidth,eax
		jmp loc2
loc1:
		mov bandwidth, 0
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		RemoteHost += 0x330;
		bandwidth = *(int *)RemoteHost;
	}
	else
	{
		bandwidth = 0;
	}
#endif
	return bandwidth;
}

const char *Get_IP_Port(int PlayerID)
{
	sockaddr_in *addr = 0;
	bool noaddr = false;
#ifdef WIN32
	_asm {
		push PlayerID
		mov eax,ServerConnection
		mov ecx,[eax]
		call Get_Remote_Host
		test eax, eax
		jz loc1
		mov ecx,eax
		call Get_Address
		mov addr,eax
		jmp loc2
loc1:
		mov noaddr,1
loc2:
	}
#else
	char *RemoteHost = Get_Remote_Host(*ServerConnection,PlayerID);
	if (RemoteHost)
	{
		addr = Get_Address(RemoteHost);
	}
	else
	{
		noaddr = true;
	}
#endif
	char *temp;
	temp = new char[40];
	int ip1,ip2,ip3,ip4,port;
	if (!noaddr && addr)
	{
		ip1 = addr->sin_addr.s_addr&0x000000FF;
		ip2 = (addr->sin_addr.s_addr&0x0000FF00)>>8;
		ip3 = (addr->sin_addr.s_addr&0x00FF0000)>>16;
		ip4 = (addr->sin_addr.s_addr&0xFF000000)>>24;
		port = ntohs(addr->sin_port);
	}
	else
	{
		ip1 = 0;
		ip2 = 0;
		ip3 = 0;
		ip4 = 0;
		port = 0;
	}
	sprintf(temp,"%d.%d.%d.%d;%d",ip1,ip2,ip3,ip4,port);
	return temp;
}
