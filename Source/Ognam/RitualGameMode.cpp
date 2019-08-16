// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameMode.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

ARitualGameMode::ARitualGameMode()
{
	GameStateClass = ARitualGameState::StaticClass();
	PlayerStateClass = ARitualPlayerState::StaticClass();
}

// This is where you init game based on options and Maps
void ARitualGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}
	MaxNumPlayers = 2;
}

bool ARitualGameMode::ReadyToStartMatch_Implementation()
{
	if (NumPlayers == MaxNumPlayers)
	{
		return true;
	}
	return false;
}

void ARitualGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ARitualGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}
}

AActor* ARitualGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	//get states
	ARitualPlayerState* PlayerState = Player->GetPlayerState<ARitualPlayerState>();
	ARitualGameState* GameState = GetGameState< ARitualGameState>();
	if (PlayerState == nullptr || GameState == nullptr)
	{
		return Super::FindPlayerStart_Implementation(Player, IncomingName);
	}

	//iterate through player state and find its own
	FName Team = PlayerState->GetTeam();
	int32 GivenIndex = PlayerState->GetTeamIndex();
	int32 CurrentIndex = 0;
	for (TActorIterator<APlayerStart> itr(GetWorld()); itr; ++itr)
	{
		if (itr->PlayerStartTag.IsEqual(Team))
		{
			if (CurrentIndex == GivenIndex)
				return *itr;
			CurrentIndex++;
		}
	}
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}
