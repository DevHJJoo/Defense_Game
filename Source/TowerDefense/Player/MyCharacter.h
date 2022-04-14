// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API AMyCharacter 
	: public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent*		m_Cam;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent*	m_Arm;

public:
	// Sets default values for this character's properties
	AMyCharacter();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveFront(float _fScale);
	void MoveSide(float _fScale);
	void Zoom(float _fScale);

};
