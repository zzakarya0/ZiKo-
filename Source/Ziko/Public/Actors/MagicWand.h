// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void BaseAttack();

private:
	UPROPERTY(EditDefaultsOnly)
	UInteractBox* InteractBox;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Wand;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* MagicSpawnPoint;
};
