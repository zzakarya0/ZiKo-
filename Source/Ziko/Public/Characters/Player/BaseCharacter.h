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
	bool IsArmed() const { return Weapon != nullptr; }

	UFUNCTION(BlueprintPure)
	bool IsAttacking() const { return bIsAttacking; }

	void SetAttackState(const bool IsAttacking) { bIsAttacking = IsAttacking; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack() PURE_VIRTUAL(ABaseCharacter::BaseAttack, );

	const AMagicWand* const GetPrimaryWeapon() const { return Weapon; }
	
private:
	/*Handle character movement*/
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	/*Interact with closest actor in range*/
	void Interact();

	AActor* GetClosestActorInRange() const;

	/*Pick up actor*/
	void PickUp(AActor* const Item);
	
	/*Update character look direction*/
	void UpdateLookDir();
	
	/*Regenerate player power energy*/
	void RegenerateEnergy(const float DeltaTime);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* BaseAttackAnim;

	UPROPERTY(EditAnywhere, Category = "Animations")
	float BaseAttackWaitRate;
	
	FTimerHandle AttackTimer;
	
	/*Abilities Component*/
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float MaxEnergy;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Components")
	float EnergyRegenerateRate;
	
	float EnergyVal;

	uint8 bIsAttacking : 1;
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*Tag for the weapon attachment socket*/
	UPROPERTY(EditAnywhere, Category = "Tags")
	FName WeaponAttachmentSocketName;

	UPROPERTY(EditAnywhere, Category = "Tags")
	FName PickableItemTag;

	/*Primary weapon player is holding*/
	UPROPERTY()
	AMagicWand* Weapon;
	
	/*Controller for the player*/
	UPROPERTY()
	APlayerCharacterController* PCController;

	/*Set of interactable actors that the player triggered their overlap event*/
	UPROPERTY()
	TSet<AActor*> InteractableActorsInRange; 
	
	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;
};