// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTower.h"
#include "../MyAnimInstance.h"

// Sets default values
AMyTower::AMyTower()
	: m_bAttack(false)
	, m_eState(ETOWER_STATE::INSTALL)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_Root);

	m_TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TowerMesh"));
	m_TowerMesh->SetupAttachment(m_Root);
}

void AMyTower::ChangeState(ETOWER_STATE _eNextState)
{
	m_eState = _eNextState;
	switch (_eNextState)
	{
	case ETOWER_STATE::INSTALL:
		break;
	case ETOWER_STATE::IDLE:
		break;
	case ETOWER_STATE::ATTACK:
		break;
	case ETOWER_STATE::UPGRADE:
		break;
	case ETOWER_STATE::REMOVEWITHUPGRADE:
		break;
	case ETOWER_STATE::REMOVE:
		break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void AMyTower::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fDirection += DeltaTime * 40.f;
	if (m_fDirection >= 360.f)
		m_fDirection = 0.f;

	m_eState = ETOWER_STATE::ATTACK;

}

bool AMyTower::UpgradeTower()
{
	return true;
}

void AMyTower::RemoveTower()
{
	Destroy();
}