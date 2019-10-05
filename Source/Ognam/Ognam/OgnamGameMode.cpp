// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameMode.h"
#include "OgnamPlayerController.h"
#include "OgnamPlayerState.h"
#include "OgnamGameState.h"

AOgnamGameMode::AOgnamGameMode()
{
	PlayerControllerClass = AOgnamPlayerController::StaticClass();
	GameStateClass = AOgnamGameState::StaticClass();
	PlayerStateClass = AOgnamPlayerState::StaticClass();
}

void AOgnamGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}
	//0 means Infinite
	MaxNumPlayers = 0;
}

void AOgnamGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}
	if (MaxNumPlayers && NumPlayers >= MaxNumPlayers)
	{
		ErrorMessage = "Match Full";
		return;
	}
}
