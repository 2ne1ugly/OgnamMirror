// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameMode.h"

bool AOgnamGameMode::ReadyToStartMatch_Implementation()
{
	Super::ReadyToStartMatch();
	return MaxNumPlayers == NumPlayers;
}

void AOgnamGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerControllers.Add(NewPlayer);
}
