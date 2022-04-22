#include "MyTower.h"

#include "../MyAnimInstance.h"
#include "../Monster/Monster.h"

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

	m_DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	m_DetectSphere->SetupAttachment(m_Root);
	m_DetectSphere->SetCollisionProfileName(TEXT("TowerType"));
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

	TArray<AActor*> TargetList;

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), TargetList);
	/*for (AActor* TargetList : TargetList)
	{
		TargetList.
	}
	if (nullptr != TargetList)
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
	}*/
	
	
	/*m_fDirection += DeltaTime * 40.f;
	if (m_fDirection >= 360.f)
		m_fDirection = 0.f;*/
}