#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
	: m_CameraMargin(10.f)
	, m_CamSpeed(5.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링 암 생성, 계층 구조 설정, 충돌 비활성화, 기본 길이 설정
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Arm->SetupAttachment(GetMesh());
	m_Arm->bDoCollisionTest = false;
	m_Arm->TargetArmLength = 1200.f;
	m_Arm->SetRelativeRotation(FRotator(-50, 0, 0));

	// 카메라 생성 및 계층 구조 설정
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Cam->SetupAttachment(m_Arm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_PlayerCtrl = Cast<APlayerController>(GetController());
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(0 == m_ScreenSizeX || 0 == m_ScreenSizeY)
		m_PlayerCtrl->GetViewportSize(m_ScreenSizeX, m_ScreenSizeY);

	PanMoveCamera(GetCameraFanDirection());
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &AMyCharacter::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AMyCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AMyCharacter::Zoom);
}

FVector	AMyCharacter::GetCameraFanDirection()
{
	if(nullptr == m_PlayerCtrl)
		m_PlayerCtrl = Cast<APlayerController>(GetController());

	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	float MarginX = m_ScreenSizeX * (m_CameraMargin / 100.f);
	float MarginY = m_ScreenSizeY * (m_CameraMargin / 100.f);
	UE_LOG(LogTemp, Warning, TEXT("Screen : (%u, %u)"), m_ScreenSizeX, m_ScreenSizeY)
	m_PlayerCtrl->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX <= MarginX)
	{
		CamDirectionX = -1;
	}

	if (MousePosY <= MarginY)
	{
		CamDirectionY = -1;
	}

	if (MousePosX >= m_ScreenSizeX - MarginX)
	{
		CamDirectionX = 1;
	}

	if (MousePosY >= m_ScreenSizeY - MarginY)
	{
		CamDirectionY = 1;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}

void AMyCharacter::PanMoveCamera(const FVector& _vPanDirection)
{
	if (FVector::ZeroVector == _vPanDirection)
	{
		return;
	}
	else
	{
		Vec3 Location = GetActorLocation();
		Location += GetCameraFanDirection() * m_CamSpeed;
		//SetActorLocation(Location, true);

		AddMovementInput(GetCameraFanDirection(), m_CamSpeed);
	}
}

void AMyCharacter::MoveFront(float _fScale)
{	
	Vec3 Location = GetActorLocation();
	Location += GetActorForwardVector() * 5.f * _fScale;
	//SetActorLocation(Location, true);

	AddMovementInput(GetActorForwardVector(), 5.f * _fScale);
}

void AMyCharacter::MoveSide(float _fScale)
{
	Vec3 Location = GetActorLocation();
	Location += GetActorRightVector() * 5.f * _fScale;
	//SetActorLocation(Location, true);

	AddMovementInput(GetActorRightVector(), 5.f * _fScale);
}

#define MIN_ARM_LENGTH 600.f
#define MAX_ARM_LENGTH 1200.f
void AMyCharacter::Zoom(float _fScale)
{
	float fDT = GetWorld()->GetDeltaSeconds();
	m_Arm->TargetArmLength += _fScale * 40.f;

	if (m_Arm->TargetArmLength > MAX_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MAX_ARM_LENGTH;
	}
	else if (m_Arm->TargetArmLength < MIN_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MIN_ARM_LENGTH;
	}	
}

void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	LOG(Warning, TEXT("Overlap Character"))
}

void AMyCharacter::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	LOG(Warning, TEXT("Hit Character"))
}