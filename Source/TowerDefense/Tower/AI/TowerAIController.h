#include "CoreMinimal.h"
#include "AIController.h"
#include "TowerAIController.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATowerAIController();

	// BehaviorTreeComponent
	// BlackboardComponent
	UBehaviorTree* m_BehaviorTree;

	UBlackboardData* m_Blackboard;

public:
	virtual void OnPossess(APawn* _mon) override;
	virtual void OnUnPossess() override;
};
