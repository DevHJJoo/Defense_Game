#include "Task_Patrol.h"

UTask_Patrol::UTask_Patrol()
{

}

EBTNodeResult::Type UTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::InProgress;
}
