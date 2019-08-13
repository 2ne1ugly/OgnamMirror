	// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"

AOgnamPlayerController::AOgnamPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/OgnamHUD"));
	if (HUDFinder.Succeeded())
	{
		HUDClass = HUDFinder.Class;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Not Loaded"));
}

void AOgnamPlayerController::BeginPlay()
{
	if (HUDClass && IsLocalPlayerController())
	{
		HUD = CreateWidget<UUserWidget>(this, HUDClass);
		if (HUD)
		{
			HUD->AddToViewport();
		}
	}
}
