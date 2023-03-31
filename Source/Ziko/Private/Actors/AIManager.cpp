// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AIManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);

	check(AIBehavior);
	RunBehaviorTree(AIBehavior);
	
	BlackBoardComp = GetBlackboardComponent();
	BlackBoardComp->SetValueAsVector(PlayerPosKey, PlayerPawn->GetActorLocation());
}
