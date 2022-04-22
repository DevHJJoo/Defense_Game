#include "Normal_Rat.h"

#include "../../MyGameInstance.h"

ANormal_Rat::ANormal_Rat()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		RatMesh(TEXT("SkeletalMesh'/Game/RPGMonsterWave02Polyart/Meshes/RatAssassinMesh.RatAssassinMesh'"));

	if (RatMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(RatMesh.Object);
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
}

bool ANormal_Rat::ChangeState(EMON_STATE _eNextState)
{
	return false;
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

}

void ANormal_Rat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ANormal_Rat::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
}
