// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/WizardCharacter.h"

#include "Actors/MagicWand.h"


// Sets default values
AWizardCharacter::AWizardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWizardCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWizardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWizardCharacter::BaseAttack()
{
	if (bIsAttacking) return;
	
	const AMagicWand* const MagicWand = GetPrimaryWeapon();
	if (!MagicWand) return;

	const int8 AttackEnergyCost = MagicWand->GetBaseAttackCost();
	if (EnergyVal < AttackEnergyCost) return;
	
	//GetMesh()->PlayAnimation(BaseAttackAnim, false);
	bIsAttacking = 1;
	GetWorldTimerManager().SetTimer(AttackTimer, MagicWand, &AMagicWand::BaseAttack, BaseAttackWaitRate, false);
	
	EnergyVal -= AttackEnergyCost;
	//bIsAttacking = false;
}
