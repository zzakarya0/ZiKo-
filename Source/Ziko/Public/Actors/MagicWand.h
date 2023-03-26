// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractBox.h"
#include "GameFramework/Actor.h"
#include "MagicWand.generated.h"

enum class EAttackType : uint8;
class UInteractBox;

UCLASS()
class ZIKO_API AMagicWand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicWand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Enable/Disable overlap events for interact box*/
	void SetOverlapEvents(const bool GenerateOverlapEvents) const { InteractBox->SetGenerateOverlapEvents(GenerateOverlapEvents); }

	/*Perform Wand Base Attack*/
	void BaseAttack() const;

	void FirstAbilityAttack() const;

	void SecondAbilityAttack() const;
	
	/*Send attack energy cost to player*/
	int8 GetAttackCost(const EAttackType AttackType) const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Wand;
	
	/*Interaction box that generates overlap events*/
	UPROPERTY(EditDefaultsOnly)
	UInteractBox* InteractBox;

	/*Spawn point for magic to attack*/
	UPROPERTY(EditAnywhere)
	USceneComponent* MagicSpawnPoint;

	/*Energy cost of base attack*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	int8 BaseAttackCost;

	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	int8 FirstAbilityAttackCost;

	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	int8 SecondAbilityAttackCost;

	/*Damage dealt by base attack*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	int8 BaseAttackDamage;

	/*Default actor to spawn when performing any attack*/
	UPROPERTY(EditDefaultsOnly, Category = "Ability Attributes")
	TSubclassOf<AActor> BpMagicBullet;
};
