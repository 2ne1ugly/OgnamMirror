// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameMode.h"
#include "OgnamShooter.h"
#include "OgnamPlayerController.h"
#include "OgnamPlayerState.h"
#include "OgnamGameState.h"

AOgnamGameMode::AOgnamGameMode()
{
	DefaultPawnClass = AOgnamShooter::StaticClass();
	PlayerControllerClass = AOgnamPlayerController::StaticClass();
	GameStateClass = AOgnamGameState::StaticClass();
	PlayerStateClass = AOgnamPlayerState::StaticClass();
}

bool AOgnamGameMode::ReadyToStartMatch_Implementation()
{
	Super::ReadyToStartMatch_Implementation();
	return true;
}

void AOgnamGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerControllers.Add(NewPlayer);
}

void AOgnamGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
}
