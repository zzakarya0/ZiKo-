// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MagicWand.h"

#include "Components/InteractBox.h"

// Sets default values
AMagicWand::AMagicWand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractBox = CreateDefaultSubobject<UInteractBox>(TEXT("Interact Box"));
	SetRootComponent(InteractBox);
	
	Wand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wand"));
	Wand->SetupAttachment(RootComponent);

	MagicSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Magic Spawn Point"));
	MagicSpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMagicWand::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void AMagicWand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicWand::BaseAttack()
{
	
}

