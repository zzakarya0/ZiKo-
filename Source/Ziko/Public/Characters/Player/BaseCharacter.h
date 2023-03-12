// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ZIKO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack() PURE_VIRTUAL(ABaseCharacter::BaseAttack, );

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

protected:
	/*Abilities Component*/
	UPROPERTY(EditAnywhere, Category = "Ability Component")
	float BaseAttackCost;
	
	UPROPERTY(EditAnywhere, Category = "Ability Component")
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Component")
	float EnergyRegenerateRate;
	
	float EnergyVal;
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;

	UPROPERTY()
	APlayerController* PlayerController;
};
