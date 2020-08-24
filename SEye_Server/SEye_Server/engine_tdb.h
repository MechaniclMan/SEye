/*	Renegade Scripts.dll
	Classes and engine calls that deal with strings.tdb
	Copyright 2007 Jonathan Wilson, Mark Sararu

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
class TDBObjClass : public PersistClass {
	StringClass EnglishString;
	StringClass Description;
	unsigned long ID;
	unsigned long SoundID;
	unsigned long CategoryID;
	StringClass Animation;
	DynamicVectorClass<WideStringClass> Strings;
public:
	~TDBObjClass();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &save);
	bool Load(ChunkLoadClass &load);
	virtual void *As_StringTwiddlerClass();
	virtual TDBObjClass *Clone();
	virtual WideStringClass *Get_String(unsigned long language);
	virtual WideStringClass *Get_String();
	virtual StringClass *Get_English_String();
	virtual unsigned long Get_ID();
	virtual const char *Get_ID_Desc();
	virtual unsigned long Get_Sound_ID();
	virtual const char *Get_Animation_Name();
	virtual unsigned long Get_Category_ID();
	virtual void Set_String(unsigned long language,const wchar_t *string);
	virtual void Set_English_String(const char *string);
	virtual void Set_ID(unsigned long ID);
	virtual void Set_ID_Desc(const char *description);
	virtual void Set_Animation_Name(const char *name);
	virtual void Set_Sound_ID(unsigned long ID);
	virtual void Set_Category_ID(unsigned long ID);
	virtual void Contains_Translation(unsigned long language);
};

void InitEngineTDB(unsigned int exe);
const char *Get_Translated_String(unsigned long ID); //Get a string from the translation database given its ID
const char *Get_Translated_Preset_Name(GameObject *obj); //Get the translated name for the preset of this object, if it has one
const char *Get_Translated_Weapon(GameObject *obj,int position); //Get the translated name of a weapon
const char *Get_Current_Translated_Weapon(GameObject *obj); //Get the translated name of the current weapon
const char *Get_Team_Name(int Team); //Get a teams name
const char *Get_Vehicle_Name(GameObject *obj); //Get the name of a vehicle (as used for the HUD display)
const char *Get_Translated_Definition_Name(const char *preset); //Get the translated name string for a preset name
const wchar_t *Get_Wide_Translated_String(unsigned long ID); //Get a wide string from the translation database given its ID
const wchar_t *Get_Wide_Vehicle_Name(GameObject *obj); //Get the name of a vehicle (as used for the HUD display) as a wide character string
const wchar_t *Get_Current_Wide_Translated_Weapon(GameObject *obj); //Get the translated name of the current weapon as a wide character string
