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

	ConstructorHelpers::FObjectFinder<UAnimMontage> Install
	(TEXT("AnimMontage'/Game/BlueprintClass/Tower/Cannon/AM_CannonLv1_Install.AM_CannonLv1_Install'"));
	ConstructorHelpers::FObjectFinder<UAnimMontage> Remove
	(TEXT("AnimMontage'/Game/BlueprintClass/Tower/Cannon/AM_CannonLv1_Remove.AM_CannonLv1_Remove'"));
	ConstructorHelpers::FObjectFinder<UAnimMontage> Attack
	(TEXT("AnimMontage'/Game/BlueprintClass/Tower/Cannon/AM_CannonLv1_Attack.AM_CannonLv1_Attack'"));

	if (Install.Succeeded())
		m_arrMontage.Add(Install.Object);
	if (Remove.Succeeded())
		m_arrMontage.Add(Remove.Object);
	if (Attack.Succeeded())
		m_arrMontage.Add(Attack.Object);


	SetTowerLv(1);
	SetTowerType(ETOWER_TYPE::CANNON);
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

}

bool ACannon::UpgradeTower()
{
	if (ETOWER_TYPE::CANNON != GetTowerType())
	{
		return false;
	}

	ETOWER_STATE eState = GetState();
	
	// Upgrade에 이미 진입한 경우
	// Upgrade 과정이 종료될 때 까지 Tower Upgrade를 금지한다.
	if (ETOWER_STATE::REMOVE == eState
	|| ETOWER_STATE::REMOVEWITHUPGRADE == eState)
		return false;
	
	int CurLv = GetTowerLv();
	FString TargetMeshStr;
	FString TargetABPStr;
	FString TargetMontageStr;

	switch (CurLv)
	{
		case 1:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv02/CannonLv2Mesh.CannonLv2Mesh'"));
			break;
		case 2:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv03/CannonLv3Mesh.CannonLv3Mesh'"));
			break;
		case 3:
			TargetMeshStr = FString(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv04/CannonLv4Mesh.CannonLv4Mesh'"));
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
	GetAnimInst()->Montage_Play(m_arrMontage[2]);
}