/*	Renegade Scripts.dll
	General ingame data related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//forward declarations
class ScriptableGameObj;

//declared here because we dont have them
class PersistFactoryClass;
class ParameterClass;

class PostLoadableClass {
	bool IsPostLoadRegistered;
public:
	virtual ~PostLoadableClass();
	virtual void On_Post_Load();
};

class PersistClass : public PostLoadableClass {
public:
	~PersistClass();
	virtual PersistFactoryClass &Get_Factory() = 0;
	virtual bool Save(ChunkSaveClass &csave);
	virtual bool Load(ChunkLoadClass &cload);
};

class FloatDataSafeClass {
	void *Data;
public:
	float Get();
	bool stdcallx Set(float &data);
};

class IntDataSafeClass {
	void *Data;
public:
	int Get();
	bool stdcallx Set(int &data);
};

class UIntDataSafeClass {
	void *Data;
public:
	unsigned int Get();
	bool stdcallx Set(unsigned int &data);
};

class ReferencerClass;
template <class T> class ReferenceableClass {
public:
	ReferencerClass *referencer;
	T *obj;
};

class ReferencerClass : public PostLoadableClass {
public:
	~ReferencerClass();
	void On_Post_Load();
	ReferenceableClass<ScriptableGameObj> *Reference;
	ReferencerClass *Next;
};

class EditableClass : public PersistClass {
public:
	~EditableClass();
	virtual int Get_Parameter_Count();
	virtual ParameterClass *Lock_Parameter(int i);
	virtual void Unlock_Parameter(int i);
};

class DefinitionClass : public EditableClass {
	int m_DefinitionMgrLink;
	StringClass m_Name;
	unsigned long m_ID;
	unsigned long m_GenericUserData;
	bool m_SaveEnabled;
public:
	~DefinitionClass();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	virtual unsigned long Get_Class_ID() = 0;
	virtual unsigned long Get_ID();
	virtual void Set_ID(unsigned long id);
	virtual PersistClass *Create() = 0;
	virtual char *Get_Name();
	virtual void Set_Name(char *new_name);
	virtual bool Is_Valid_Config(const char *message);
};

void InitEngineDef(unsigned int exe);
const char *Get_Definition_Name(unsigned long id); //Convert a definition/preset ID into a name
unsigned long Get_Definition_ID(const char *name); //Convert a definition/preset name into an ID
DefinitionClass *Find_Named_Definition(const char *name); //Find a DefinitionClass given its name
DefinitionClass *Find_Definition(unsigned long id); //Find a DefinitionClass given its ID
unsigned long Get_Definition_Class_ID(const char *name); //get the class ID of a definition (matches the #defines above)
DefinitionClass *Get_Definition(GameObject *obj); //Get a DefinitionClass given an object
DefinitionClass *Get_Phys_Definition(GameObject *obj); //Get a DefinitionClass for the physics class given a PhysicalGameObj
bool Is_Valid_Preset_ID(unsigned long ID); //Is this a valid preset id
bool Is_Valid_Preset(const char *Preset); //Is this a valid preset name
