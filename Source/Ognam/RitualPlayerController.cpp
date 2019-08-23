// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerController.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualGameMode.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"
#include "Interactable.h"
	
ARitualPlayerController::ARitualPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder1(TEXT("/Game/UI/CharacterSelection"));
	if (HUDFinder1.Succeeded())
	{
		CharacterSelectionHUDClass = HUDFinder1.Class;
	}
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

void ARitualPlayerController::OnPawnDeath()
{
	ARitualPlayerState* RitualPlayerState = GetPlayerState<ARitualPlayerState>();
	if (RitualPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Ritual Player State"));
		return;
	}
	RitualPlayerState->SetIsAlive(false);
}

void ARitualPlayerController::ServerChangeCharacter_Implementation(UClass* CharacterClass)
{
	//Set pawn class
	ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(PlayerState);
	RitualPlayerState->SetPawnClass(CharacterClass);

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

bool ARitualPlayerController::CanInteract() const
{
	FHitResult HitResult;

	//See if pawn exists as character
	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(GetPawn());
	if (OgnamCharacter == nullptr)
	{
		return false;
	}

	//See if something's blocking hit from camera
	OgnamCharacter->GetAimHitResult(HitResult, 0.f, 10000.f);
	if (!HitResult.bBlockingHit)
	{
		return false;
	}

	//See if it's interactable
	AActor* Actor = HitResult.Actor.Get();
	IInteractable* Interactable = Cast<IInteractable>(Actor);
	if (Interactable == nullptr)
	{
		return false;
	}

	//See if it's interactable range
	float Distance = FVector::Dist(OgnamCharacter->GetActorLocation(),  Actor->GetActorLocation());
	if (Interactable->GetInteractDistance() < Distance)
	{
		return false;
	}
	return true;
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
