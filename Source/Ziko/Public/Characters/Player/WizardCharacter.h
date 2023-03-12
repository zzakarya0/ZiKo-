// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WizardCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ZIKO_API AWizardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizardCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	/*Handle character movement*/
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	/*Update character look direction*/
	void UpdateLookDir();
	
	/*Regenerate player power energy*/
	void RegenerateEnergy(const float DeltaTime);
	
	/*Perform character base attack*/
	void BaseAttack();
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*Abilities Component*/
	UPROPERTY(EditAnywhere, Category = "Ability Component")
	float BaseAttackCost;
	
	UPROPERTY(EditAnywhere, Category = "Ability Component")
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Component")
	float EnergyRegenerateRate;
	
	float EnergyVal;

	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;

	UPROPERTY()
	APlayerController* PlayerController;
};
