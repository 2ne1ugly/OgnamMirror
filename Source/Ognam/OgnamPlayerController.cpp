	// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"

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

AOgnamCharacter* AOgnamPlayerController::GetPossessedPawn() const
{
	return PossessedPawn;
}

void AOgnamPlayerController::BeginPlay()
{
	/*
	**	TODO: Have this hud thing done after postlogin.
	**	IsLocalPlayerController isn't set propley
	*/
	if (HUDClass && IsLocalPlayerController())
	{
		HUD = CreateWidget<UUserWidget>(this, HUDClass);
		UProperty* Property = HUD->GetClass()->FindPropertyByName("Parent Controller");
		if (Property)
		{
			AOgnamPlayerController* reference = Property->ContainerPtrToValuePtr<AOgnamPlayerController>(HUD);
			reference = this;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("no prop"));
		if (HUD)
		{
			HUD->AddToViewport();
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Not hh"));
	}
}

void AOgnamPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedPawn = Cast<AOgnamCharacter>(InPawn);
}

void AOgnamPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedPawn = nullptr;
}
