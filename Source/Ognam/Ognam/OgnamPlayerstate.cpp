// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerState.h"
#include "UnrealNetwork.h"

AOgnamPlayerState::AOgnamPlayerState()
{
	Name = "Name me";
	NumKill = 0;
	NumDeath = 0;
	Team = TEXT("No Team");
}

void AOgnamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamPlayerState, Name);
	DOREPLIFETIME(AOgnamPlayerState, NumKill);
	DOREPLIFETIME(AOgnamPlayerState, NumDeath);
	DOREPLIFETIME(AOgnamPlayerState, Team);
}

void AOgnamPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
			OgnamPlayerState->Name = Name;
		}
	}
}

void AOgnamPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
			Name = OgnamPlayerState->Name;
		}
	}
}

void AOgnamPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName AOgnamPlayerState::GetTeam() const
{
	return Team;
}
