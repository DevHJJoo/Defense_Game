#include "MonAIController.h"

#include "../Monster.h"


AMonAIController::AMonAIController()
	: m_BehaviorTree(nullptr)
	, m_Blackboard(nullptr)
{

}

void AMonAIController::OnPossess(APawn* _mon)
{
	AMonster* pMonster = Cast<AMonster>(_mon);

	if (nullptr != pMonster)
	{
		m_BehaviorTree = pMonster->GetBehaviorTree();
		m_Blackboard = pMonster->GetBlackboard();
	}
}