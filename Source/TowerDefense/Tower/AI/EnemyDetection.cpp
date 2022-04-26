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

	if (m_fPrevTargetDist == 0.f)
		m_fPrevTargetDist = pTower->GetTowerInfo().fDetectRange;

	pController->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnable"), pTower->GetAttackEnable());

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
		for (AActor* TargetIter : OverlapList)
		{
			float fCheckDist = Vec3::Distance(vTowerPos, TargetIter->GetActorLocation());
			if (fCheckDist <= m_fPrevTargetDist)
			{
				m_fPrevTargetDist = fCheckDist;

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
		if (false == pSphere->IsOverlappingActor(m_pTarget))
		{
			m_pTarget = nullptr;
			m_fPrevTargetDist = 400.f;
			pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		}
	}
	
}
