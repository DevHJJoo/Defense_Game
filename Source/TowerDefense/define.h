#pragma once

UENUM(BlueprintType)
enum class ETOWER_STATE : uint8
{
	INSTALL,
	IDLE,
	ATTACK,
	UPGRADE,
	REMOVEWITHUPGRADE,
	REMOVE,
	END,
};

UENUM(BlueprintType)
enum class ETOWER_TYPE : uint8
{
	NONE,
	CANNON,
	MORTAR,
	TOWER3,
	TOWER4,
	TOWER5,
	TOWER6,
};