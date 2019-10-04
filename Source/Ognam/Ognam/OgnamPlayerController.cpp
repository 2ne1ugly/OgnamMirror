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
#include "Sound/SoundCue.h"

AOgnamPlayerController::AOgnamPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/OgnamHUD"));
	if (HUDFinder.Succeeded())
	{
		OgnamHUDClass = HUDFinder.Class;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("%s Not Loaded"), __FUNCTION__);

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuHUDFinder(TEXT("/Game/UI/GameMenu"));
	if (MenuHUDFinder.Succeeded())
	{
		MenuHUDClass = MenuHUDFinder.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundCue(TEXT("SoundCue'/Game/Sounds/General/hitsound_Cue.hitsound_Cue'"));

	HitSound = HitSoundCue.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> KillSoundCue(TEXT("SoundCue'/Game/Sounds/General/Kill/ownage_Cue.ownage_Cue'"));

	KillSound = KillSoundCue.Object;
}

void AOgnamPlayerController::BeginPlay()
{
	//LoadSensitivity();
	LoadConfig();
	if (OgnamHUDClass && IsLocalPlayerController())
	{
		OgnamHUD = CreateWidget<UUserWidget>(this, OgnamHUDClass);

		//This part should be chosen properly
		if (OgnamHUD)
		{
			OgnamHUD->AddToViewport();
		}
	}
	if (MenuHUDClass && IsLocalPlayerController())
	{
		MenuHUD = CreateWidget<UUserWidget>(this, MenuHUDClass);
		MenuHUD->bIsFocusable = true;
	}
}

void AOgnamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GameMenu"), EInputEvent::IE_Pressed, this, &AOgnamPlayerController::ShowMenu);
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
	ClientPlaySound(HitSound, 1.f, 1.f);
}

void AOgnamPlayerController::ClientFeedBackKill_Implementation()
{
	ClientPlaySound(KillSound, 10.f, 1.f);
}

void AOgnamPlayerController::ShowMenu()
{
	if (MenuHUD->IsInViewport())
	{
		MenuHUD->RemoveFromViewport();
		if (GetPawn())
		{
			GetPawn()->EnableInput(this);
		}
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		MenuHUD->AddToViewport();
		if (GetPawn())
		{
			GetPawn()->DisableInput(this);
		}
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}

float AOgnamPlayerController::GetSensitivity() const
{
	return InputYawScale;
}

void AOgnamPlayerController::SetSensitivity(float Sens)
{
	SaveConfig();
	InputPitchScale = -Sens;
	InputYawScale = Sens;
}
