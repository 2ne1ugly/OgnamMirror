// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameState.h"
#include "RitualGameMode.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
#include "RitualShrine.h"
#include "RitualAcolyte.h"
#include "EngineUtils.h"

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
	CurrentOffenseTeam = GreenName;
	CurrentDefenseTeam = BlueName;
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
	DOREPLIFETIME(ARitualGameState, NumAcolytes);
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

void ARitualGameState::StartNewRound()
{
	//Increase Current Round
	CurrentRound++;

	//Reset Round time
	RoundStartTime = GetWorld()->GetTimeSeconds();

	//Start Phase 1
	PhaseStartTime = GetWorld()->GetTimeSeconds();

	for (TActorIterator<ARitualShrine> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->SpawnAcolytes(3);
	}

	PhaseGivenTime = 30;
}

void ARitualGameState::SwitchSides()
{
	//Switch Offense/Defense
	FName Temp = CurrentOffenseTeam;
	CurrentOffenseTeam = CurrentDefenseTeam;
	CurrentDefenseTeam = Temp;
}

bool ARitualGameState::ShouldEndMatch()
{
	if (GreenScore >= RequiredScore || BlueScore >= RequiredScore)
	{ 
		return true;
	}
	return false;
}

bool ARitualGameState::ShouldEndRound()
{
	if (GreenAliveCount == 0 || BlueAliveCount == 0 || GetPhaseRemainingTime() <= 0 || NumAcolytes == 0)
	{
		return true;
	}
	return false;
}

void ARitualGameState::DecideRoundWinner()
{
	// Out of time
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
		return;
	}

	// All acolytes dead
	if (NumAcolytes <= 0)
	{
		if (CurrentOffenseTeam == GreenName)
		{
			GreenScore++;
		}
		else if (CurrentOffenseTeam == BlueName)
		{
			BlueScore++;
		}
		return;
	}

	// Survining team
	if (GreenAliveCount != 0)
	{
		GreenScore++;
	}
	else if (BlueAliveCount != 0)
	{
		BlueScore++;
	}
}

void ARitualGameState::UpdateProperties()
{
	int32 Green = 0;
	int32 GreenAlive = 0;
	int32 Blue = 0;
	int32 BlueAlive = 0;
	for (APlayerState* PlayerState : PlayerArray)
	{
		ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(PlayerState);
		if (PlayerState == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Ritual Player State"));
			continue;
		}
		FName Team = RitualPlayerState->GetTeam();
		if (Team == GreenName)
		{
			Green++;
			if (RitualPlayerState->IsAlive())
				GreenAlive++;
		}
		else if (Team == BlueName)
		{
			Blue++;
			if (RitualPlayerState->IsAlive())
				BlueAlive++;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown Team name"));
		}
	}
	NumGreenPlayers = Green;
	GreenAliveCount = GreenAlive;
	NumBluePlayers = Blue;
	BlueAliveCount = BlueAlive;

	int32 AcolyteCount = 0;
	for (TActorIterator<ARitualShrine> Itr(GetWorld()); Itr; ++Itr)
	{
		AcolyteCount += Itr->Acolytes.Num();
	}
	NumAcolytes = AcolyteCount;
}

void ARitualGameState::GiveAcolyteKillReward()
{
	PhaseGivenTime += 20;
}
