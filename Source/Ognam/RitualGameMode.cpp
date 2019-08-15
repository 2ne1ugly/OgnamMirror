// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameMode.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"

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

AActor* ARitualGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	ARitualPlayerState* PlayerState = Player->GetPlayerState<ARitualPlayerState>();
	ARitualGameState* GameState = GetGameState< ARitualGameState>();
	if (PlayerState == nullptr || GameState == nullptr)
	{
		return nullptr;
	}
	FName Team = PlayerState->GetTeam();
	if (Team == GameState->GetCurrentOffenseTeam())
	{
		
	}
	else if (Team == GameState->GetCurrentDefenseTeam())
	{

	}
	return nullptr;
}
