// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <Components/DecalComponent.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API AMyCharacter 
	: public ACharacter
{
	GENERATED_BODY()

private:
	USkeletalMesh* m_SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent*		m_Cam;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent*	m_Arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerController*		m_PlayerCtrl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float					m_CameraMargin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32					m_ScreenSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32					m_ScreenSizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float					m_CamSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FPlayerInfo				m_Info;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	FVector	GetCameraFanDirection();

	UFUNCTION()
	void PanMoveCamera(const FVector& PanDirection);

protected:
	void SetSkeletalMesh(USkeletalMesh* _mesh) { m_SkeletalMesh = _mesh; }

public:
	void MoveFront(float _fScale);
	void MoveSide(float _fScale);
	void Zoom(float _fScale);
	APlayerController* GetPlayerController() { return m_PlayerCtrl; }

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);
};
