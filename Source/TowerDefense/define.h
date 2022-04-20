#pragma once

DECLARE_LOG_CATEGORY_EXTERN(Client, Log, All);

// Output Log
// Syntax : LOG([Verbose], ["¹®ÀÚ¿­"])
// Verbose : (Fatal, Error, Warning, Display, Log, Verbose, VeryVerbose)
#define LOG(Verbose, String) UE_LOG(Client, Verbose, TEXT("%s"),\
					 *FString::Printf(TEXT("%s : { %d } : %s"), *FString(__FUNCTION__), __LINE__, String));

#define SINGLE_H(type)	private:\
							static type* m_This;\
							static UWorld* m_World;\
						public:\
							static type* GetInst(UWorld* _world);\
							static void Destroy();\
						private:\
							type();\
							~type();


#define SINGLE_CPP(type)	type* type::m_This = nullptr;\
							UWorld* type::m_World = nullptr;\
							type::type()\
							{\
							}\
							type::~type()\
							{\
							}\
							type* type::GetInst(UWorld* _world)\
							{\
							   if (nullptr == m_This)\
							   {\
								   m_This = NewObject<type>();\
								   m_This->AddToRoot();\
								   m_World = _world;\
							   }\
							   if (m_World != _world)\
							   {\
								   m_World = _world;\
							   }\
								return m_This;\
							}\
							void type::Destroy()\
							{\
							   if (nullptr != m_This)\
							   {\
								   m_This->ConditionalBeginDestroy();\
								   m_This = nullptr;\
								   m_World = nullptr;\
							   }\
							}

typedef FVector Vec3;


UENUM(BlueprintType)
enum class ETOWER_STATE : uint8
{
	INSTALL,
	IDLE,
	ATTACK,
	NEEDUPGRADE,
	REMOVEWITHUPGRADE,
	REMOVE,
};

UENUM(BlueprintType)
enum class ETOWER_TYPE : uint8
{
	CANNON,
	MORTAR,
	TOWER3,
	TOWER4,
	TOWER5,
	TOWER6,
};

enum ETOWER_MONTAGE : uint8
{
	INSTALL = 0,
	ATTACK,
	IDLE,
	REMOVE,
};

UENUM(BlueprintType)
enum class EMON_STATE : uint8
{
	IDLE = 0,
	MOVE,
	HIT,
	DEAD
};

UENUM(BlueprintType)
enum class EEFFECT_TYPE : uint8
{
	MUZZLEFLASH,
	EXPLOSION,
	TRAIL,
	SMOKE,
	HIT,
	ZONE,
};