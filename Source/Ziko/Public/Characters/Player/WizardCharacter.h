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
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void UpdateLookDir();
	void RegenerateEnergy(const float DeltaTime);
	
private:
	UPROPERTY()
	APlayerController* PlayerController;

	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;

	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*Energy Components consumed by player abilities*/
	UPROPERTY(EditAnywhere, Category = "Energy Components")
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "Energy Components")
	float EnergyRegenerateRate;
	
	float EnergyVal;
};
