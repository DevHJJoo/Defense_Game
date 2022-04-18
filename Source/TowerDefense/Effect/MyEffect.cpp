// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Particle =  CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");
	SetRootComponent(m_Particle);
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();

	UParticleSystem* ParticleAsset = nullptr;

	switch (m_eType)
	{
	case EEFFECT_TYPE::MUZZLEFLASH:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(),
			TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_Ems_MuzzleFlash_01.P_Ems_MuzzleFlash_01'"));
		break;
	case EEFFECT_TYPE::EXPLOSION:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(),
			TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_Ems_Explosion_02.P_Ems_Explosion_02'"));
		break;
	case EEFFECT_TYPE::TRAIL:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(),
			TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_SmokeTrail_01.P_SmokeTrail_01'"));
		break;
	case EEFFECT_TYPE::SMOKE:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(),
		TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_Smoke_01.P_Smoke_01'"));
		break;
	case EEFFECT_TYPE::HIT:
		ParticleAsset = LoadObject<UParticleSystem>(GetWorld(),
			TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_Hit_02.P_Hit_02'"));
		break;
	case EEFFECT_TYPE::ZONE:
		break;
	}

	if (nullptr != ParticleAsset)
	{
		m_Particle->SetTemplate(ParticleAsset);
		m_Particle->OnSystemFinished.AddDynamic(this, &AMyEffect::OnFinish);
	}	
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyEffect::OnFinish(UParticleSystemComponent* _Particle)
{
	Destroy();
}

