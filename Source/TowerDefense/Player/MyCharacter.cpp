#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라, 스프링 암 생성
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	// 카메라, 스프링 암 계층구조 설정
	m_Arm->SetupAttachment(GetMesh());
	m_Cam->SetupAttachment(m_Arm);

	m_Arm->TargetArmLength = 900.f;
	m_Arm->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &AMyCharacter::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AMyCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AMyCharacter::Zoom);
}

void AMyCharacter::MoveFront(float _fScale)
{
	AddMovementInput(GetActorForwardVector(), _fScale);
}

void AMyCharacter::MoveSide(float _fScale)
{
	AddMovementInput(GetActorRightVector(), _fScale);
}

#define MIN_ARM_LENGTH 700.f
#define MAX_ARM_LENGTH 900.f
void AMyCharacter::Zoom(float _fScale)
{
	float fDT = GetWorld()->GetDeltaSeconds();
	m_Arm->TargetArmLength += _fScale * 20.f;

	if (m_Arm->TargetArmLength > MAX_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MAX_ARM_LENGTH;
	}
	else if (m_Arm->TargetArmLength < MIN_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MIN_ARM_LENGTH;
	}	
}
