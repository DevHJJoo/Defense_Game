// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTower.generated.h"

UCLASS()
class TOWERDEFENSE_API AMyTower : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* m_Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* m_TowerMesh;

	UPROPERTY(VisibleAnywhere)
	int	m_TowerLv;

	UPROPERTY(VisibleAnywhere)
	int m_TowerType;

protected:
	USkeletalMeshComponent* GetMesh() { return m_TowerMesh; }
	void SetTowerLv(int _Lv) { m_TowerLv = _Lv; }
	void SetTowerType(int _TowerType) { m_TowerType = _TowerType; }
	int GetTowerLv() { return m_TowerLv; }
	int GetTowerType() { return m_TowerType; }

public:
	// Sets default values for this pawn's properties
	AMyTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual bool UpgradeTower();
	virtual void RemoveTower();
};
