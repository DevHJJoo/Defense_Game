#include "EnemyDetection.h"

#include <BehaviorTree/BlackboardComponent.h>
#include "TowerAIController.h"
#include "../../Monster/Monster.h"
#include "../MyTower.h"

UEnemyDetection::UEnemyDetection()
{
	Interval = 0.1;

	RandomDeviation = 0.f;

	NodeName = TEXT("Detect Enemy");

	m_pTarget = nullptr;
}

void UEnemyDetection::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* pController = OwnerComp.GetAIOwner();
	if (nullptr == pController)
		return;

	AMyTower* pTower = Cast<AMyTower>(pController->GetPawn());
	if (nullptr == pTower)
		return;

	USphereComponent* pSphere = pTower->GetDetectSphere();
	if (nullptr == pSphere)
		return;

	TArray<AActor*> OverlapList;
	pSphere->GetOverlappingActors(OverlapList, TSubclassOf<AMonster>());
	
	if (0 == OverlapList.Num())
		return;

	Vec3 vTowerPos = pTower->GetActorLocation();

	if (nullptr == m_pTarget)
	{
		float fDetectRange = pTower->GetTowerInfo().fDetectRange;
		float fPrevTargetDist = fDetectRange;

		for (AActor* TargetIter : OverlapList)
		{
			static float fCheckDist = Vec3::Distance(vTowerPos, TargetIter->GetActorLocation());
			if (fCheckDist < fPrevTargetDist)
			{
				m_pTarget = Cast<AMonster>(TargetIter);
				if (nullptr == m_pTarget)
				{
					pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
					return;
				}

				pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), m_pTarget);
			}
		}
	}
	else
	{
		if (pSphere->IsOverlappingActor(m_pTarget))
		{
			Vec3 vTargetDir = m_pTarget->GetActorLocation() - vTowerPos;
			vTargetDir.Z = 0.f;
			vTargetDir.Normalize();

			FRotator fRot = FRotationMatrix::MakeFromX(vTargetDir).Rotator();
			pTower->SetDirection(fRot.Yaw);
		}
		else
		{
			m_pTarget = nullptr;
			pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
		}
	}
	
}
