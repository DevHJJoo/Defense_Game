#pragma once

#include "../../global.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnemyDetection.generated.h"

/** 
 * Class on what conditions to detect enemies
 */

class AMonster;

UCLASS()
class TOWERDEFENSE_API UEnemyDetection : public UBTService
{
	GENERATED_BODY()

public:
	UEnemyDetection();

private:
	AMonster*	m_pTarget;

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
