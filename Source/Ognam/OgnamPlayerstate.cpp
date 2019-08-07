// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerState.h"

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
