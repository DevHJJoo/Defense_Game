// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn>
		MainCharacterClass(TEXT("Blueprint'/Game/BlueprintClass/BPC_Hero.BPC_Hero_C'"));

	if (MainCharacterClass.Succeeded())
	{
		DefaultPawnClass = MainCharacterClass.Class;
	}
}
