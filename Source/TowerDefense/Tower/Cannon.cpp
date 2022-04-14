// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"


// Sets default values
ACannon::ACannon()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		CannonMesh(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv01/Cannon_Lv01.Cannon_Lv01'"));

	if (CannonMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CannonMesh.Object);
	}

	SetTowerLv(1);
	SetTowerType(1);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpgradeTower();
}

bool ACannon::UpgradeTower()
{
	if (1 != GetTowerType())
	{
		return false;
	}
	
	int CurLv = GetTowerLv();
	FString TargetMeshStr;
	switch (CurLv)
	{
		case 1:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv02/Cannon_Lv02.Cannon_Lv02'"));
			break;
		case 2:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv03/Cannon_Lv03.Cannon_Lv03'"));
			break;
		case 3:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv04/Cannon_Lv04.Cannon_Lv04'"));
			break;
		case 4:
			break;
		default:
			break;
	}

	USkeletalMesh* CannonMesh = LoadObject<USkeletalMesh>(NULL, *TargetMeshStr);
	
	if (CannonMesh)
	{
		GetMesh()->SetSkeletalMesh(CannonMesh);

		SetTowerLv(CurLv + 1);
		return true;
	}

	return false;
}

void ACannon::RemoveTower()
{
	Destroy();
}