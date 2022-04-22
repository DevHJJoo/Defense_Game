#include "Cannon.h"

#include "../Effect/MyEffect.h"
#include "../Manager/EffectMgr.h"
#include "../Projectile/Missile/Missile.h"
#include "../MyGameInstance.h"

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

	FTowerInfo info = {};

	/*
	반드시 테스트 후 이 변수는 지울 것.
	*/
	m_fAttackInterval = 0.f;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	int CurLv = GetTowerLv();
	switch (CurLv)
	{
	case 4:
		SetTowerTable("CannonLv4");
		break;
	case 3:
		SetTowerTable("CannonLv3");
		break;
	case 2:
		SetTowerTable("CannonLv2");
		break;
	case 1:
	default:
		SetTowerTable("CannonLv1");
		break;
	}

	SetDetectSphereSize(GetTowerInfo().fDetectRange);
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
	FName fnSocket = FName(TEXT("Bone_002socket"));
	FTransform tEffectTrans = GetMesh()->GetSocketTransform(fnSocket);

	Vec3 vScale = Vec3(3.f);
	tEffectTrans.SetScale3D(vScale);

	UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::MUZZLEFLASH, tEffectTrans, GetLevel());
	ACannon::SpawnProjectile(tEffectTrans);

	if (4 == GetTowerLv())
	{
		fnSocket = FName(TEXT("Bone_002socket1"));
		tEffectTrans = GetMesh()->GetSocketTransform(fnSocket);
		
		tEffectTrans.SetScale3D(vScale);

		UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::MUZZLEFLASH, tEffectTrans, GetLevel());
		ACannon::SpawnProjectile(tEffectTrans);
	}
}

void ACannon::SetTowerTable(const FString& _TowerStr)
{
	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FTowerInfo* pTableRow = pGameInst->GetTowerInfo(_TowerStr);
		if (nullptr != pTableRow)
		{
			SetTowerInfo(*pTableRow);
		}
	}
}

void ACannon::SpawnProjectile(FTransform _trans)
{
	Vec3 vPos = _trans.GetLocation();
	Vec3 vForward = _trans.GetRotation().Rotator().Vector();

	FActorSpawnParameters SpawnParam = {};
	// 생성될 레벨
	SpawnParam.OverrideLevel = GetLevel();
	// 충돌될 지점이 어디인지에 따라 스폰을 할 지에 대한 것을 나타냄
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 지연 스폰.
	SpawnParam.bDeferConstruction = true;

	AMissile* pMissile = GetWorld()->SpawnActor<AMissile>(m_Projectile
		, vPos + vForward * 50.f
		, vForward.Rotation(), SpawnParam);

	// BeginPlay 호출
	pMissile->FinishSpawning(pMissile->GetTransform());
}

bool ACannon::ChangeTower(int _CurLv)
{
	if (4 == _CurLv)
		return false;

	FString TargetMeshStr;
	FString TargetABPStr;

	switch (_CurLv)
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
	default:
		break;
	}

	USkeletalMesh* CannonMesh = LoadObject<USkeletalMesh>(NULL, *TargetMeshStr);
	UAnimBlueprint* CannonABP = LoadObject<UAnimBlueprint>(NULL, *TargetABPStr);

	if (nullptr != CannonMesh
		&& nullptr != CannonABP)
	{
		GetMesh()->SetAnimInstanceClass(nullptr);
		GetMesh()->SetSkeletalMesh(CannonMesh);
		GetMesh()->SetAnimInstanceClass(CannonABP->GeneratedClass);
	}
	else
	{
		return false;
	}

	return true;
}

void ACannon::DestroyProcess()
{
	Destroy();
}

void ACannon::Install()
{
	int CurLv = GetTowerLv();
	switch (CurLv)
	{
	case 4:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv4");
		break;
	case 3:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv3");
		break;
	case 2:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv2");
		break;
	case 1:
	default:
		break;
	}

	SetDetectSphereSize(GetTowerInfo().fDetectRange);
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

	int CurLv = GetTowerLv();

	ETOWER_STATE eState = GetState();

	if(ETOWER_STATE::NEEDUPGRADE != eState)
		return;

	SetTowerLv(++CurLv);
	SetUpgrade(false);
	ChangeState(ETOWER_STATE::INSTALL);
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

