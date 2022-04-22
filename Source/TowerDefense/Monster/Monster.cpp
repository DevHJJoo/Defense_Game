#include "Monster.h"

#include "AI/MonAIController.h"
// Sets default values
AMonster::AMonster()
	: m_eState(EMON_STATE::IDLE)
	, m_NextPatrolIdx(-1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��� �� AIController Ŭ���� ����
	AIControllerClass = AMonAIController::StaticClass();

	// AIController ���� ��� ����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// �浹 �������� ����
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyType"));
	
	m_Info = {};
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnBeginOverlap);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_PrevHP != m_Info.fCurHP)
	{

	}

	m_PrevHP = m_Info.fCurHP;
}

void AMonster::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{

}
