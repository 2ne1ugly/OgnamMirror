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
	// Num Players contains non initialized players.
	// use Num to make it safe
	if (PlayerControllers.Num() == MaxNumPlayers)
	{
		return true;
	}
	return false;
}

void ARitualGameMode::HandleMatchHasStarted()
{
	ARitualGameState* GameState = GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not a Ritual Gamestate"));
		return;
	}
	GameState->StartRound();
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
		if (GameState->GetNumGreenPlayers() <= GameState->GetNumBluePlayers())
		{
			RitualPlayerState->SetTeam(GameState->GreenName);
			RitualPlayerState->SetTeamIndex(GameState->GetNumGreenPlayers());
			GameState->IncNumGreenPlayers();
		}
		else
		{
			RitualPlayerState->SetTeam(GameState->BlueName);
			RitualPlayerState->SetTeamIndex(GameState->GetNumBluePlayers());
			GameState->IncNumBluePlayers();
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
	if (NumPlayers == MaxNumPlayers)
	{
		ErrorMessage = TEXT("Match Full");
	}
}

AActor* ARitualGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (!HasMatchStarted())
		return Super::FindPlayerStart_Implementation(Player, IncomingName);
	//get states
	ARitualPlayerState* PlayerState = Player->GetPlayerState<ARitualPlayerState>();
	if (PlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState or ARitualPlayerController invalid"));
		return nullptr;
	}

	//find right n'th index
	FName Side = PlayerState->GetSide();
	int32 GivenIndex = PlayerState->GetTeamIndex();
	int32 CurrentIndex = 0;
	for (TActorIterator<APlayerStart> itr(GetWorld()); itr; ++itr)
	{
		if (itr->PlayerStartTag.IsEqual(Side))
		{
			if (CurrentIndex == GivenIndex)
			{
				return *itr;
			}
			CurrentIndex++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Not enough Spawn points"));
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

void ARitualGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	if (NewPlayer == nullptr || NewPlayer->IsPendingKillPending())
	{
		return;
	}
	if (!StartSpot)
	{
		UE_LOG(LogGameMode, Warning, TEXT("RestartPlayerAtPlayerStart: Player start not found"));
		return;
	}

	FRotator SpawnRotation = StartSpot->GetActorRotation();

	UE_LOG(LogGameMode, Verbose, TEXT("RestartPlayerAtPlayerStart %s"), (NewPlayer && NewPlayer->PlayerState) ? *NewPlayer->PlayerState->GetPlayerName() : TEXT("Unknown"));

	if (MustSpectate(Cast<APlayerController>(NewPlayer)))
	{
		UE_LOG(LogGameMode, Verbose, TEXT("RestartPlayerAtPlayerStart: Tried to restart a spectator-only player!"));
		return;
	}

	if (NewPlayer->GetPawn() != nullptr)
	{
		APawn* Pawn = NewPlayer->GetPawn();
		NewPlayer->UnPossess();
		Pawn->Destroy();
	}
	if (GetDefaultPawnClassForController(NewPlayer) != nullptr)
	{
		// Try to create a pawn to use of the default class for this player
		NewPlayer->SetPawn(SpawnDefaultPawnFor(NewPlayer, StartSpot));
	}

	if (NewPlayer->GetPawn() == nullptr)
	{
		NewPlayer->FailedToSpawnPawn();
	}
	else
	{
		// Tell the start spot it was used
		InitStartSpot(StartSpot, NewPlayer);

		FinishRestartPlayer(NewPlayer, SpawnRotation);
	}
}
