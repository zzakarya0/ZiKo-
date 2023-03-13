// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractBox.h"


UInteractBox::UInteractBox()
{
	//Register overlap events
	OnComponentBeginOverlap.AddDynamic(this, &UInteractBox::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractBox::OnOverlapEnd);
}

void UInteractBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* Owner = GetOwner();
	
	if (Owner && OtherActor && OtherActor != Owner)
		UE_LOG(LogTemp, Warning, TEXT("OnOverlap --> Box Owner: %s"), *OtherActor->GetName());
}

void UInteractBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
}


