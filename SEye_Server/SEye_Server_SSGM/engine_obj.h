/*	Renegade Scripts.dll
	GameObject classes and related engine calls
	Copyright 2007 Jonathan Wilson, Mark Sararu, WhiteDragon(MDB)

	This file is part of the Renegade scripts.dll
	The Renegade scripts.dll is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	In addition, an exemption is given to allow Run Time Dynamic Linking of this code with any closed source module that does not contain code covered by this licence.
	Only the source code to the module(s) containing the licenced code has to be released.
*/
//forward declarations
class WeaponBagClass;
class PhysicalGameObj;
class ScriptZoneGameObj;
class DamageableGameObj;
class PowerupGameObj;
class C4GameObj;
class BeaconGameObj;
class ArmedGameObj;
class CinematicGameObj;
class SimpleGameObj;

//declared here because we dont have them
class AudibleSoundClass;
class AnimControlClass;
class TransitionInstanceClass;
class CollisionEventClass;
class PhysClass;
class ActiveConversationClass;
class BuildingGameObj;
class SoldierGameObj;
class VehicleGameObj;
class SmartGameObj;
class SoundSceneObjClass;
class LogicalListenerClass;
class LogicalSoundClass;

class BaseGameObjDef : public DefinitionClass {
public:
	~BaseGameObjDef();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
};

class BaseGameObj : public PersistClass, public NetworkObjectClass {
public:
	DefinitionClass *definition;
	bool ThinkTriggered;
	bool Freeze;
	~BaseGameObj();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	virtual void Init() = 0;
	virtual void Think();
	virtual void Post_Think();
	virtual bool Is_Hibernating();
	virtual PhysicalGameObj *As_PhysicalGameObj();
	virtual VehicleGameObj *As_VehicleGameObj();
	virtual SmartGameObj *As_SmartGameObj();
	virtual ScriptableGameObj *As_ScriptableGameObj();
	unsigned int Get_Network_Class_ID();
	void Delete();
};

class ScriptableGameObjDef : public BaseGameObjDef {
public:
	DynamicVectorClass<StringClass> Scripts;
	DynamicVectorClass<StringClass> Parameters;
	~ScriptableGameObjDef();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
};

class AudioCallbackClass {
public:
	virtual ~AudioCallbackClass();
	virtual void On_Sound_Started(SoundSceneObjClass *);
	virtual void On_Sound_Ended(SoundSceneObjClass *);
	virtual void On_Logical_Heard(LogicalListenerClass *,LogicalSoundClass *);
	DynamicVectorClass<SoundSceneObjClass *> Sounds;
};

class GameObjObserverTimerClass
{
	int ObserverID;
	float Time;
	int TimerNum;
};

class GameObjCustomTimerClass
{
	float Delay;
	ReferencerClass Sender;
	int Message;
	int Param;
};

class ScriptableGameObj : public BaseGameObj, public ReferenceableClass<ScriptableGameObj>, public AudioCallbackClass {
public:
	~ScriptableGameObj();
	void On_Post_Load();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Think();
	void Post_Think();
	ScriptableGameObj *As_ScriptableGameObj();
	virtual void Post_Re_Init();
	void Set_Delete_Pending();
	virtual void Get_Position(Vector3 *Position) = 0;
	virtual DamageableGameObj *As_DamageableGameObj();
	virtual BuildingGameObj *As_BuildingGameObj();
	virtual SoldierGameObj *As_SoldierGameObj();
	virtual ScriptZoneGameObj *As_ScriptZoneGameObj();
	virtual void Get_Information(StringClass &str);
	virtual bool Is_Always_Dirty();
	void On_Sound_Ended(SoundSceneObjClass *);
	void Import_Creation(BitStreamClass &BitStream);
	void Export_Creation(BitStreamClass &BitStream);
	void Start_Observers();
	bool ObserversNeedStarting;
	SimpleDynVecClass<GameObjObserverClass *> Observers;
	DynamicVectorClass<GameObjObserverTimerClass *> ObserverTimers;
	DynamicVectorClass<GameObjCustomTimerClass *> CustomTimers;
};

