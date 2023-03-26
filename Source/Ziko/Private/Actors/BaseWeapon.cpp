// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"

#include "Components/InteractBox.h"
#include "Ziko.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractBox = CreateDefaultSubobject<UInteractBox>(TEXT("Interact Box"));
	SetRootComponent(InteractBox);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseAttackCost = 0;
	FirstAbilityAttackCost = 0;
	SecondAbilityAttackCost = 0;

	BaseAttackDamage = 0;
	FirstAbilityAttackDamage = 0;
	SecondAbilityAttackDamage = 0;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::SetOverlapEvents(const bool GenerateOverlapEvents) const
{
	check(InteractBox);
	InteractBox->SetGenerateOverlapEvents(GenerateOverlapEvents);
}

uint8 ABaseWeapon::GetAttackCost(const EAttackType AttackType) const
{
	switch (AttackType)
	{
		case EAttackType::AT_Basic: return BaseAttackCost;
		case EAttackType::AT_Ability1: return FirstAbilityAttackCost;
		case EAttackType::AT_Ability2: return SecondAbilityAttackCost;
		default: check(nullptr); return 0; // shouldn't reach this point
	}
}

uint8 ABaseWeapon::GetAttackDamage(const EAttackType AttackType) const
{
	switch (AttackType)
	{
		case EAttackType::AT_Basic: return BaseAttackDamage;
		case EAttackType::AT_Ability1: return FirstAbilityAttackDamage;
		case EAttackType::AT_Ability2: return SecondAbilityAttackDamage;
		default: check(nullptr); return 0; // shouldn't reach this point
	}
}

