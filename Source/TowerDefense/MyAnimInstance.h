// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "global.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "User Define")
	void testtest(int a);
};
