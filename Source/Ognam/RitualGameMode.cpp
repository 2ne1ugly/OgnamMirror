// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameMode.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

ARitualGameMode::ARitualGameMode()
{
	GameStateClass = ARitualGameState::StaticClass();
	PlayerStateClass = ARitualPlayerState::StaticClass();
	PlayerControllerClass = ARitualPlayerController::StaticClass();
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
	// if everyone's in and everyone is ready
	if (NumPlayers == MaxNumPlayers)
	{
		for (ARitualPlayerController* PlayerController : PlayerControllers)
		{
			if (!PlayerController->GetIsReady())
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void ARitualGameMode::HandleMatchHasStarted()
{
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		RestartPlayer(PlayerController);
	}
}

void ARitualGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ARitualPlayerController *PlayerController = Cast<ARitualPlayerController>(NewPlayer);
	ARitualGameState* GameState = GetGameState<ARitualGameState>();
	ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	//Assign Team
	if (RitualPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Some one is not a Ritual Player State!"));
	}
	else
	{
		if (GameState->GreenPlayers.Num() < GameState->BluePlayers.Num())
		{
			RitualPlayerState->SetTeam(GameState->GreenName);
			RitualPlayerState->SetTeamIndex(GameState->GreenPlayers.Num());
			PlayerController->SetTeam(GameState->GreenName);
			PlayerController->SetTeamIndex(GameState->GreenPlayers.Num());
			PlayerController->GetReady(GameState->GreenPlayers.Num(), GameState->GreenName);
			GameState->GreenPlayers.Push(RitualPlayerState);
		}
		else
		{
			RitualPlayerState->SetTeam(GameState->BlueName);
			RitualPlayerState->SetTeamIndex(GameState->BluePlayers.Num());
			PlayerController->SetTeam(GameState->BlueName);
			PlayerController->SetTeamIndex(GameState->BluePlayers.Num());
			PlayerController->GetReady(GameState->BluePlayers.Num(), GameState->BlueName);
			GameState->BluePlayers.Push(RitualPlayerState);
		}
		PlayerControllers.Push(PlayerController);
	}
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
	ARitualPlayerController* PlayerController = Cast<ARitualPlayerController>(Player);
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState or ARitualPlayerController invalid"));
		return nullptr;
	}

	//find right n'th index
	FName Side = PlayerController->GetSide();
	int32 GivenIndex = PlayerController->GetTeamIndex();
	int32 CurrentIndex = 0;
	for (TActorIterator<APlayerStart> itr(GetWorld()); itr; ++itr)
	{
		if (itr->PlayerStartTag.IsEqual(Side))
		{
			if (CurrentIndex == GivenIndex)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *itr->PlayerStartTag.ToString());
				return *itr;
			}
			CurrentIndex++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Not enough Spawn points"));
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}
