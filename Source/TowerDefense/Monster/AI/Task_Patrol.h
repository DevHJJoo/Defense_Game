// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTask_Patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
