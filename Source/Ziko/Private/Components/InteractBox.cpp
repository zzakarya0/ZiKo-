// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractBox.h"

#include "Characters/Player/BaseCharacter.h"
#include "GameFramework/Character.h"


UInteractBox::UInteractBox()
{
	// Register overlap events
	OnComponentBeginOverlap.AddDynamic(this, &UInteractBox::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractBox::OnOverlapEnd);
}

void UInteractBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Overlap Event Genereated"));
	
	// Owner is the actor this box is attached to.
	AActor* const Owner = GetOwner();
	
	if (Owner && OtherActor && OtherActor != Owner)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);
		if (!Character) return;

		Character->PickUp(Owner);
	}
}

void UInteractBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}


