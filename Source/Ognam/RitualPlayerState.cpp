// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerState.h"

ARitualPlayerState::ARitualPlayerState()
{
	Team = TEXT("Undefined");
}

void ARitualPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ARitualPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName ARitualPlayerState::GetTeam() const
{
	return Team;
}