#define LADDER_EXIT_TOP 0
#define LADDER_EXIT_BOTTOM 1
#define LADDER_ENTER_TOP 2
#define LADDER_ENTER_BOTTOM 3
#define LEGACY_VEHICLE_ENTER_0 4
#define LEGACY_VEHICLE_ENTER_1 5
#define LEGACY_VEHICLE_EXIT_0 6
#define LEGACY_VEHICLE_EXIT_1 7
#define VEHICLE_ENTER 8
#define VEHICLE_EXIT 9

class TransitionDataClass
{
	int type;
	OBBoxClass box;
	StringClass animation;
	Matrix3D matrix;
};

class TransitionGameObjDef : public BaseGameObjDef {
public:
	~TransitionGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	DynamicVectorClass<TransitionDataClass *> Transitions;
};

class TransitionGameObj : public BaseGameObj {
public:
	~TransitionGameObj();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	DynamicVectorClass<TransitionInstanceClass *> Transitions;
	Matrix3D Transform;
	int LadderIndex;
};

class DamageZoneGameObjDef : public BaseGameObjDef {
public:
	~DamageZoneGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	float DamageRate;
	int DamageWarhead;
	Vector3 Color;
};

class DamageZoneGameObj : public BaseGameObj {
public:
	~DamageZoneGameObj();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	OBBoxClass BoundingBox;
	float Time;
};

class ScriptZoneGameObjDef : public ScriptableGameObjDef {
public:
	~ScriptZoneGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	bool Is_Valid_Config(const char *message);
	int ZoneType;
	Vector3 Color;
	bool CheckStarsOnly;
	bool IsEnvironmentZone;
};

class ScriptZoneGameObj : public ScriptableGameObj {
public:
	~ScriptZoneGameObj();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	void Get_Position(Vector3 *Position);
	ScriptZoneGameObj *As_ScriptZoneGameObj();
	bool Inside_Me(SmartGameObj *obj);
	OBBoxClass BoundingBox;
	int PlayerType;
	SList<ReferencerClass> ZoneContents;
};

class DefenseObjectDefClass {
	FloatDataSafeClass Health;
	FloatDataSafeClass HealthMax;
	UIntDataSafeClass Skin;
	FloatDataSafeClass ShieldStrength;
	FloatDataSafeClass ShieldStrengthMax;
	UIntDataSafeClass ShieldType;
	FloatDataSafeClass DamagePoints;
	FloatDataSafeClass DeathPoints;
};

class DamageableGameObjDef : public ScriptableGameObjDef {
public:
	~DamageableGameObjDef();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	DefenseObjectDefClass DefenseDef;
	StringClass InfoIconTextureFilename;
	unsigned int TranslatedNameID;
	int EncyclopediaType;
	unsigned int EncyclopediaID;
	bool NotTargetable;
	int PlayerType;
};

class DefenseObjectClass {
public:
	virtual ~DefenseObjectClass();
	virtual void Import(BitStreamClass &BitStream);
	virtual void Export(BitStreamClass &BitStream);
	void Set_Max_Health(float health);
	void Set_Max_Shield_Strength(float shieldstrength);
	void Mark_Owner_Dirty();
	FloatDataSafeClass Health;
	FloatDataSafeClass HealthMax;
	UIntDataSafeClass Skin;
	FloatDataSafeClass ShieldStrength;
	FloatDataSafeClass ShieldStrengthMax;
	UIntDataSafeClass ShieldType;
	FloatDataSafeClass DamagePoints;
	FloatDataSafeClass DeathPoints;
	bool CanObjectDie;
	ReferencerClass Owner;
};

class OffenseObjectClass {
public:
	bool b1;
	bool b2;
	float damage;
	int warhead;
	ReferencerClass Damager;
};

