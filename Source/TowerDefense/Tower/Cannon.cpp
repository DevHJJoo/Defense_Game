// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"


// Sets default values
ACannon::ACannon()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		CannonMesh(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv01/CannonLv1Mesh.CannonLv1Mesh'"));

	if (CannonMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CannonMesh.Object);
	}

	ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimBlueprint(TEXT("AnimBlueprint'/Game/BlueprintClass/Tower/Cannon/ABP_CannonLv1.ABP_CannonLv1_C'"));
	if (AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprint.Class);
	}

	SetTowerLv(1);
	SetTowerType(ETOWER_TYPE::CANNON);
	ChangeState(ETOWER_STATE::INSTALL);
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

	if (IsNeedToUpgrade())
	{
		Upgrade();
	}

	static bool change = false;
	static float testval = 0.f;
	testval += DeltaTime;

	if (testval >= 3.0
		&& GetTowerLv() != 4)
	{
		change = true;
		testval = 0.f;
		ChangeState(ETOWER_STATE::REMOVEWITHUPGRADE);
	}
}

void ACannon::DestroyProcess()
{
}

void ACannon::Install()
{
	ChangeState(ETOWER_STATE::IDLE);
}

void ACannon::Idle()
{
}

void ACannon::Attack()
{
}

void ACannon::NeedUpgrade()
{
	SetUpgrade(true);
}

void ACannon::Upgrade()
{
	if (ETOWER_TYPE::CANNON != GetTowerType())
	{
		return;
	}

	ETOWER_STATE eState = GetState();

	if(ETOWER_STATE::NEEDUPGRADE != eState)
		return;

	int CurLv = GetTowerLv();
	FString TargetMeshStr;
	FString TargetABPStr;

	switch (CurLv)
	{
	case 1:
		{
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv02/CannonLv2Mesh.CannonLv2Mesh'"));
			TargetABPStr = FString(TEXT("AnimBlueprint'/Game/BlueprintClass/Tower/Cannon/ABP_CannonLv2.ABP_CannonLv2'"));			
		}
		break;
	case 2:
	{
		TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv03/CannonLv3Mesh.CannonLv3Mesh'"));
		TargetABPStr = FString(TEXT("AnimBlueprint'/Game/BlueprintClass/Tower/Cannon/ABP_CannonLv3.ABP_CannonLv3'"));
	}
		
		break;
	case 3:
	{
		TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv04/CannonLv4Mesh.CannonLv4Mesh'"));
		TargetABPStr = FString(TEXT("AnimBlueprint'/Game/BlueprintClass/Tower/Cannon/ABP_CannonLv4.ABP_CannonLv4'"));
	}		
		break;
	case 4:
		return;
		break;
	default:
		break;
	}

	USkeletalMesh* CannonMesh = LoadObject<USkeletalMesh>(NULL, *TargetMeshStr);
	UAnimBlueprint* CannonABP = LoadObject<UAnimBlueprint>(NULL, *TargetABPStr);
	
	if (nullptr != CannonMesh
		&& nullptr != CannonABP)
	{
		RemoveMontage();
		GetMesh()->SetAnimInstanceClass(nullptr);
		GetMesh()->SetSkeletalMesh(CannonMesh);
		GetMesh()->SetAnimInstanceClass(CannonABP->GeneratedClass);

		SetTowerLv(CurLv + 1);

		ChangeState(ETOWER_STATE::INSTALL);		
	}
}

void ACannon::RemoveWithUpgarde()
{
	/*if (nullptr != m_arrMontage[ETOWER_MONTAGE::REMOVE])
		GetAnimInst()->Montage_Play(m_arrMontage[ETOWER_MONTAGE::REMOVE]);*/
}

void ACannon::Remove()
{
	/*if (nullptr != m_arrMontage[ETOWER_MONTAGE::REMOVE])
		GetAnimInst()->Montage_Play(m_arrMontage[ETOWER_MONTAGE::REMOVE]);*/
}

