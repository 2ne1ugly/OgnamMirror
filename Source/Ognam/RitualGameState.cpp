// Fill out your copyright notice in the Description page of Project Settings.

#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "UnrealNetwork.h"

ARitualGameState::ARitualGameState()
{
	CurrentRound = 1;
	RequiredScore = 3;
	GreenScore = 0;
	BlueScore = 0;
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
}

void ARitualGameState::HandleMatchHasStarted()
{
	//distribute Teams, it is not replicated func bc it should be always synced.
	for (APlayerState* PlayerState : PlayerArray)
	{
		ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(PlayerState);
		if (RitualPlayerState == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Some one is not a Ritual Player State!"));
		}
		else
		{
			//Set team recieves Fname which is basically hash mapped comparison.
			if (GreenPlayers.Num() > BluePlayers.Num())
			{
				RitualPlayerState->SetTeam(TEXT("Green"));
			}
			else
			{
				RitualPlayerState->SetTeam(TEXT("Blue"));
			}
		}
	}

	//Init attack and defense
	CurrentOffenseTeam = TEXT("Green");
	CurrentDefenseTeam = TEXT("Blue");
}

FName ARitualGameState::GetCurrentOffenseTeam() const
{
	return CurrentOffenseTeam;
}

FName ARitualGameState::GetCurrentDefenseTeam() const
{
	return CurrentDefenseTeam;
}
