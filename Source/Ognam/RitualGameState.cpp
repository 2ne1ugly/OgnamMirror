// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameState.h"
#include "RitualGameMode.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"

ARitualGameState::ARitualGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	CurrentRound = 0;
	RequiredScore = 3;
	GreenScore = 0;
	BlueScore = 0;
	BlueAliveCount = 0;
	GreenAliveCount = 0;
	CurrentOffenseTeam = BlueName;
	CurrentDefenseTeam = GreenName;
}

void ARitualGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARitualGameState, RequiredScore);
	DOREPLIFETIME(ARitualGameState, CurrentRound);
	DOREPLIFETIME(ARitualGameState, GreenScore);
	DOREPLIFETIME(ARitualGameState, BlueScore);
	DOREPLIFETIME(ARitualGameState, CurrentOffenseTeam);
	DOREPLIFETIME(ARitualGameState, CurrentDefenseTeam);
	DOREPLIFETIME(ARitualGameState, NumBluePlayers);
	DOREPLIFETIME(ARitualGameState, NumGreenPlayers);
	DOREPLIFETIME(ARitualGameState, GreenAliveCount);
	DOREPLIFETIME(ARitualGameState, BlueAliveCount);
}

void ARitualGameState::Tick(float DeltaTime)
{
	if (!HasMatchStarted())
		return;

	//Check Round ending condition
	if (HasAuthority())
	{
		if (GreenAliveCount == 0 || BlueAliveCount == 0)
		{
			EndRound();
		}
	}
}

FName ARitualGameState::GetCurrentOffenseTeam() const
{
	return CurrentOffenseTeam;
}

FName ARitualGameState::GetCurrentDefenseTeam() const
{
	return CurrentDefenseTeam;
}

int32 ARitualGameState::GetGreenAliveCount() const
{
	return GreenAliveCount;
}

int32 ARitualGameState::GetBlueAliveCount() const
{
	return BlueAliveCount;
}

int32 ARitualGameState::GetGreenScore() const
{
	return GreenScore;
}

int32 ARitualGameState::GetBlueScore() const
{
	return BlueScore;
}

int32 ARitualGameState::GetNumGreenPlayers() const
{
	return NumGreenPlayers;
}

int32 ARitualGameState::GetNumBluePlayers() const
{
	return NumBluePlayers;
}

int32 ARitualGameState::GetCurrentRound() const
{
	return CurrentRound;
}

void ARitualGameState::IncNumGreenPlayers()
{
	NumGreenPlayers++;
}

void ARitualGameState::IncNumBluePlayers()
{
	NumBluePlayers++;
}

void ARitualGameState::StartRound()
{
	if (HasAuthority())
	{
		//Increase Current Round
		CurrentRound++;
		ARitualGameMode* GameMode = Cast<ARitualGameMode>(AuthorityGameMode);
		if (GameMode == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not ritual gamemode"));
		}

		//Restart all player and set them to alive, meanwhile set Alive count to correct number
		int32 GreenCount = 0;
		int32 BlueCount = 0;
		for (ARitualPlayerController* PlayerController : GameMode->PlayerControllers)
		{
			GameMode->RestartPlayer(PlayerController);
			ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
			RitualPlayerState->SetIsAlive(true);
			if (RitualPlayerState->GetTeam() == GreenName)
			{
				GreenCount++;
			}
			else if (RitualPlayerState->GetTeam() == BlueName)
			{
				BlueCount++;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid Name!"));
			}
		}
		GreenAliveCount = GreenCount;
		BlueAliveCount = BlueCount;

		//Switch Offense/Defense
		FName Temp = CurrentOffenseTeam;
		CurrentOffenseTeam = CurrentDefenseTeam;
		CurrentDefenseTeam = Temp;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call of Start Round"));
	}
}

void ARitualGameState::KillPlayer(ARitualPlayerController* PlayerController)
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call"));
		return;
	}

	//Kill pawn
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(PlayerController->GetPawn());
	if (Character != nullptr)
	{
		Character->Die();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Player Controller"));
	}

	//Set states
	ARitualPlayerState* PlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	PlayerState->SetIsAlive(false);
	if (PlayerState->GetTeam() == GreenName)
	{
		GreenAliveCount--;
	}
	else if (PlayerState->GetTeam() == BlueName)
	{
		BlueAliveCount--;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Team name"));
	}
}

void ARitualGameState::EndRound()
{
	if (HasAuthority())
	{
		ARitualGameMode* GameMode = Cast<ARitualGameMode>(AuthorityGameMode);
		if (GreenAliveCount != 0)
		{
			GreenScore++;
			if (GreenScore == RequiredScore)
			{
				GameMode->EndMatch();
			}
		}
		else if (BlueAliveCount != 0)
		{
			BlueScore++;
			if (BlueScore == RequiredScore)
			{
				GameMode->EndMatch();

			}
		}
		StartRound();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call of End Round"));
	}
}