class DamageableGameObj : public ScriptableGameObj {
public:
	~DamageableGameObj();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	DamageableGameObj *As_DamageableGameObj();
	virtual void Apply_Damage(const OffenseObjectClass &offense,float f,int i);
	virtual void Completly_Damaged(const OffenseObjectClass &offense);
	virtual bool Is_Targetable();
	virtual bool Is_Health_Bar_Displayed();
	virtual void Set_Is_Health_Bar_Displayed(bool display);
	virtual int Get_Player_Type();
	virtual void Set_Player_Type(int type);
	void Import_Occasional(BitStreamClass &BitStream);
	void Export_Occasional(BitStreamClass &BitStream);
	Vector3 Get_Team_Color();
	DefenseObjectClass Defense;
	int PlayerType;
	bool IsHealthBarDisplayed;
};

class PhysicalGameObjDef : public DamageableGameObjDef {
public:
	~PhysicalGameObjDef();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	bool Is_Valid_Config(const char *message);
	int Type;
	int BlipShape;
	float BullseyeOffsetZ;
	StringClass Animation;
	int PhysDefID;
	int KilledExplosionID;
	bool DefaultHibernationEnable;
	bool AreInnateConversationsAllowed;
	int OratorType;
	bool UseCreationEffect;
};

class PhysObserverClass {
public:
	virtual int Collision_Occurred(const CollisionEventClass& collide);
	virtual int Object_Expired(PhysClass *obj);
	virtual void Object_Removed_From_Scene(PhysClass *obj);
	virtual void Object_Shattered_Something(PhysClass *obj1,PhysClass *obj2,int i);
};

class CombatPhysObserverClass : public PhysObserverClass {
public:
	virtual DamageableGameObj *As_DamageableGameObj();
	virtual BuildingGameObj *As_BuildingGameObj();
	virtual PhysicalGameObj *As_PhysicalGameObj();
};

class PhysicalGameObj : public DamageableGameObj, public CombatPhysObserverClass {
public:
	~PhysicalGameObj();
	void On_Post_Load();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Post_Think();
	bool Is_Hibernating();
	PhysicalGameObj *As_PhysicalGameObj();
	VehicleGameObj *As_VehicleGameObj();
	void Get_Position(Vector3 *Position);
	DamageableGameObj *As_DamageableGameObj();
	SoldierGameObj *As_SoldierGameObj();
	void Get_Information(StringClass &str);
	void Export_Creation(BitStreamClass &BitStream);
	void Import_Creation(BitStreamClass &BitStream);
	void Apply_Damage(const OffenseObjectClass &offense,float f,int i);
	void Completly_Damaged(const OffenseObjectClass &offense);
	void Set_Player_Type(int type);
	virtual void Startup();
	virtual void Set_Animation(const char *animation,bool loop,float firstframe);
	virtual void Set_Animation_Frame(const char *animation,int frame);
	virtual float Get_Bullseye_Position();
	virtual void Apply_Damage_Extended(const OffenseObjectClass &offense,float f,const Vector3& v,int i);
	virtual bool Takes_Explosion_Damage();
	int Object_Expired(PhysClass *obj);
	virtual PowerupGameObj *As_PowerupGameObj();
	virtual C4GameObj *As_C4GameObj();
	virtual BeaconGameObj *As_BeaconGameObj();
	virtual ArmedGameObj *As_ArmedGameObj();
	virtual CinematicGameObj *As_CinematicGameObj();
	virtual SimpleGameObj *As_SimpleGameObj();
	virtual void Begin_Hibernation();
	virtual void End_Hibernation();
	void Export_Rare(BitStreamClass &BitStream);
	void Import_Rare(BitStreamClass &BitStream);
	void Export_Frequent(BitStreamClass &BitStream);
	void Import_Frequent(BitStreamClass &BitStream);
	int Get_Vis_ID();
	bool Get_World_Position(Vector3 &Position);
	void Object_Shattered_Something(PhysClass *obj1,PhysClass *obj2,int i);
	void Set_Transform(Matrix3D *mat);
	Matrix3D *Get_Transform();
	ActiveConversationClass *Conversation;
	PhysClass *Physics;
	AnimControlClass *Animation;
	int ServerSkips;
	float HibernationTime;
	bool IsHibernating;
	ReferencerClass Ref;
	int AttachBoneIndex;
	int RadarBlipShape;
	int RadarBlipColor;
	float RadarBlipIntensity;
	PhysicalGameObj *AttachObj;
	bool HudPokableIndicatorEnabled;
	bool InnateConversationsEnabled;
};

