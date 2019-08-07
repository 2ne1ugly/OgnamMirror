// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameState.h"
#include "UnrealNetwork.h"

void AOgnamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamGameState, TeamACount);
	DOREPLIFETIME(AOgnamGameState, TeamBCount);
}

int32 AOgnamGameState::GetTeamACount() const
{
	return TeamACount;
}

int32 AOgnamGameState::GetTeamBCount() const
{
	return TeamBCount;
}
