#include "Characters/Player/BarbarianCharacter.h"

ABarbarianCharacter::ABarbarianCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABarbarianCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABarbarianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABarbarianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABarbarianCharacter::BaseAttack()
{
	
}




