// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerController.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualGameMode.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
	
ARitualPlayerController::ARitualPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/CharacterSelection"));
	if (HUDFinder.Succeeded())
	{
		CharacterSelectionHUDClass = HUDFinder.Class;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Not Loaded"));
}

void ARitualPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("CharacterSelection"), IE_Pressed, this, &ARitualPlayerController::ToggleChangeCharacterUI);
}

void ARitualPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (CharacterSelectionHUDClass && IsLocalPlayerController())
	{
		CharacterSelectionHUD = CreateWidget<UUserWidget>(this, CharacterSelectionHUDClass);
		return;
	}
}

void ARitualPlayerController::Die()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Authoral call"));
		return;
	}
	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Ritual GameState"));
		return;
	}
	GameState->KillPlayer(this);
}

void ARitualPlayerController::ServerChangeCharacter_Implementation(UClass* PawnClass)
{
	//Set pawn class
	ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(PlayerState);
	RitualPlayerState->SetPawnClass(PawnClass);

	//respawn character
	ARitualGameMode* GameMode = Cast<ARitualGameMode>(GetWorld()->GetGameState()->AuthorityGameMode);
	GameMode->RestartPlayer(this);
}

void ARitualPlayerController::ShowCharacterSelection()
{
	//Find a better way to set input mode
	CharacterSelectionHUD->AddToViewport();
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	SetInputMode(FInputModeUIOnly());
}

void ARitualPlayerController::HideCharacterSelection()
{
	CharacterSelectionHUD->RemoveFromViewport();
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	SetInputMode(FInputModeGameOnly());
}

void ARitualPlayerController::ToggleChangeCharacterUI()
{
	if (!CharacterSelectionHUD || !IsLocalPlayerController())
	{
		return;
	}
	if (!CharacterSelectionHUD->IsInViewport())
	{
		ShowCharacterSelection();
	}
	else
	{
		HideCharacterSelection();
	}
}
