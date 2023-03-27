#pragma once
#include "BaseCharacter.h"
#include "CoreMinimal.h"

UCLASS()
class ZIKO_API ABarbarianCharacter : public  ABaseCharacter
{
	GENERATED_BODY();
public:
	ABarbarianCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void BaseAttack() override;

	/*Perform character base attack*/
	virtual void FirstAbilityAttack() override;

	/*Perform character base attack*/
	virtual void SecondAbilityAttack() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