class SpecialEffectsGameObjDef : public PhysicalGameObjDef {
public:
	~SpecialEffectsGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	StringClass AnimationName;
	int SoundDefID;
};

class SpecialEffectsGameObj : public PhysicalGameObj {
public:
	~SpecialEffectsGameObj();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	float TotalTime;
	bool EffectRunning;
};

class SimpleGameObjDef : public PhysicalGameObjDef {
public:
	~SimpleGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	bool IsEditorObject;
	bool IsHiddenObject;
	int PlayerTerminalType;
};

class SimpleGameObj : public PhysicalGameObj {
public:
	~SimpleGameObj();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	bool Is_Always_Dirty();
	SimpleGameObj *As_SimpleGameObj();
};

class PowerupGameObjDef : public SimpleGameObjDef {
public:
	~PowerupGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	int GrantShieldType;
	float GrantShieldStrength;
	float GrantShieldStrengthMax;
	float GrantHealth;
	float GrantHealthMax;
	int GrantWeaponID;
	bool GrantWeapon;
	int GrantWeaponRounds;
	bool GrantWeaponClips;
	bool Persistant;
	int GrantKey;
	bool AlwaysAllowGrant;
	int GrantSoundID;
	StringClass GrantAnimationName;
	int IdleSoundID;
	StringClass IdleAnimationName;
	void Grant(GameObject *obj,int powerup,bool showonhud);
};

class PowerupGameObj : public SimpleGameObj {
public:
	~PowerupGameObj();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	bool Is_Always_Dirty();
	PowerupGameObj *As_PowerupGameObj();
	void Get_Description(StringClass &Description);
	AudibleSoundClass *IdleSound;
	int State;
	float Time;
	WeaponBagClass *Backpack;
};

class MuzzleRecoilClass {
public:
	int unk1;
	float unk2;
	float unk3;
	float unk4;
};

class ArmedGameObjDef : public PhysicalGameObjDef {
public:
	~ArmedGameObjDef();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	//All of these floats are in radians (although leveledit shows degrees)
	float WeaponTiltRate;
	float WeaponTiltMin;
	float WeaponTiltMax;
	float WeaponTurnRate;
	float WeaponTurnMin;
	float WeaponTurnMax;
	float WeaponError;
	int WeaponDefID;
	int SeconaryWeaponDefID;
	int WeaponRounds;
};

class ArmedGameObj : public PhysicalGameObj {
public:
	~ArmedGameObj();
	void On_Post_Load();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Post_Think();
	bool Is_Always_Dirty();
	ArmedGameObj *As_ArmedGameObj();
	void Export_Frequent(BitStreamClass &BitStream);
	void Import_Frequent(BitStreamClass &BitStream);
	virtual void Import_State_Cs(BitStreamClass &BitStream);
	virtual void Export_State_Cs(BitStreamClass &BitStream);
	virtual Matrix3D Get_Muzzle(int muzzle);
	virtual bool Set_Targeting(const Vector3& target, bool b);
	WeaponBagClass *WeaponBag;
	Vector3 TargetVector;
	int MuzzleBoneIndexes[4];
	MuzzleRecoilClass MuzzleRecoils[4];
};

class CinematicGameObjDef : public ArmedGameObjDef {
public:
	~CinematicGameObjDef();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	unsigned long Get_Class_ID();
	PersistClass *Create();
	int SoundDefID;
	StringClass SoundBoneName;
	StringClass AnimationName;
	bool AutoFireWeapon;
	bool DestroyAfterAnimation;
	bool CameraRelative;
};

