// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameMode.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ARitualGameMode::ARitualGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	GameStateClass = ARitualGameState::StaticClass();
	PlayerStateClass = ARitualPlayerState::StaticClass();
	PlayerControllerClass = ARitualPlayerController::StaticClass();

	PostRoundTime = 3.f;
}

void ARitualGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasMatchStarted())
	{
		return ;
	}

	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not a Ritual Gamestate"), __FUNCTION__);
		return;
	}
	RitualGameState->UpdateProperties();
	if (RitualGameState->ShouldEndRound() && !RitualGameState->IsRoundEnding())
	{
		RitualGameState->SetRoundEnding(true);
		GetWorld()->GetTimerManager().SetTimer(MatchEndTimer, this, &ARitualGameMode::EndRound, PostRoundTime, false);
	}
}

// This is where you init game based on options and Maps
void ARitualGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (!ErrorMessage.IsEmpty())
	{
		return;
	}

	FString PlayerCount = UGameplayStatics::ParseOption(Options, "numplayers");
	UE_LOG(LogTemp, Warning, TEXT("%s\n"), *Options);
	UE_LOG(LogTemp, Warning, TEXT("%s\n"), *PlayerCount);
	MaxNumPlayers = FCString::Atoi(*PlayerCount);

	if (MaxNumPlayers == 0)
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
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not a Ritual Gamestate"), __FUNCTION__);
		return;
	}
	StartFirstRound();
}

void ARitualGameMode::KillPlayer(ARitualPlayerController* PlayerController)
{
	//Kill pawn
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(PlayerController->GetPawn());
	if (Character != nullptr)
	{
		Character->Die();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Player Controller"), __FUNCTION__);
	}

	//Set states
	ARitualPlayerState* PlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	if (PlayerState != nullptr)
	{
		PlayerState->SetIsAlive(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Player Controller"), __FUNCTION__);
	}
}

void ARitualGameMode::RespawnPlayer(ARitualPlayerController* PlayerController)
{
}

void ARitualGameMode::RespawnAllPlayer()
{
	//Restart all player and set them to alive
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		RestartPlayer(PlayerController);
		ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
		if (RitualPlayerState != nullptr)
		{
			RitualPlayerState->SetIsAlive(true);
		}
	}
}

void ARitualGameMode::StartFirstRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Ritual Gamestate"), __FUNCTION__);
		return;
	}

	RespawnAllPlayer();
	RitualGameState->StartNewRound();
}

void ARitualGameMode::RestartRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Ritual Gamestate"), __FUNCTION__);
		return;
	}

	RitualGameState->SetRoundEnding(false);
	RitualGameState->SwitchSides();
	RespawnAllPlayer();
	RitualGameState->StartNewRound();
}

void ARitualGameMode::EndRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Ritual Gamestate"), __FUNCTION__);
		return;
	}

	//Decide Round Winnder;
	RitualGameState->DecideRoundWinner();

	//If Match should be done End match
	if (RitualGameState->ShouldEndMatch())
		EndMatch();

	//Start round no matter what for testing purpose
	RestartRound();
}

void ARitualGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ARitualPlayerController *PlayerController = Cast<ARitualPlayerController>(NewPlayer);
	if (PlayerController == nullptr)
		return;
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	//Assign Team
	if (RitualPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Some one is not a Ritual Player State!"), __FUNCTION__);
	}
	else
	{
		if (PlayerControllers.Num() % 2)
		{
			RitualPlayerState->SetTeam(RitualGameState->GreenName);
			RitualPlayerState->SetTeamIndex(RitualGameState->GetNumGreenPlayers());
		}
		else
		{
			RitualPlayerState->SetTeam(RitualGameState->BlueName);
			RitualPlayerState->SetTeamIndex(RitualGameState->GetNumBluePlayers());
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
	UE_LOG(LogTemp, Warning, TEXT("%s\n"), *Options);
	if (IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Warning, TEXT("This is running Dedicated Server"));
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
		UE_LOG(LogTemp, Warning, TEXT("%s GameState or ARitualPlayerController invalid"), __FUNCTION__);
		return nullptr;
	}

	//find right n'th index
	FName Side = PlayerState->GetSide();
	int32 GivenIndex = PlayerState->GetTeamIndex();
	int32 CurrentIndex = 0;
	for (TActorIterator<APlayerStart> itr(GetWorld()); itr; ++itr)
	{
		if (itr->PlayerStartTag == Side)
		{
			if (CurrentIndex == GivenIndex)
			{
				return *itr;
			}
			CurrentIndex++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%s Not enough Spawn points"), __FUNCTION__);
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
		UE_LOG(LogGameMode, Warning, TEXT("%s Player start not found"), __FUNCTION__);
		return;
	}

	FRotator SpawnRotation = StartSpot->GetActorRotation();

	UE_LOG(LogGameMode, Verbose, TEXT("%s %s"), __FUNCTION__, (NewPlayer && NewPlayer->PlayerState) ? *NewPlayer->PlayerState->GetPlayerName() : TEXT("Unknown"));

	if (MustSpectate(Cast<APlayerController>(NewPlayer)))
	{
		UE_LOG(LogGameMode, Verbose, TEXT("%s Tried to restart a spectator-only player!"), __FUNCTION__);
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

UClass* ARitualGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ARitualPlayerState* PlayerState = InController->GetPlayerState<ARitualPlayerState>();
	return PlayerState->GetPawnClass();
}
