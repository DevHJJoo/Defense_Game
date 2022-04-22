// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTower.generated.h"

class UMyAnimInstance;

UCLASS()
class TOWERDEFENSE_API AMyTower : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent*			m_Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent*		m_TowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USphereComponent*			m_DetectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int							m_iTowerLv;

	UPROPERTY(VisibleAnywhere)
	bool						m_bIsNeedToUpgrade;

	// 가장 가까이 인지한 몬스터의 방향을 가리키도록 한다.

	UPROPERTY(VisibleAnywhere)
	float						m_fDirection;

	UMyAnimInstance*			m_AnimInst;

	bool						m_bFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ETOWER_STATE				m_eState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FTowerInfo					m_Info;

protected:
	ETOWER_TYPE					m_eTowerType;

public:
	void SetUpgrade(bool _b) { m_bIsNeedToUpgrade = _b; }
	bool IsNeedToUpgrade() { return m_bIsNeedToUpgrade; }
	void SetDirection(float _f) { m_fDirection = _f; }
	float GetDirection() { return m_fDirection; }
	void SetFire(bool _b) { m_bFire = _b; }
	bool GetFire() { return m_bFire; }

	void SetTowerInfo(const FTowerInfo& _info) { m_Info = _info; }
	ETOWER_STATE GetState() { return m_eState; }
	void ChangeState(ETOWER_STATE _eNextState);

protected:
	const FTowerInfo& GetTowerInfo() { return m_Info; }
	USkeletalMeshComponent* GetMesh() { return m_TowerMesh; }
	USphereComponent* GetDetectSphere() { return m_DetectSphere; }
	int GetTowerLv() { return m_iTowerLv; }
	void SetTowerType(ETOWER_TYPE _TowerType) { m_eTowerType = _TowerType; }
	ETOWER_TYPE GetTowerType() { return m_eTowerType; }

	void SetDetectSphereSize(float _Size)
	{
		m_DetectSphere->SetSphereRadius(_Size);
	}

public:
	void SetTowerLv(int _Lv) { m_iTowerLv = _Lv; }
	
public:
	UMyAnimInstance* GetAnimInst() { return m_AnimInst; }

public:
	// Sets default values for this pawn's properties
	AMyTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Notify
public:
	virtual void Fire() {}
	virtual void DestroyProcess() {}
	
	// Anim Montage play
protected:
	virtual void Install() {}
	virtual void Idle() {}
	virtual void Attack() {}
	virtual void NeedUpgrade() {}
	virtual void Upgrade() {}
	virtual void RemoveWithUpgarde() {}
	virtual void Remove() {}
};
