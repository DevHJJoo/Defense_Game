#pragma once

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