// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTower.h"

// Sets default values
AMyTower::AMyTower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_Root);

	m_TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TowerMesh"));
	m_TowerMesh->SetupAttachment(m_Root);
}

// Called when the game starts or when spawned
void AMyTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMyTower::UpgradeTower()
{
	return true;
}

void AMyTower::RemoveTower()
{
	Destroy();
}