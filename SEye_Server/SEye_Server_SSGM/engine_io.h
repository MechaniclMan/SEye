/*	Renegade Scripts.dll
	File Input/Output related classes and engine calls
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
class INISection;

#ifndef HANDLE
typedef void *HANDLE;
#endif

class FileClass {
public:
	virtual ~FileClass()
	{
	}
	virtual char *File_Name() = 0;
	virtual char *Set_Name(const char* name) = 0;
	virtual bool Create() = 0;
	virtual bool Delete() = 0;
	virtual bool Is_Available(int handle) = 0;
	virtual bool Is_Open() = 0;
	virtual int Open(const char* name, int mode) = 0;
	virtual int Open(int mode) = 0;
	virtual int Read(void* buffer, int size) = 0;
	virtual int Seek(int offset, int origin) = 0;
	virtual int Tell()
	{
		return Seek(0,1);
	}
	virtual int Size() = 0;
	virtual int Write(void* buffer, int size) = 0;
	virtual void Close() = 0;
	virtual unsigned long Get_Date_Time()
	{
		return 0;
	}
	virtual bool Set_Date_Time()
	{
		return false;
	}
	virtual void Error(int a, int b, char *c) = 0;
	virtual HANDLE Get_File_Handle()
	{
		return (HANDLE)-1;
	}
	virtual void Bias(int start, int length) = 0;
};

class FileFactoryClass {
public:
	virtual ~FileFactoryClass();
	virtual FileClass* Get_File(const char* Filename) = 0;
	virtual void Return_File(FileClass* File) = 0;
};

struct ChunkHeader {
	unsigned long ChunkType;
	unsigned long ChunkSize;
};

struct MicroChunkHeader {
	unsigned char ChunkType;
	unsigned char ChunkSize;
};

struct IOVector2Struct {
	float X;
	float Y;
};

struct IOVector3Struct {
	float X;
	float Y;
	float Z;
};

struct IOVector4Struct {
	float X;
	float Y;
	float Z;
	float W;
};

struct IOQuaternionStruct {
	float Q[4];
};

class ChunkLoadClass {
private:
	FileClass* File;
	int StackIndex;
	unsigned long PositionStack[256];
	ChunkHeader HeaderStack[256];
	bool InMicroChunk;
	int MicroChunkPosition;
	MicroChunkHeader MCHeader;
public:
	ChunkLoadClass(FileClass *file);
	bool Open_Chunk();
	bool Peek_Next_Chunk(unsigned int *id, unsigned int *length);
	bool Close_Chunk();
	unsigned long Cur_Chunk_ID();
	unsigned long Cur_Chunk_Length();
	int Cur_Chunk_Depth();
	int Contains_Chunks();
	bool Open_Micro_Chunk();
	bool Close_Micro_Chunk();
	unsigned long Cur_Micro_Chunk_ID();
	unsigned long Cur_Micro_Chunk_Length();
	long Seek(unsigned long nbytes);
	long Read(void *buf, unsigned long nbytes);
	long Read(IOVector2Struct *v);
	long Read(IOVector3Struct *v);
	long Read(IOVector4Struct *v);
	long Read(IOQuaternionStruct *q);
};

class ChunkSaveClass {
	class FileClass* File;
	int StackIndex;
	int PositionStack[256];
	struct ChunkHeader HeaderStack[256];
	bool InMicroChunk;
	int MicroChunkPosition;
	struct MicroChunkHeader MCHeader;
public:
	ChunkSaveClass(FileClass *file);
	bool Begin_Chunk(unsigned long id);
	bool End_Chunk();
	int Cur_Chunk_Depth();
	bool Begin_Micro_Chunk(unsigned long id);
	bool End_Micro_Chunk();
	unsigned long Write(void* buf,unsigned long nbytes);
	unsigned long Write(IOVector2Struct& v);
	unsigned long Write(IOVector3Struct& v);
	unsigned long Write(IOVector4Struct& v);
	unsigned long Write(IOQuaternionStruct& q);
};

class INIClass {
	List<INISection *> *SectionList;
	IndexClass<int,INISection *> *SectionIndex;
public:
	int Get_Int(char const *section,char const *entry,int defaultvalue);
	float Get_Float(char const *section,char const *entry,float defaultvalue);
	bool Get_Bool(char const *section,char const *entry,bool defaultvalue);
	void Get_String(char const *section,char const *entry,char const *defaultvalue,char *result,int size);
	virtual ~INIClass();
};

void InitEngineIO(unsigned int exe);
FileClass *Get_Data_File(char *file); //Open a file using the mix file opening logic
void Close_Data_File(FileClass *file); //Close a file that was opened with Get_Data_File
INIClass *Get_INI(char const *filename); //Open an INI file (reading using the normal mix file opening logic) and read stuff from it
void Release_INI(INIClass *ini); //Close an INI file opened with Get_INI
unsigned int Get_Registry_Int(const char *entry,int defaultvalue); //Get an int value from the renegade registry key
unsigned long CRC_Memory(const unsigned char *data,unsigned long length,unsigned long crc); //Calculate the CRC of a block of memory
