// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/BaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "NetworkMessage.h"
#include "Actors/MagicWand.h"
#include "Actors/PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "DrawDebugHelpers.h"

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

	AttackType = EAttackType::AT_None;

	Weapon = nullptr;
	PCController = nullptr;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnergyVal = MaxEnergy;
	
	PCController = Cast<APlayerCharacterController>(GetController());
	check(PCController);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 1000), FColor::Red, true);
	// UE_LOG(LogTemp, Warning, TEXT("BEFORE FUNCTION CALL: Rotation = %s"), *GetActorRotation().ToCompactString());
	// UE_LOG(LogTemp, Warning, TEXT("BEFORE FUNCTION CALL: FOrward Vector = %s"), *GetActorForwardVector().ToCompactString());
	
	UpdateLookDir();
	RegenerateEnergy(DeltaTime); //FIXME: Don't regenerate in Tick, use Timer maybe

	// UE_LOG(LogTemp, Warning, TEXT("AFTER FUNCTION CALL: Rotation = %s"), *GetActorRotation().ToCompactString());
	// UE_LOG(LogTemp, Warning, TEXT("AFTER FUNCTION CALL: FOrward Vector = %s"), *GetActorForwardVector().ToCompactString());
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("BaseAttack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::BaseAttack);
	PlayerInputComponent->BindAction(TEXT("Ability1"), EInputEvent::IE_Pressed, this, &ABaseCharacter::FirstAbilityAttack);
	PlayerInputComponent->BindAction(TEXT("Ability2"), EInputEvent::IE_Pressed, this, &ABaseCharacter::SecondAbilityAttack);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Interact);
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
	if (!PCController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit)) return;
	//DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5.f, 10.f, FColor::Red, true);
	const FVector player_fwd = GetActorLocation() + GetActorForwardVector();
	
	FRotator newRot = ( OutHit.Location- player_fwd ).Rotation();
	AddActorLocalRotation(FRotator(0.0f,newRot.Yaw,0.0f));
	/*
	const FRotator InitialRotation = GetActorRotation();
	const FVector Forward =	GetActorForwardVector().GetSafeNormal();
	FVector CharacterToMouse = OutHit.ImpactPoint - GetActorLocation();
	CharacterToMouse = CharacterToMouse.GetSafeNormal();
	
	//Get angle between player forward and mouse position
	const float CosAngle = FVector::DotProduct(Forward, CharacterToMouse) / (Forward.Size() * CharacterToMouse.Size());
	float Angle = FMath::Acos(CosAngle);
	Angle = FMath::RadiansToDegrees(FMath::Abs(Angle - InitialRotation.Yaw));

	//Check if mouse position is in right/left of player
	const float CosDirAngle = FVector::DotProduct(GetActorRightVector(), CharacterToMouse) / (GetActorForwardVector().Size() * CharacterToMouse.Size());
	float LookDir = FMath::Acos(CosDirAngle);
	LookDir = FMath::RadiansToDegrees(LookDir);
	LookDir = LookDir < 90.f? Angle : - Angle; //FIXME: Weird rotation when mouse transition from left to right or inverse
	
	AddActorLocalRotation(FRotator(0.f, LookDir, 0.f));
	//UE_LOG(LogTemp, Warning, TEXT("Within UpdateLookDir: Rotation = %s"), *GetActorRotation().ToCompactString());
	OutHit.Reset();
	*/
	
}

void ABaseCharacter::AddInteractableActorInRange(AActor* Item)
{
	InteractableActorsInRange.Add(Item);
}

void ABaseCharacter::RemoveInteractableActorInRange(AActor* Item)
{
	InteractableActorsInRange.Remove(Item);
}

void ABaseCharacter::Interact()
{
	if (InteractableActorsInRange.Num() == 0) return;	//FIXME: Couldn't find TArray::IsEmpty()??

	AActor* const Item = GetClosestActorInRange();	//FIXME: Get closest item based on distance and player look direction
	check(Item);
	
	if (Item->ActorHasTag(PickableItemTag) && !Weapon) Equip(Item);
	// if (Item->ActorHasTag(PickableItemTag) && MagicWand) add to inventory;

	InteractableActorsInRange.Remove(Item);
}

AActor* ABaseCharacter::GetClosestActorInRange() const
{
	const FVector PlayerFwd = GetActorForwardVector();
	AActor* ClosestActor = nullptr;
	float AngleInRad = 3.14f;	// initialize with ~180 deg
	
	for (AActor* const Item : InteractableActorsInRange)
	{
		const FVector PlayerToItem = Item->GetActorLocation() - GetActorLocation();
		const float CosAngle = FVector::DotProduct(PlayerFwd, PlayerToItem) / (PlayerFwd.Size() * PlayerToItem.Size());
		const float Angle = FMath::Acos(CosAngle);
		
		if (Angle <= AngleInRad)
		{
			AngleInRad = Angle;
			ClosestActor = Item;
		}
	}
	
	check(ClosestActor);
	return ClosestActor;
}

void ABaseCharacter::Equip(AActor* const Item)
{
	check(Item);
	Item->SetActorLocation(FVector(0.f));
	Item->AttachToComponent(GetMesh() ,FAttachmentTransformRules::KeepRelativeTransform, WeaponAttachmentSocketName);
	Item->SetOwner(this);
	Weapon = Cast<AMagicWand>(Item);	/*FIXME: Extend pickup functionality for weapons/items, weapons: overload_1 to
										  pickup and equip, items/potions/other: overload_2 add to inventory.
										  Or add boolean arg bIsWeapon*/
	check(Weapon);
	Weapon->SetOverlapEvents(false);
}

void ABaseCharacter::RegenerateEnergy(const float DeltaTime)
{
	EnergyVal = FMath::Clamp(EnergyVal + (EnergyRegenerateRate * DeltaTime), 0.f, MaxEnergy);
}