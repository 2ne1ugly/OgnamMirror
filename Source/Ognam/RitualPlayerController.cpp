// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerController.h"
#include "RitualGameState.h"
#include "Engine/World.h"

void ARitualPlayerController::Die()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call"));
		return;
	}
	Super::Die();
	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Ritual GameState"));
		return;
	}
	GameState->KillPlayer(this);
}
