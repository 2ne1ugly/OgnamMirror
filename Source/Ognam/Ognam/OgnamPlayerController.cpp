	// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "OgnamCharacter.h"

AOgnamPlayerController::AOgnamPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/OgnamHUD"));
	if (HUDFinder.Succeeded())
	{
		OgnamHUDClass = HUDFinder.Class;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("%s Not Loaded"), __FUNCTION__);
}

void AOgnamPlayerController::BeginPlay()
{
	if (OgnamHUDClass && IsLocalPlayerController())
	{
		OgnamHUD = CreateWidget<UUserWidget>(this, OgnamHUDClass);

		//This part should be chosen properly
		if (OgnamHUD)
		{
			OgnamHUD->AddToViewport();
		}
	}
}

void AOgnamPlayerController::OnPawnDeath()
{
}

void AOgnamPlayerController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(Pawn);

	if (Character == nullptr)
	{
		return;
	}

	if (Character->CharacterSpecificHUDClass && IsLocalPlayerController())
	{
		CharacterSpecificHUD = CreateWidget<UUserWidget>(this, Character->CharacterSpecificHUDClass);
		if (CharacterSpecificHUD)
		{
			CharacterSpecificHUD->AddToViewport();
		}
	}
}

void AOgnamPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (CharacterSpecificHUD && IsLocalPlayerController() && CharacterSpecificHUD->IsInViewport())
	{
		CharacterSpecificHUD->RemoveFromViewport();
		CharacterSpecificHUD = nullptr;
	}
}


