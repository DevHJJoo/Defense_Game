// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "PlayerHUD.h"
#include "TowerSelect.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UPlayerHUD* m_PlayerHUD;
	UTowerSelect* m_TowerSelect;

public:
	UPlayerHUD* GetPlayerHUD() { return m_PlayerHUD; }
	UTowerSelect* GetTowerSelect() { return m_TowerSelect; }
	
	void ToggleTowerSelect(bool _On);

	void SetTowerSelectTarget(ATowerPod* _target) { m_TowerSelect->SetTargetPod(_target); }

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DT) override;
	
};
