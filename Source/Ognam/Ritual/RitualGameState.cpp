// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameState.h"
#include "RitualGameMode.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
#include "RitualShrine.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamMacro.h"

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
	DilationAmount = .5f;
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
	DOREPLIFETIME(ARitualGameState, bRoundEnding);
	DOREPLIFETIME(ARitualGameState, bPreRound);
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

bool ARitualGameState::IsPreRound() const
{
	return bPreRound;
}

void ARitualGameState::SetPreRoundStage(bool bIsPreRound)
{
	bPreRound = bIsPreRound;
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

const FString ARitualGameState::GetFormatRemainingTime() const
{
	int Time = FMath::RoundToInt(GetPhaseRemainingTime());
	int Seconds = Time % 60;
	int Minutes = (Time - Seconds) / 60.f;
	return FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
}

void ARitualGameState::StartNewRound()
{
	//Increase Current Round
	CurrentRound++;

	//Reset Round time
	RoundStartTime = GetWorld()->GetTimeSeconds();

	//Start Phase 1
	PhaseStartTime = GetWorld()->GetTimeSeconds();

	PhaseGivenTime = 120;

	for (TActorIterator<ARitualShrine> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->Reset();
	}

	bPreRound = false;
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
	if (bPreRound)
		return false;
	if (GreenAliveCount == 0 || BlueAliveCount == 0 || GetPhaseRemainingTime() <= 0)
	{
		return true;
	}

	for (TActorIterator<ARitualShrine> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr->ShouldRoundEnd())
		{
			return true;
		}
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

	// Captured a site
	for (TActorIterator<ARitualShrine> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr->ShouldRoundEnd())
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
			O_LOG(TEXT("Not Ritual Player State"));
			continue;
		}
		FName Team = RitualPlayerState->GetTeam();
		O_LOG(TEXT("RitualGameState : %s - %d"), *RitualPlayerState->GetPlayerName(), RitualPlayerState->IsAlive());
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
			O_LOG(TEXT("Unknown Team name"));
		}
	}
	NumGreenPlayers = Green;
	GreenAliveCount = GreenAlive;
	NumBluePlayers = Blue;
	BlueAliveCount = BlueAlive;
}

void ARitualGameState::SetRoundEnding(bool b)
{
	bRoundEnding = b;
}

bool ARitualGameState::IsRoundEnding() const
{
	return bRoundEnding;
}

void ARitualGameState::NetEndSlowMotion_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void ARitualGameState::NetStartSlowMotion_Implementation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilationAmount);
}
