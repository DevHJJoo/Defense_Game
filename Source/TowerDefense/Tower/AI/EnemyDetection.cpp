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

	float fTowerDetectRange = pTower->GetTowerInfo().fDetectRange;

	if (m_fPrevTargetDist == 0.f)
		m_fPrevTargetDist = fTowerDetectRange;

	pController->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnable"), pTower->GetAttackEnable());

	USphereComponent* pSphere = pTower->GetDetectSphere();
	if (nullptr == pSphere)
		return;

	TArray<AActor*> OverlapList;
	pSphere->GetOverlappingActors(OverlapList, TSubclassOf<AMonster>());
	
	if (0 == OverlapList.Num())
	{
		m_pTarget = nullptr;
		m_fPrevTargetDist = fTowerDetectRange;
		pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
	}

	if (nullptr != m_pTarget)
	{
		if (EMON_STATE::DEAD == m_pTarget->GetState())
		{
			m_pTarget = nullptr;
			m_fPrevTargetDist = fTowerDetectRange;
			pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
		}
	}

	Vec3 vTowerPos = pTower->GetActorLocation();

	if (nullptr == m_pTarget)
	{
		for (AActor* TargetIter : OverlapList)
		{
			EMON_STATE TargetState = Cast<AMonster>(TargetIter)->GetState();
			if (EMON_STATE::DEAD == TargetState)
				continue;

			float fCheckDist = Vec3::Distance(vTowerPos, TargetIter->GetActorLocation());
			if (fCheckDist <= m_fPrevTargetDist)
			{
				m_pTarget = Cast<AMonster>(TargetIter);				
				m_fPrevTargetDist = fCheckDist;
				if (nullptr == m_pTarget)
				{
					pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
					return;
				}

				pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), m_pTarget);
				break;
			}
		}
	}
	else
	{
		if (nullptr == pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")))
		{
			m_pTarget = nullptr;
			m_fPrevTargetDist = fTowerDetectRange;

			return;
		}

		float fCheckDist = Vec3::Distance(vTowerPos, m_pTarget->GetActorLocation());
		if (fCheckDist > fTowerDetectRange)
		{
			m_pTarget = nullptr;
			m_fPrevTargetDist = fTowerDetectRange;
			pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
		}
	}	
}