// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	bShowMouseCursor = true;
}

void AMainMenuPlayerController::JoinGame(FString Address)
{
	ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
