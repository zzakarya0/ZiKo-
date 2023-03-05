// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/WizardCharacter.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


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
	check(Controller);
}

// Called every frame
void AWizardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit))
	{
		//UE_LOG(LogTemp, Display, TEXT("Mouse Pos: %f, %f"));
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.f, 10.f, FColor::Red, true);
	}
}

// Called to bind functionality to input
void AWizardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AWizardCharacter::MoveForward);
}

void AWizardCharacter::MoveForward(float AxisValue)
{
	//UE_LOG(LogTemp, Display, TEXT("Received X value: %f"), AxisValue);
}