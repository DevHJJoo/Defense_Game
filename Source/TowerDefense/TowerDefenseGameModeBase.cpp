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

	DefaultPawnClass = AMyCharacter::StaticClass();

	//ConstructorHelpers::FClassFinder<APawn>
	//	MainCharacterClass(TEXT("MyCharacter"));

	//if (MainCharacterClass.Succeeded())
	//{
	//	DefaultPawnClass = MainCharacterClass.Class;
	//}
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// InputMode
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	//FInputModeUIOnly mode;
	//FInputModeGameOnly mode;
	FInputModeGameAndUI mode;

	Controller->SetInputMode(mode);
	Controller->bShowMouseCursor = true; // ������ ���콺 Ŀ���� ���̰� �Ѵ�.
	Controller->bEnableClickEvents = true;	// ���콺 Ŭ�� �̺�Ʈ�� �߻��ϵ��� �Ѵ�.
	Controller->bEnableMouseOverEvents = true; // ���콺 ���� �̺�Ʈ�� �߻��ϵ��� �Ѵ�.
	ULevelStreamMgr::GetInst(GetWorld())->LoadAssetAsync();
}