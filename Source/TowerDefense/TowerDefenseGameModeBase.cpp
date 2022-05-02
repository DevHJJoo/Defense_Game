// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "MyGameInstance.h"
#include "Player/MyCharacter.h"

#include "manager/LevelStreamMgr.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	// 시작 캐릭터 클래스 정보 알림 (객체 생성 및 플레이어 컨트롤러 부착용)
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
	Controller->bShowMouseCursor = true; // 언제나 마우스 커서가 보이게 한다.
	Controller->bEnableClickEvents = true;	// 마우스 클릭 이벤트가 발생하도록 한다.
	Controller->bEnableMouseOverEvents = true; // 마우스 오버 이벤트가 발생하도록 한다.
	ULevelStreamMgr::GetInst(GetWorld())->LoadAssetAsync();
}