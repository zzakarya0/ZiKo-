// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AMagicWand;
class APlayerCharacterController;
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

	void AddInteractableActorInRange(AActor* Item);

	void RemoveInteractableActorInRange(AActor* Item);

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

	/*Interact with closest actor in range*/
	void Interact();

	/*Pick up actor*/
	void PickUp(AActor* const Item);
	
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

	/*Tag for the weapon attachment socket*/
	UPROPERTY(EditAnywhere, Category = "Tags")
	FName WeaponAttachmentSocketName;

	UPROPERTY(EditAnywhere, Category = "Tags")
	FName PickableItemTag;
	
	/*Controller for the player*/
	UPROPERTY()
	APlayerCharacterController* PCController;

	/*Array of interactable actors that the player triggered their overlap event*/
	UPROPERTY()
	TArray<AActor*> InteractableActorsInRange;
	
	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;
};