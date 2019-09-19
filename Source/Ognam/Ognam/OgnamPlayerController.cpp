	// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerController.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "OgnamCharacter.h"
#include "Engine/World.h"
#include "DamageText.h"

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

void AOgnamPlayerController::ClientRestart_Implementation(APawn* aPawn)
{
	Super::ClientRestart_Implementation(aPawn);

	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(aPawn);

	if (OgnamCharacter == nullptr)
	{
		return;
	}
	if (CharacterHUD && CharacterHUD->IsInViewport())
	{
		CharacterHUD->RemoveFromViewport();
		CharacterHUD = nullptr;
	}
	if (OgnamCharacter->CharacterSpecificHUDClass)
	{
		CharacterHUD = CreateWidget<UUserWidget>(this, OgnamCharacter->CharacterSpecificHUDClass);
		if (CharacterHUD)
		{
			CharacterHUD->AddToViewport();
		}
	}

}

void AOgnamPlayerController::ClientFeedBackDamageDealt_Implementation(FVector Location, float Damage)
{
	ADamageText* Text = GetWorld()->SpawnActor<ADamageText>(Location, FRotator::ZeroRotator);
	Text->SetDamage(Damage);
}

