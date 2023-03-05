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

public:	
	
private:
	UPROPERTY()
	APlayerController* PlayerController;
	
	// Camera Components	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;
};
