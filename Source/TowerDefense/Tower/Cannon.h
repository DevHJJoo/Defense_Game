// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"
#include "../MyAnimInstance.h"

#include "CoreMinimal.h"
#include "MyTower.h"
#include "Cannon.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ACannon : public AMyTower
{
	GENERATED_BODY()

public:
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual bool UpgradeTower() override;
	virtual void RemoveTower() override;
};
