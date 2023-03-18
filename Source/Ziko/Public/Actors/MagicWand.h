// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractBox.h"
#include "GameFramework/Actor.h"
#include "MagicWand.generated.h"

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
	
	/*Send base attack energy cost to player*/
	int8 GetBaseAttackCost() const { return BaseAttackCost; }

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

	/*Damage dealt by base attack*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	int8 BaseAttackDamage;

	/*Default actor to spawn when performing any attack*/
	UPROPERTY(EditDefaultsOnly, Category = "Ability Attributes")
	TSubclassOf<AActor> BpMagicBullet;
};
