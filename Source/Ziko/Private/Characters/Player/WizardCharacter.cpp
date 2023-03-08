// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/WizardCharacter.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AWizardCharacter::AWizardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraSpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring"));
	CameraSpringComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(CameraSpringComp);

	CameraSpringComp->TargetArmLength = 750.f;
	CameraSpringComp->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AWizardCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);
}

// Called every frame
void AWizardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	if (!PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit)) return;
	//DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.f, 10.f, FColor::Red, true);

	const FVector Forward = GetActorForwardVector();
	const FVector CharacterToMousePos = OutHit.ImpactPoint - GetActorLocation();
	
	//Get angle between player forward and mouse position
	const float CosAngle = FVector::DotProduct(Forward, CharacterToMousePos) / (Forward.Size() * CharacterToMousePos.Size());
	float Angle = FMath::Acos(CosAngle);
	Angle = FMath::RadiansToDegrees(Angle);

	//Check if mouse position is in right/left of player
	const float CosDirAngle = FVector::DotProduct(GetActorRightVector(), CharacterToMousePos) / (GetActorForwardVector().Size() * CharacterToMousePos.Size());
	float LookDir = FMath::Acos(CosDirAngle);
	LookDir = FMath::RadiansToDegrees(LookDir);
	LookDir = LookDir < 90.f? Angle : 360.f - Angle; //FIX ME: Weird rotation when mouse transitions from left to right or inverse
	
	SetActorRotation(FRotator(0.f, LookDir, 0.f));
}

// Called to bind functionality to input
void AWizardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWizardCharacter::MoveForward);
}

void AWizardCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}