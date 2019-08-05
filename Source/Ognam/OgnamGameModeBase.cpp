// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameModeBase.h"
#include "OgnamCharacter.h"
#include "OgnamPlayerController.h"

AOgnamGameModeBase::AOgnamGameModeBase()
{
	DefaultPawnClass = AOgnamCharacter::StaticClass();
	PlayerControllerClass = AOgnamPlayerController::StaticClass();
}