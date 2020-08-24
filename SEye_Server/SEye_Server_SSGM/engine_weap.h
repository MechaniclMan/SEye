/*	Renegade Scripts.dll
	Weapon related classes and engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu, WhiteDragon(MDB)

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//declared here because we dont have them
class RenderObjClass;
class ParticleEmitterClass;

class AmmoDefinitionClass : public DefinitionClass {
public:
	StringClass W3D;
	StringClass Model;
	IntDataSafeClass Warhead;
	FloatDataSafeClass Damage;
	FloatDataSafeClass Range;
	FloatDataSafeClass Velocity;
	float Gravity;
	float Elasticity;
	float RateOfFire;
	float SprayAngle;
	IntDataSafeClass SprayCount;
	StringClass TrailEmitterName;
	float AcquireTime;
	float BurstDelayTime;
	IntDataSafeClass BurstMax;
	int SoftPierceLimit;
	float TurnRate;
	bool TimeActivated;
	bool TerrainActivated;
	bool IsTracking;
	FloatDataSafeClass EffectiveRange;
	int ExplosionDefID;
	int RandomTrackingScale;
	bool DisplayLaser;
	FloatDataSafeClass ChargeTime;
	int ContinuousSoundDefID;
	int FireSoundDefID;
	StringClass ContinuousEmitterName;
	int MaxBounces;
	int SprayBulletCost;
	IntDataSafeClass AmmoType;
	float C4TriggerTime1;
	float C4TriggerTime2;
	float C4TriggerTime3;
	float C4TriggerRange1;
	float C4TriggerRange2;
	float C4TriggerRange3;
	int C4TimingSound1ID;
	int C4TimingSound2ID;
	int C4TimingSound3ID;
	float AliasedSpeed;
	int HitterType;
	int BeaconObject;
	bool BeamEnabled;
	Vector3 BeamColor;
	float BeamTime;
	float BeamWidth;
	bool BeamEndCaps;
	StringClass BeamTexture;
	bool BeamSubdivisionEnabled;
	float BeamSubdivisionScale;
	bool BeamSubdivisionFrozen;
	int IconNameID;
	StringClass IconTextureName;
	RectClass IconTextureUV;
	Vector2 IconOffset;
	int GrenadeSafetyTime;
	~AmmoDefinitionClass();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
};

class WeaponDefinitionClass : public DefinitionClass {
public:
	int Style;
	StringClass Model;
	StringClass IdleAnim;
	StringClass FireAnim;
	StringClass BackModel;
	float SwitchTime;
	FloatDataSafeClass ReloadTime;
	float KeyNumber;
	bool CanSnipe;
	bool CanRecieveGenericCnCAmmo;
	float Rating;
	int EjectPhysDefID;
	int MuzzleFlashPhysDefID;
	StringClass FirstPersonModel;
	Vector3 FirstPersonOffset;
	int RecoilImpulse;
	StringClass HUDIconTextureName;
	int ReloadSoundDefID;
	int EmptySoundDefID;
	int PrimaryAmmoDefID;
	int SecondaryAmmoDefID;
	IntDataSafeClass ClipSize;
	float RecoilTime;
	float RecoilScale;
	bool AGiveWeaponsWeapon;
	IntDataSafeClass MaxInventoryRounds;
	int IconNameID;
	StringClass IconTextureName;
	RectClass IconTextureUV;
	Vector2 IconTextureOffset;
	StringClass HumanFiringAnimation;
	~WeaponDefinitionClass();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
};

class MuzzleFlashClass {
public:
	int MuzzleBone1;
	int MuzzleBone2;
	int unk1;
	RenderObjClass *MuzzleRenderer;
	bool unk2;
	bool unk3;
};

class WeaponClass {
public:
	WeaponDefinitionClass *WeaponDef;
	ReferencerClass Owner;
	RenderObjClass *ModelRenderer;
	int DetonationMode;
	AmmoDefinitionClass *AmmoDef1;
	AmmoDefinitionClass *AmmoDef2;
	IntDataSafeClass LoadedBullets;
	IntDataSafeClass InventoryBullets;
	FloatDataSafeClass Time;
	IntDataSafeClass FireCount;
	float Speed;
	bool IsOwned;
	unsigned int State;
	float StateValue;
	bool Firing;
	bool PrimaryUnk;
	bool SecondaryUnk;
	bool PrimaryTriggered;
	bool SecondaryTriggered;
	int Muzzle1;
	bool unk1;
	bool CanFire;
	float FlashTime;
	int Muzzle2;
	int unk2;
	int StateVal;
	Vector3 Position;
	ReferencerClass Target;
	SimpleVecClass<ParticleEmitterClass*> Emitters;
	AudibleSoundClass *ContinuousSound;
	AudibleSoundClass *FiringSound;
	int CurrentFireSoundDefID;
	MuzzleFlashClass Muzzle;
};

class ExplosionDefinitionClass : public DefinitionClass {
public:
	int NextID;
	int TwiddlerID;
	float DamageRadius;
	float DamageStrength;
	int Warhead;
	bool DamageIsScaled;
	StringClass DecalFilename;
	float DecalSize;
	bool AnimatedExplosion;
	float CameraShakeIntensity;
	float CameraShakeRadius;
	float CameraShakeDuration;
	~ExplosionDefinitionClass();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
};

class WeaponBagClass {
public:
	GameObject *owner;
	DynamicVectorClass<WeaponClass *> Vector;
	int current;
	bool flag1;
	bool flag2;
};

class BeaconGameObjDef : public SimpleGameObjDef {
public:
	~BeaconGameObjDef();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	float BroadcastToAllTime;
	float ArmTime;
	float DisarmTime;
	float PreDetonateCinematicDelay;
	float DetonateTime;
	float PostDetonateTime;
	int ArmedSoundDefID;
	int DisarmingTextID;
	int DisarmedTextID;
	int ArmingTextID;
	int ArmingInterruptedTextID;
	int DisarmingInterruptedTextID;
	int PreDetonateCinematicObj;
	int PostDetonateCinematicObj;
	int ExplosionObj;
	bool IsNuke;
	StringClass ArmingAnimationName;
};

class BeaconGameObj : public SimpleGameObj {
public:
	~BeaconGameObj();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Get_Information(StringClass &str);
	void Completly_Damaged(const OffenseObjectClass &offense);
	BeaconGameObj *As_BeaconGameObj();
	GameObject *BeaconGameObj::Get_Beacon_Owner();
	ReferencerClass Owner;
	int State;
	float ArmTime;
	float PreDetonateCinematicDelay;
	float DetonateTime;
	float BroadcastToAllTime;
	AudibleSoundClass *ArmedSound;
	AudibleSoundClass *CurrentMessageSound;
	bool PreDetonateCinematicActive;
	WeaponDefinitionClass *WeaponDef;
	ReferencerClass CinematicObj;
	PlayerDataClass *Player;
};

class C4GameObjDef : public SimpleGameObjDef {
public:
	~C4GameObjDef();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	float ThrowVelocity;
};

class C4GameObj : public SimpleGameObj {
public:
	~C4GameObj();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	void Post_Think();
	void Get_Information(StringClass &str);
	void Completly_Damaged(const OffenseObjectClass &offense);
	C4GameObj *As_C4GameObj();
	void Export_Rare(BitStreamClass &BitStream);
	void Import_Rare(BitStreamClass &BitStream);
	int Collision_Occurred(const CollisionEventClass& collide);
	void Defuse();
	float TriggerTime;
	ReferencerClass Owner;
	PlayerDataClass *Player;
	AmmoDefinitionClass *AmmoDef;
	int DetonationMode;
	bool unk1;
	bool unk2;
	ReferencerClass Attached;
	Vector3 AttachLocation;
	int AttachBoneIndex;
	PhysClass *Physics;
	bool IsAttachedToMCT;
	float Time;
};

void InitEngineWeap(unsigned int exe);
int Get_Current_Bullets(GameObject *obj); //Get loaded bullets for an objects current gun
int Get_Current_Clip_Bullets(GameObject *obj); //Get clip/backpack bullets for an objects current gun
int Get_Current_Total_Bullets(GameObject *obj); //Get total bullets for an objects current gun
int Get_Total_Bullets(GameObject *obj,const char *weapon); //Get total bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Clip_Bullets(GameObject *obj,const char *weapon); //Get clip/backpack bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Bullets(GameObject *obj,const char *weapon); //Get loaded bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Current_Max_Bullets(GameObject *obj); //Get max loaded bullets for an objects current gun
int Get_Current_Clip_Max_Bullets(GameObject *obj); //Get max clip/backpack bullets for an objects current gun
int Get_Current_Total_Max_Bullets(GameObject *obj); //Get total bullets for an objects current gun
int Get_Max_Total_Bullets(GameObject *obj,const char *weapon); //Get max total bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Max_Clip_Bullets(GameObject *obj,const char *weapon); //Get max clip/backpack bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Max_Bullets(GameObject *obj,const char *weapon); //Get max loaded bullets for a specific gun (if the object doesnt have the gun, return is zero)
int Get_Position_Total_Bullets(GameObject *obj, int position); //Get total bullets for an objects gun at a specific position
int Get_Position_Bullets(GameObject *obj,int position); //Get loaded bullets for an objects gun at a specific position
int Get_Position_Clip_Bullets(GameObject *obj,int position); //Get clip/backpack bullets for an objects gun at a specific position
int Get_Position_Total_Max_Bullets(GameObject *obj, int position); //Get total bullets for an objects gun at a specific position
int Get_Position_Max_Bullets(GameObject *obj,int position); //Get loaded bullets for an objects gun at a specific position
int Get_Position_Clip_Max_Bullets(GameObject *obj,int position); //Get clip/backpack bullets for an objects gun at a specific position
void Set_Current_Bullets(GameObject *obj,int bullets); //Set current loaded bullets for an object
void Set_Current_Clip_Bullets(GameObject *obj,int bullets); //Set current clip/backpack bullets for an object
void Set_Position_Bullets(GameObject *obj,int position,int bullets); //Set position loaded bullets for an object
void Set_Position_Clip_Bullets(GameObject *obj,int position,int bullets); //Set position clip/backpack bullets for an object
void Set_Bullets(GameObject *obj,const char *weapon,int bullets); //Set loaded bullets for an object
void Set_Clip_Bullets(GameObject *obj,const char *weapon,int bullets); //Set clip/backpack bullets for an object
//For all of these, -1 means "infinate ammo"
const char *Get_Powerup_Weapon(const char *Powerup); //Get the weapon name that a powerup will grant if collected
AmmoDefinitionClass *Get_Weapon_Ammo_Definition(const char *weapon,bool PrimaryFire); //Get the AmmoDefinitionClass of a weapon given its preset name
AmmoDefinitionClass *Get_Current_Weapon_Ammo_Definition(GameObject *obj,bool PrimaryFire); //Get the AmmoDefinitionClass of an objects current weapon
AmmoDefinitionClass *Get_Position_Weapon_Ammo_Definition(GameObject *obj,int position,bool PrimaryFire); //Get the AmmoDefinitionClass of an objects weapon at tbe specified position
WeaponDefinitionClass *Get_Weapon_Definition(const char *weapon); //Get the WeaponDefinitionClass of a weapon given its preset name
WeaponDefinitionClass *Get_Current_Weapon_Definition(GameObject *obj); //Get the WeaponDefinitionClass of an objects current weapon
WeaponDefinitionClass *Get_Position_Weapon_Definition(GameObject *obj,int position); //Get the WeaponDefinitionClass of an objects weapon at the specified position
ExplosionDefinitionClass *Get_Explosion(const char *explosion); //Get the ExplosionDefinitionClass of an explosion given its preset name
const char *Get_Powerup_Weapon_By_Obj(GameObject *Powerup); //Get the name of a powerup weapon given a PowerupGameObj
int Get_Current_Weapon_Style(GameObject *obj); //Get weapon style for an objects current gun
int Get_Position_Weapon_Style(GameObject *obj,int position); //Get weapon style for an objects gun at a specific position
int Get_Weapon_Style(GameObject *obj,const char *weapon); //Get weapon style for a specific gun (if the object doesnt have the gun, return is zero)
//bullet style values
#define Style_C4 0 //note that this list reflects the list in leveledit
#define Style_None 1
#define Style_Shoulder 2
#define Style_Hip 3
#define Style_Launcher 4
#define Style_Handgun 5
#define Style_Beacon 6
void Disarm_Beacon(GameObject *obj); //Disarm a beacon
void Disarm_Beacons(int PlayerID); //Disarm all beacons for a player
void Disarm_Nearest_Beacon(GameObject *Host,int Team,bool Nearest); //disarms the nearest beacon
void Disarm_C4(GameObject *obj); //Disarm a C4 object
void Disarm_All_Proxy_C4(int PlayerID); //Disarm all proximity C4 owned by a player
void Disarm_All_C4(int PlayerID); //Disarm all C4 owned by a player
const char *Get_Current_Weapon(GameObject *obj); //gets the current weapon of an object
int Get_Weapon_Count(GameObject *obj); //gets the weapon count for an object
const char *Get_Weapon(GameObject *obj,int position); //get the specified position in the weapon bag
bool Has_Weapon(GameObject *obj,const char *weapon); //does the object have the weapon
GameObject *Find_Beacon(int Number,int Team); //find a beacon
int Get_C4_Count(int Team); //get the C4 count
int Get_Beacon_Count(int Team); //get the beacon count
char Get_Mine_Limit(); //gets the current mine limit (use the MLIMIT console command to set it)
int Get_C4_Mode(GameObject *obj); //get the C4 mode for a C4GameObj, 1 = remote, 2 = timed, 3 = proximity, anything else is invalid
int Get_C4_Count_Proximity(int Team); //Get the proximity C4 count for a team
int Get_C4_Count_Remote(int Team); //Get the remote C4 count for a team
GameObject *Get_C4_Planter(GameObject *obj); //Gets the planter of a C4GameObj
GameObject *Get_C4_Attached(GameObject *obj); //Gets the object a C4GameObj is attached to (if any)
GameObject *Get_Beacon_Planter(GameObject *obj); //Gets the planter of a BeaconGameObj
