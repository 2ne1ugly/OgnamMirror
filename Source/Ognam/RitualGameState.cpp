// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameState.h"
#include "RitualGameMode.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"

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
	RoundStartTime = 0;
	PhaseStartTime = 0;
	PhaseGivenTime = 0;
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
	DOREPLIFETIME(ARitualGameState, RoundStartTime);
	DOREPLIFETIME(ARitualGameState, PhaseStartTime);
	DOREPLIFETIME(ARitualGameState, PhaseGivenTime);
}

void ARitualGameState::Tick(float DeltaTime)
{
	if (!HasMatchStarted())
		return;

	//Check Round ending condition
	if (HasAuthority())
	{
		//If etiher of the side is all dead or time ran out
		if (GreenAliveCount == 0 || BlueAliveCount == 0 || GetPhaseRemainingTime() <= 0)
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

float ARitualGameState::GetRoundStartTime() const
{
	return RoundStartTime;
}

float ARitualGameState::GetPhaseStartTime() const
{
	return PhaseStartTime;
}

float ARitualGameState::GetPhaseGivenTime() const
{
	return PhaseGivenTime;
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

		//Switch Offense/Defense
		FName Temp = CurrentOffenseTeam;
		CurrentOffenseTeam = CurrentDefenseTeam;
		CurrentDefenseTeam = Temp;

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

		//Reset Round time
		RoundStartTime = GetWorld()->GetTimeSeconds();

		//Start Phase 1
		PhaseStartTime = GetWorld()->GetTimeSeconds();
		PhaseGivenTime = 30;
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

float ARitualGameState::GetPhaseRemainingTime() const
{
	float CurrentTime;
	if (HasAuthority())
	{
		CurrentTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		CurrentTime = GetServerWorldTimeSeconds();
	}

	return	PhaseGivenTime - (CurrentTime - PhaseStartTime);
}

void ARitualGameState::EndRound()
{
	if (HasAuthority())
	{
		ARitualGameMode* GameMode = Cast<ARitualGameMode>(AuthorityGameMode);

		if (GetPhaseRemainingTime() <= 0)
		{
			if (CurrentDefenseTeam == GreenName)
			{
				GreenScore++;
			}
			else if (CurrentDefenseTeam == BlueName)
			{
				BlueScore++;
			}
		}
		else if (GreenAliveCount != 0)
		{
			GreenScore++;
		}
		else if (BlueAliveCount != 0)
		{
			BlueScore++;
		}

		// Deal with this problem later
		if (GreenScore == RequiredScore)
		{
			GameMode->EndMatch();
			return;
		}
		else if (BlueScore == RequiredScore)
		{
			GameMode->EndMatch();
			return;
		}
		StartRound();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call of End Round"));
	}
}
