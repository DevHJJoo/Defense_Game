// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "MyGameInstance.h"
#include "Player/MyCharacter.h"

#include "manager/LevelStreamMgr.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	// ���� ĳ���� Ŭ���� ���� �˸� (��ü ���� �� �÷��̾� ��Ʈ�ѷ� ������)
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == GI)
		return;

	ConstructorHelpers::FClassFinder<APawn>
		MainCharacterClass(TEXT("Blueprint'/Game/BlueprintClass/BPC_Hero.BPC_Hero_C'"));

	if (MainCharacterClass.Succeeded())
	{
		DefaultPawnClass = MainCharacterClass.Class;
	}
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// InputMode
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	//FInputModeUIOnly mode;
	FInputModeGameOnly mode;
	//FInputModeGameAndUI mode;

	Controller->SetInputMode(mode);
	Controller->bShowMouseCursor = false; // ������ ���콺 Ŀ���� ���̰� �Ѵ�.

	ULevelStreamMgr::GetInst(GetWorld())->LoadAssetAsync();
}