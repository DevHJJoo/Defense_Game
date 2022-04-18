// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "../Effect/MyEffect.h"

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

	/*
	반드시 테스트 후 이 변수는 지울 것.
	*/
	m_fAttackInterval = 0.f;
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

	m_fAttackInterval += DeltaTime;
	if (m_fAttackInterval >= 3.0)
	{
		m_fAttackInterval = 0.f;
		ChangeState(ETOWER_STATE::ATTACK);
	}
}

void ACannon::Fire()
{
	const FName fnSocket1 = FName(TEXT("Bone_002socket"));
	const FName fnSocket2 = FName(TEXT("Bone_002socket1"));

	/*if ((nullptr == GetMesh()->GetSocketByName(fnSocket1))
		|| (nullptr == GetMesh()->GetSocketByName(fnSocket2)))
		return;*/

	FActorSpawnParameters SpawnParam = {};

	// 지연 생성
	SpawnParam.OverrideLevel = GetLevel();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;


	Vec3 vScale = Vec3(3.f);

	FTransform tEffectTrans = GetMesh()->GetSocketTransform(fnSocket1);
	tEffectTrans.SetScale3D(vScale);

	AMyEffect* pEffect = GetWorld()->SpawnActor<AMyEffect>(AMyEffect::StaticClass(), tEffectTrans, SpawnParam);
	pEffect->SetEffectType(EEFFECT_TYPE::MUZZLEFLASH);

	pEffect->FinishSpawning(pEffect->GetTransform());

	if (4 == GetTowerLv())
	{
		tEffectTrans = GetMesh()->GetSocketTransform(fnSocket2);
		tEffectTrans.SetScale3D(vScale);

		pEffect = GetWorld()->SpawnActor<AMyEffect>(AMyEffect::StaticClass(), tEffectTrans, SpawnParam);
		pEffect->SetEffectType(EEFFECT_TYPE::MUZZLEFLASH);

		pEffect->FinishSpawning(pEffect->GetTransform());
	}
}

void ACannon::DestroyProcess()
{
	Destroy();
}

void ACannon::Install()
{
	// Info 구조체를 설정할 것?
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

		SetUpgrade(false);
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

