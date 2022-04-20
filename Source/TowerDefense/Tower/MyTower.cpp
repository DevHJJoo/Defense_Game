// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTower.h"
#include "../MyAnimInstance.h"
#include "../Player/MyCharacter.h"

// Sets default values
AMyTower::AMyTower()
	: m_bIsNeedToUpgrade(false)
	, m_eState(ETOWER_STATE::IDLE)
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
	if (m_eState == _eNextState)
		return;
	
	m_eState = _eNextState;

	switch (_eNextState)
	{
	case ETOWER_STATE::INSTALL:
	{
		Install();
	}
		break;
	case ETOWER_STATE::IDLE:
	{
		Idle();
	}
		break;
	case ETOWER_STATE::ATTACK:
	{
		Attack();
	}
		break;
	case ETOWER_STATE::NEEDUPGRADE:
	{
		NeedUpgrade();
	}
		break;
	case ETOWER_STATE::REMOVEWITHUPGRADE:
	{
		RemoveWithUpgarde();
	}
		break;
	case ETOWER_STATE::REMOVE:
	{
		Remove();
	}
		break;
	default:
		break;
	}
}

void AMyTower::InitTowerMontage(const TCHAR* _strInstall, const TCHAR* _strAttack, const TCHAR* _strIdle, const TCHAR* _strRemove)
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> Install
	(_strInstall);
	ConstructorHelpers::FObjectFinder<UAnimMontage> Attack
	(_strAttack);
	ConstructorHelpers::FObjectFinder<UAnimMontage> Idle
	(_strIdle);
	ConstructorHelpers::FObjectFinder<UAnimMontage> Remove
	(_strRemove);

	if (Install.Succeeded())
		m_arrMontage.Add(Install.Object);
	if (Attack.Succeeded())
		m_arrMontage.Add(Attack.Object);
	if (Idle.Succeeded())
		m_arrMontage.Add(Idle.Object);
	if (Remove.Succeeded())
		m_arrMontage.Add(Remove.Object);
}

void AMyTower::ChangeTowerMontage(const TCHAR* _strInstall, const TCHAR* _strAttack, const TCHAR* _strIdle, const TCHAR* _strRemove)
{
	m_arrMontage.Empty();
	UAnimMontage* Montage = LoadObject<UAnimMontage>(NULL, _strInstall);
	m_arrMontage.Add(Montage);
	Montage = LoadObject<UAnimMontage>(NULL, _strAttack);
	m_arrMontage.Add(Montage);
	Montage = LoadObject<UAnimMontage>(NULL, _strIdle);
	m_arrMontage.Add(Montage);
	Montage = LoadObject<UAnimMontage>(NULL, _strRemove);
	m_arrMontage.Add(Montage);
	return;

	//TArray<UAnimMontage*> ChangedMontage;
	//
	//// _strInstall
	///*UAnimMontage**/ Montage = LoadObject<UAnimMontage>(NULL, _strInstall);
	//if (Montage)
	//	ChangedMontage.Add(Montage);
	//	//m_arrMontage.Add(Montage);
	//else
	//	return false;

	//// _strAttack
	//Montage = LoadObject<UAnimMontage>(NULL, _strAttack);
	//if (Montage)
	//	ChangedMontage.Add(Montage);
	//else
	//	return false;

	//// _strIdle
	//Montage = LoadObject<UAnimMontage>(NULL, _strIdle);
	//if (Montage)
	//	ChangedMontage.Add(Montage);
	//else
	//	return false;

	//// _strRemove
	//Montage = LoadObject<UAnimMontage>(NULL, _strRemove);
	//if (Montage)
	//	ChangedMontage.Add(Montage);
	//else
	//	return false;

	//m_arrMontage.Empty();
	//m_arrMontage = ChangedMontage;
	//return true;
}

// Called when the game starts or when spawned
void AMyTower::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	ChangeState(ETOWER_STATE::INSTALL);
}

// Called every frame
void AMyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMyCharacter* pPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (nullptr != pPlayer)
	{
		Vec3 vTowerPos = GetActorLocation();
		float fDistance = Vec3::Distance(vTowerPos, pPlayer->GetActorLocation());
		
		if (fDistance < 600.f)
		{
			Vec3 vTargetDir = pPlayer->GetActorLocation() - vTowerPos;
			vTargetDir.Z = 0.f;
			vTargetDir.Normalize();

			FRotator fRot = FRotationMatrix::MakeFromX(vTargetDir).Rotator();

			m_fDirection = fRot.Yaw;
		}
		else
		{
			m_fDirection += DeltaTime * 40.f;
			if (m_fDirection >= 360.f)
				m_fDirection = 0.f;
		}
	}
	
	
	/*m_fDirection += DeltaTime * 40.f;
	if (m_fDirection >= 360.f)
		m_fDirection = 0.f;*/
}