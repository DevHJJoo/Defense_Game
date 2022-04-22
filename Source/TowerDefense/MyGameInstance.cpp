#include "MyGameInstance.h"

#include "Manager/EffectMgr.h"

UMyGameInstance::UMyGameInstance()
	: m_MonTable(nullptr)
	, m_TowerTable(nullptr)
{
	ConstructorHelpers::FObjectFinder<UDataTable> monTable(TEXT("DataTable'/Game/BlueprintClass/Monster/MonTable.MonTable'"));
	if (monTable.Succeeded())
	{
		m_MonTable = monTable.Object;		
	}

	ConstructorHelpers::FObjectFinder<UDataTable> towerTable(TEXT("DataTable'/Game/BlueprintClass/Tower/TowerInfo.TowerInfo'"));
	if (towerTable.Succeeded())
	{
		m_TowerTable = towerTable.Object;
	}
}

UMyGameInstance::~UMyGameInstance()
{
	UEffectMgr::Destroy();
}

const FMonInfo* UMyGameInstance::GetMonInfo(const FString& _RowName)
{
	FMonInfo* pMonInfo = m_MonTable->FindRow<FMonInfo>(FName(_RowName), TEXT(""));
	return pMonInfo;
}

const FTowerInfo* UMyGameInstance::GetTowerInfo(const FString& _RowName)
{
	FTowerInfo* pTowerInfo = m_TowerTable->FindRow<FTowerInfo>(FName(_RowName), TEXT(""));
	return pTowerInfo;
}