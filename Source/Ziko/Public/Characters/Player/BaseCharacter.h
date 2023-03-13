// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AMagicWand;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ZIKO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Pick up actors*/
	void PickUp(AActor* const Item);

	UFUNCTION(BlueprintPure)
	bool IsArmed() const { return MagicWand != nullptr; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack() PURE_VIRTUAL(ABaseCharacter::BaseAttack, );
	
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
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float BaseAttackCost;
	
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Components")
	float EnergyRegenerateRate;
	
	float EnergyVal;
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	UPROPERTY()
	AMagicWand* MagicWand;
	
	UPROPERTY(EditAnywhere)
	FName WeaponAttachmentSocketName;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;
};