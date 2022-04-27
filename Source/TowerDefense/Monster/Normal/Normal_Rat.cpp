#include "Normal_Rat.h"

#include "../../MyGameInstance.h"

ANormal_Rat::ANormal_Rat()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		RatMesh(TEXT("SkeletalMesh'/Game/RPGMonsterWave02Polyart/Meshes/RatAssassinMesh.RatAssassinMesh'"));

	if (RatMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(RatMesh.Object);
		GetMesh()->GetRelativeTransform().SetScale3D(Vec3(0.6f));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimBlueprint(TEXT("AnimBlueprint'/Game/BlueprintClass/Monster/Normal/Rat/ABP_Rat.ABP_Rat_C'"));
	if (AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprint.Class);
	}

	// 사용 할 행동트리
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/BlueprintClass/Monster/Normal/BT_NormalMon.BT_NormalMon'"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
	// 사용 할 블랙보드
	ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/BlueprintClass/Monster/Normal/BB_NormalMon.BB_NormalMon'"));

	if (BB.Succeeded())
	{
		SetBlackboard(BB.Object);
	}

	SetUnStopable(false);
}

bool ANormal_Rat::ChangeState(EMON_STATE _eNextState)
{	
	EMON_STATE eCurState = GetState();

	if (EMON_STATE::DEAD == eCurState)
		return false;

	if (EMON_STATE::HIT == _eNextState)
	{
		SetUnStopable(false);
	}

	if (IsUnStopable() || eCurState == _eNextState)
		return false;

	SetState(_eNextState);

	switch (GetState())
	{
	case EMON_STATE::IDLE:
		SetState(EMON_STATE::MOVE);
		break;
	case EMON_STATE::MOVE:
		break;
	case EMON_STATE::HIT:
		break;
	case EMON_STATE::DEAD:
		GetMovementComponent()->StopMovementImmediately();
		SetUnStopable(true);
		GetMesh()->SetSimulatePhysics(true);
		SetLifeSpan(2);
		break;
	default:
		break;
	}

	return true;
}

void ANormal_Rat::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FMonInfo* pTableRow = pGameInst->GetMonInfo(TEXT("NormalRatEasy"));
		if (nullptr != pTableRow)
		{
			SetMonInfo(*pTableRow);
		}
	}

	SetState(EMON_STATE::MOVE);
}

void ANormal_Rat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANormal_Rat::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	if (ECC_GameTraceChannel4 == _OtherComp->GetCollisionObjectType())
	{
		LOG(Warning, "MonsterOverlap");
		ChangeState(EMON_STATE::HIT);
		FMonInfo info = GetMonInfo();
		info.fCurHP -= 10.f;
		SetMonInfo(info);
	}
}


void ANormal_Rat::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	if (ECC_GameTraceChannel4 == _OtherComp->GetCollisionObjectType())
	{
		LOG(Warning, "MonsterHit");
		ChangeState(EMON_STATE::HIT);
		FMonInfo info = GetMonInfo();
		info.fCurHP -= 10.f;
		SetMonInfo(info);
	}
}