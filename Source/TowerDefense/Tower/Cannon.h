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
	virtual void DestroyProcess() override;

protected:
	virtual void Install() override;
	virtual void Idle() override;
	virtual void Attack() override;
	virtual void NeedUpgrade() override;
	virtual void Upgrade() override;
	virtual void RemoveWithUpgarde() override;
	virtual void Remove() override;
};
