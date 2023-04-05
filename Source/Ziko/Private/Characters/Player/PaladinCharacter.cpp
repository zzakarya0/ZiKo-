#include "Characters/Player/PaladinCharacter.h"

APaladinCharacter::APaladinCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APaladinCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APaladinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APaladinCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APaladinCharacter::BaseAttack()
{
	
}

void APaladinCharacter::FirstAbilityAttack()
{
	
}

void APaladinCharacter::SecondAbilityAttack()
{
	
}






