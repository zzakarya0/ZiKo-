// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

enum class EAttackType : uint8;
class UInteractBox;

UCLASS()
class ZIKO_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Enable/Disable overlap events for interact box*/
	void SetOverlapEvents(const bool GenerateOverlapEvents) const;
	
	virtual void BaseAttack() const PURE_VIRTUAL(ABaseWeapon::BaseAttack, );
	virtual void FirstAbilityAttack() const PURE_VIRTUAL(ABaseWeapon::FirstAbilityAttack, );
	virtual void SecondAbilityAttack() const PURE_VIRTUAL(ABaseWeapon::SecondAbilityAttack, );
	
	/*Send attack energy cost to player*/
	uint8 GetAttackCost(const EAttackType AttackType) const;

protected:
	/*Send attack damage to damaged actors*/
	uint8 GetAttackDamage(const EAttackType AttackType) const;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;
	
	/*Interaction box that generates overlap events*/
	UPROPERTY(EditDefaultsOnly)
	UInteractBox* InteractBox;

	/*Energy cost of  attacks*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 BaseAttackCost;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 FirstAbilityAttackCost;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 SecondAbilityAttackCost;

	/*Damage dealt by attacks*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 BaseAttackDamage;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 FirstAbilityAttackDamage;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 SecondAbilityAttackDamage;
};