class CinematicGameObj : public ArmedGameObj {
public:
	~CinematicGameObj();
	void On_Post_Load();
	PersistFactoryClass &Get_Factory();
	bool Save(ChunkSaveClass &csave);
	bool Load(ChunkLoadClass &cload);
	void Init();
	void Think();
	void Post_Think();
	void Completly_Damaged(const OffenseObjectClass &offense);
	bool Takes_Explosion_Damage();
	CinematicGameObj *As_CinematicGameObj();
	void Export_Rare(BitStreamClass &BitStream);
	void Import_Rare(BitStreamClass &BitStream);
	AudibleSoundClass *Sound;
};

//type/class ID values for various things
#define Beacon 0x3016
#define Building 0xD001 //only covers generic buildings,not the special stuff like PowerPlant or Refinery
#define C4 0x3006
#define PowerPlant 0xD003
#define PowerUp 0x3003
#define Refinery 0xD002
#define RepairBay 0xD009
#define SamSite 0x3007
#define ScriptZone 0x300E
#define SimpleObj 0x3004
#define Soldier 0x3001
#define SoldierFactory 0xD004
#define SpecialEffects 0x3013
#define Vehicle 0x3010
#define VehicleFactory 0xD005 //for WarFactory or Airstrip,use the relavent values
#define WarFactory 0xD007
#define Airstrip 0xD006
#define Cinematic 0x3011
#define ComCenter 0xD008

extern SList<GameObject> *BuildingGameObjList; //list of all buildings
extern SList<GameObject> *SmartGameObjList; //list of all soldiers and vehicles
extern SList<GameObject> *BaseGameObjList; //list of all objects

