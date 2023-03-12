// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring"));
	CameraSpringComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(CameraSpringComp);

	CameraSpringComp->TargetArmLength = 750.f;
	CameraSpringComp->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

	MaxEnergy = -1.f;
	EnergyRegenerateRate = -1.f;
	EnergyVal = -1.f;

	PlayerController = nullptr;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnergyVal = MaxEnergy;

	PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLookDir();
	RegenerateEnergy(DeltaTime); //FIXME: Don't regenerate in Tick, use Timer maybe
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("BaseAttack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::BaseAttack);
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ABaseCharacter::UpdateLookDir()
{
	if (!PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit)) return;
	//DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.f, 10.f, FColor::Red, true);

	const FVector Forward = GetActorForwardVector();
	const FVector CharacterToMouse = OutHit.ImpactPoint - GetActorLocation();
	
	//Get angle between player forward and mouse position
	const float CosAngle = FVector::DotProduct(Forward, CharacterToMouse) / (Forward.Size() * CharacterToMouse.Size());
	float Angle = FMath::Acos(CosAngle);
	Angle = FMath::RadiansToDegrees(Angle);

	//Check if mouse position is in right/left of player
	const float CosDirAngle = FVector::DotProduct(GetActorRightVector(), CharacterToMouse) / (GetActorForwardVector().Size() * CharacterToMouse.Size());
	float LookDir = FMath::Acos(CosDirAngle);
	LookDir = FMath::RadiansToDegrees(LookDir);
	LookDir = LookDir < 90.f? Angle : 360.f - Angle; //FIXME: Weird rotation when mouse transition from left to right or inverse
	
	SetActorRotation(FRotator(0.f, LookDir, 0.f));
	OutHit.Reset();
}

void ABaseCharacter::RegenerateEnergy(const float DeltaTime)
{
	EnergyVal = FMath::Clamp(EnergyVal + (EnergyRegenerateRate * DeltaTime), 0.f, MaxEnergy);
	//UE_LOG(LogTemp, Warning, TEXT("Energy is: %f"), EnergyVal);
}

