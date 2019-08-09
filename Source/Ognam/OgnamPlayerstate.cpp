// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerState.h"
#include "UnrealNetwork.h"

AOgnamPlayerState::AOgnamPlayerState()
{
	Name = "Name me";
	NumKill = 0;
	NumDeath = 0;
}

void AOgnamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamPlayerState, Name);
	DOREPLIFETIME(AOgnamPlayerState, NumKill);
	DOREPLIFETIME(AOgnamPlayerState, NumDeath);
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
	Super::CopyProperties(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
			Name = OgnamPlayerState->Name;
		}
	}
}