void InitEngineObj(unsigned int exe);
int Get_Object_Type(GameObject *obj); //get the team of an object,0 = Nod,1 = GDI,2 = neutral,works on buildings
void Set_Object_Type(GameObject *obj,int type); //set the team of an object,0 = Nod,1 = GDI,2 = neutral,works on buildings
GameObject *As_ArmedGameObj(GameObject *obj); //Check if object is an ArmedGameObj
GameObject *As_BeaconGameObj(GameObject *obj); //Check if object is a BeaconGameObj
GameObject *As_C4GameObj(GameObject *obj); //Check if object is a C4GameObj
GameObject *As_ScriptableGameObj(GameObject *obj); //Check if object is a ScritableGameObj
GameObject *As_VehicleGameObj(GameObject *obj); //Check if object is a VehicleGameObj
GameObject *As_SoldierGameObj(GameObject *obj); //Check if object is a SoldierGameObj
GameObject *As_BuildingGameObj(GameObject *obj); //Check if object is a BuildingGameObj
GameObject *As_SmartGameObj(GameObject *obj); //Check if object is a SmartGameObj
GameObject *As_PhysicalGameObj(GameObject *obj); //Check if object is a PhysicalGameObj
GameObject *As_DamageableGameObj(GameObject *obj); //Check if object is a DamageableGameObj
GameObject *As_ScriptZoneGameObj(GameObject *obj); //Check if object is a ScriptZoneGameObj
GameObject *As_VehicleFactoryGameObj(GameObject *obj); //Check of object is a VehicleFactoryGameObj
bool Is_Building(GameObject *obj); //is a BuildingGameObj
bool Is_Soldier(GameObject *obj); //is a SoldierGameObj
bool Is_Vehicle(GameObject *obj); //is a VechicleGameObj
bool Is_Cinematic(GameObject *obj); //is a CinematicGameObj
bool Is_ScriptZone(GameObject *obj); //is a ScriptZoneGameObj
bool Is_Powerup(GameObject *obj); //is a PowerUpGameObj
bool Is_C4(GameObject *obj); //is a C4GameObj
bool Is_Beacon(GameObject *obj); //is a BeaconGameObj
bool Is_Armed(GameObject *obj); //is an ArmedGameObj
bool Is_Simple(GameObject *obj); //is a SimpleGameObj
bool Is_PowerPlant(GameObject *obj); //is a PowerPlantGameObj
bool Is_SoldierFactory(GameObject *obj); //is a SoldierFactoryGameObj
bool Is_VehicleFactory(GameObject *obj); //is a VehicleFactoryGameObj
bool Is_Airstrip(GameObject *obj); //is an AirstripGameObj
bool Is_WarFactory(GameObject *obj); //is a WarFactoryGameObj
bool Is_Refinery(GameObject *obj); //is a RefineryGameObj
bool Is_ComCenter(GameObject *obj); //is a ComCenterGameObj
bool Is_RepairBay(GameObject *obj); //is a RepairBayGameObj
bool Is_Scriptable(GameObject *obj); //is a ScriptableGameObj
const char *Get_Building_Type(GameObject *obj); //returns a string indicating the building type of an object
void Get_Object_Color(GameObject *obj, unsigned int *red, unsigned int *green, unsigned int *blue); //get color for a player
GameObject *Find_Smart_Object_By_Team(int Team); //will find the first SmartGameObj (i.e. soldier or vechicle) for the team,0 = Nod,1 = GDI
GameObject *Find_Object_By_Team(int Team); //will find the first object for the team,0 = Nod,1 = GDI
GameObject *Find_Non_Player_Object_By_Team(int Team); //will find the first non player object for the team,0 = Nod,1 = GDI
GameObject *Find_Object_By_Preset(int Team,const char *Preset_Name); //will find the first object of team matching preset,0 = Nod,1 = GDI,2 = either
GameObject *Find_Closest_Non_Building_Object_By_Team(int Team,Vector3 position); //find the closest non building object to position
GameObject *Find_Closest_Preset_By_Team(int Team,const Vector3 &pos,const char *Preset); //Find the closest object of this preset to this position
GameObject *Find_Random_Preset_By_Team(int Team,const char *Preset); //Find a random object on this team with this preset
int Get_Object_Count(int Team,const char *Preset); //Get the number of objects that exist with this preset
SimpleDynVecClass<GameObject*> Get_All_Objects_By_Preset(int Team,const char *Preset); //Returns an array of all objects of this preset
GameObject *Find_Nearest_Preset(Vector3 position, const char* preset); //find the nearest preset
GameObject *Find_Random_Preset(const char* preset, int min, int max); //find a random preset
void Send_Custom_To_Team_Buildings(int Team,GameObject *sender,int message,int param,float delay); //send custom to team buildings
void Send_Custom_To_Team_Preset(int Team,const char *PresetName,GameObject *sender,int message,int param,float delay); //send custom to team preset
void Send_Custom_All_Objects_Area(int message,const Vector3 &Position,float Distance,GameObject *sender,int team); //sends a custom to all objects in a given area
void Send_Custom_All_Objects(int message,GameObject *sender,int team); //sends a custom to all objects
void Send_Custom_Event_To_Object(GameObject *sender,const char *Preset,int message,int param,float delay); //this is like Send_Custom_Event except it sends to all objects of the passed in preset
bool Is_Unit_In_Range(const char *preset,float range,Vector3 location,int team); //Is the given unit type in range of a location
bool Get_Is_Powerup_Persistant(GameObject *obj); //Returns if this powerup is persistant
void Set_Is_Powerup_Persistant(GameObject *obj,bool Persist); //Sets if this powerup is persistant
bool Get_Powerup_Always_Allow_Grant(GameObject *obj); //Returns if this powerup is set to always allows grant
void Set_Powerup_Always_Allow_Grant(GameObject *obj,bool Grant); //Change if this powerup is set to always allows grant
int Get_Powerup_Grant_Sound(GameObject *obj); //Returns the sound that is played when this powerup is picked up
void Set_Powerup_Grant_Sound(GameObject *obj,int SoundID); //Set the sound that is played when this powerup is picked up
void Grant_Powerup(GameObject *obj,const char *Preset_Name); //grants a powerup
