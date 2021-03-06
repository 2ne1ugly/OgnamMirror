// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameMode.h"
#include "GameFramework/PlayerState.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamMacro.h"
#include "CreateSessionCallbackProxy.h"

ARitualGameMode::ARitualGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	GameStateClass = ARitualGameState::StaticClass();
	PlayerStateClass = ARitualPlayerState::StaticClass();
	PlayerControllerClass = ARitualPlayerController::StaticClass();

	PostRoundTime = 1.5f; // this is actually 3 seconds
	CharacterSelectionTime = 10.f;
	if (GIsEditor)
	{
		CharacterSelectionTime = 5.f;
	}
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
		O_LOG(TEXT("Not a Ritual Gamestate"));
		return;
	}
	RitualGameState->UpdateProperties();
	if (RitualGameState->ShouldEndRound() && !RitualGameState->IsRoundEnding())
	{
		StartPostRound();
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
	
	O_LOG(TEXT("Option String : %s"), *Options);
	
	MaxNumPlayers = FCString::Atoi(*PlayerCount);

	O_LOG(TEXT("PlayerCount - %s"), *PlayerCount);
	if (MaxNumPlayers == 0)
		MaxNumPlayers = 4;
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
	if (!RitualGameState)
	{
		O_LOG(TEXT("Not a Ritual Gamestate"));
		return;
	}
	StartPreRound();
}

void ARitualGameMode::StartPreRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (!RitualGameState)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	RitualGameState->SetPreRoundStage(true);
	RitualGameState->UpdateProperties();
	RitualGameState->NetReset();
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
		PlayerController->PreRoundBegin();
		RitualPlayerState->ClientStartPreRound();
		if (!RitualPlayerState)
		{
			O_LOG(TEXT("No Playerstate bound to Player Controller"));
		}
		else
		{
			RitualPlayerState->SetIsAlive(true);
			RitualPlayerState->ForceNetUpdate();
		}
	}
	GetWorld()->GetTimerManager().SetTimer(PreRoundTimer, this, &ARitualGameMode::EndPreRound, CharacterSelectionTime, false);
}

void ARitualGameMode::EndPreRound()
{
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		RestartPlayer(PlayerController);
		PlayerController->PreRoundEnd();
		ARitualPlayerState* State = PlayerController->GetPlayerState<ARitualPlayerState>();
		State->ClientEndPreRound();
		State->PawnClass = PlayerController->GetPawn()->GetClass();
	}
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (!RitualGameState)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	BeginRound();
}

void ARitualGameMode::BeginRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		ARitualPlayerState* State = PlayerController->GetPlayerState<ARitualPlayerState>();
		State->ClientBeginRound();
	}
	RitualGameState->SetPreRoundStage(false);
	RitualGameState->SetRoundEnding(false);
	RitualGameState->StartNewRound();
}

void ARitualGameMode::StartPostRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		ARitualPlayerState* State = PlayerController->GetPlayerState<ARitualPlayerState>();
		State->ClientStartPostRound();
	}
	RitualGameState->SetRoundEnding(true);
	RitualGameState->NetStartSlowMotion();
	GetWorld()->GetTimerManager().SetTimer(PostRoundTimer, this, &ARitualGameMode::EndPostRound, PostRoundTime, false);
}

void ARitualGameMode::EndPostRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (RitualGameState == nullptr)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		ARitualPlayerState* State = PlayerController->GetPlayerState<ARitualPlayerState>();
		State->ClientEndPostRound();
	}
	RitualGameState->NetEndSlowMotion();
	EndRound();
}

void ARitualGameMode::EndRound()
{
	ARitualGameState* RitualGameState = GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		O_LOG(TEXT("Not Ritual Gamestate"));
		return;
	}
	for (ARitualPlayerController* PlayerController : PlayerControllers)
	{
		ARitualPlayerState* State = PlayerController->GetPlayerState<ARitualPlayerState>();
		State->ClientEndRound();
	}
	RitualGameState->DecideRoundWinner();

	RitualGameState->NetEndSlowMotion();

	//If Match should be done End match
	if (RitualGameState->ShouldEndMatch())
	{
		EndMatch();
	}

	//Start round no matter what for testing purpose
	RitualGameState->SwitchSides();

	for (TActorIterator<AOgnamCharacter> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->Destroy();
	}
	StartPreRound();
}

void ARitualGameMode::KillPlayer(ARitualPlayerController* PlayerController)
{
	//This function doesn't go through kill event signal.
	//Kill pawn
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(PlayerController->GetPawn());
	if (Character != nullptr)
	{
		Character->NetDie();
	}
	else
	{
		O_LOG(TEXT("Not Player Controller"));
	}

	//Set states
	ARitualPlayerState* PlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	if (PlayerState != nullptr)
	{
		PlayerState->SetIsAlive(false);
	}
	else
	{
		O_LOG(TEXT("Not Player Controller"));
	}
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
		O_LOG(TEXT("Some one is not a Ritual Player State!"));
	}
	else
	{
		int32 GreenCount = RitualGameState->GetNumGreenPlayers();
		int32 BlueCount = RitualGameState->GetNumBluePlayers();
		if (GreenCount > BlueCount)
		{
			RitualPlayerState->SetTeam(RitualGameState->BlueName);
			RitualPlayerState->SetTeamIndex(RitualGameState->GetNumBluePlayers());
		}
		else
		{
			RitualPlayerState->SetTeam(RitualGameState->GreenName);
			RitualPlayerState->SetTeamIndex(RitualGameState->GetNumGreenPlayers());
		}
		PlayerController->ClientGameStarted();
		PlayerControllers.Push(PlayerController);
		RitualGameState->UpdateProperties();
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
	O_LOG(TEXT("%s\n"), *Options);
}

void ARitualGameMode::Logout(AController* PlayerController)
{
	Super::Logout(PlayerController);
	APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>();
	O_LOG(TEXT("%s player left"), *PlayerState->GetPlayerName());
	ARitualPlayerController* RitualController = Cast<ARitualPlayerController>(PlayerController);
	PlayerControllers.Remove(RitualController);
}

AActor* ARitualGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (!HasMatchStarted())
		return Super::FindPlayerStart_Implementation(Player, IncomingName);
	//get states
	ARitualPlayerState* PlayerState = Player->GetPlayerState<ARitualPlayerState>();
	if (PlayerState == nullptr)
	{
		O_LOG(TEXT("GameState or ARitualPlayerController invalid"), __FUNCTION__);
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
	O_LOG(TEXT("Not enough Spawn points"));
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
		O_LOG(TEXT("Player start not found"));
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
	return PlayerState->GetSelectedPawnClass();
}
