// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MagicWand.h"

#include "DrawDebugHelpers.h"
#include "Characters/Player/BaseCharacter.h"
#include "Components/InteractBox.h"

// Sets default values
AMagicWand::AMagicWand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MagicSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Magic Spawn Point"));
	MagicSpawnPoint->SetupAttachment(RootComponent);


	FreezingRange = 0;
	IceCrystalZPos = 0;
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

void AMagicWand::BaseAttack() const
{
	UWorld* const World = GetWorld();
	check(World);
	ABaseCharacter* const MyOwner = Cast<ABaseCharacter>(GetOwner());
	check(MyOwner);

	FVector const SpawnPoint = MagicSpawnPoint->GetComponentLocation();
	FRotator const SpawnRotation =	FRotator(0.f, MyOwner->GetActorRotation().Yaw, 0.f);

	check(BpMagicBullet);
	AActor* const MagicBullet = World->SpawnActor(BpMagicBullet, &SpawnPoint, &SpawnRotation);
	check(MagicBullet);
	
	MagicBullet->SetOwner(MyOwner);
	MyOwner->SetAttackState(EAttackType::AT_None);
}

void AMagicWand::FirstAbilityAttack() const
{
	UWorld* const World = GetWorld();
	check(World);
	ABaseCharacter* const MyOwner = Cast<ABaseCharacter>(GetOwner());
	check(MyOwner);

	FVector_NetQuantize SpawnPoint;
	const bool bWasHit = MyOwner->GetMouseLocation(SpawnPoint);
	if (!bWasHit) return;

	SpawnPoint.Set(SpawnPoint.X, SpawnPoint.Y, IceCrystalZPos);
	check(BpIceCrystal);
	AActor* const IceCrystal = World->SpawnActor(BpIceCrystal, &SpawnPoint);
	DrawDebugSphere(World, SpawnPoint, FreezingRange, 10, FColor::Red, true);
	check(IceCrystal);
	
	IceCrystal->SetOwner(MyOwner);
	MyOwner->SetAttackState(EAttackType::AT_None);
}

void AMagicWand::SecondAbilityAttack() const
{
	UWorld* const World = GetWorld();
	check(World);
	
	ABaseCharacter* const MyOwner = Cast<ABaseCharacter>(GetOwner());
	check(MyOwner);

	FVector const SpawnPoint = MagicSpawnPoint->GetComponentLocation();
	FRotator const SpawnRotation =	FRotator(0.f, MyOwner->GetActorRotation().Yaw, 0.f);
	AActor* const MagicBullet = World->SpawnActor(BpMagicBullet, &SpawnPoint, &SpawnRotation);
	check(MagicBullet);
	
	MagicBullet->SetOwner(MyOwner);
	MyOwner->SetAttackState(EAttackType::AT_None);
}

