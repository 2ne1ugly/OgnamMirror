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
#include "UnrealNetwork.h"
#include "Engine.h"
	
ARitualPlayerController::ARitualPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder1(TEXT("/Game/UI/CharacterSelection"));
	if (HUDFinder1.Succeeded())
	{
		CharacterSelectionHUDClass = HUDFinder1.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder2(TEXT("/Game/UI/ProgressBar"));
	if (HUDFinder2.Succeeded())
	{
		InteractionBarClass = HUDFinder2.Class;
	}
}

void ARitualPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("CharacterSelection"), IE_Pressed, this, &ARitualPlayerController::ToggleChangeCharacterUI);
	InputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ARitualPlayerController::StartInteract);
	InputComponent->BindAction(TEXT("Interact"), IE_Released, this, &ARitualPlayerController::StopInteract);
}

void ARitualPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Create all using widget
	if (IsLocalPlayerController())
	{
		if (CharacterSelectionHUDClass)
		{
			CharacterSelectionHUD = CreateWidget<UUserWidget>(this, CharacterSelectionHUDClass);
		}
		if (InteractionBarClass)
		{
			InteractionBar = CreateWidget<UUserWidget>(this, InteractionBarClass);
		}
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

void ARitualPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Replicating Tick values seems dangerous. find a better way.
	if (bIsInteracting)
	{
		InteractionTime += DeltaTime;
	}

	// Interaction progress
	if (HasAuthority() && bIsInteracting)
	{
		IInteractable* Interactable = Cast<IInteractable>(InteractedActor);
		if (Interactable == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Interactable"));
			return;
		}
		// Interrupt Interaction when too far.
		if (Interactable->GetInteractDistance() <= GetDistanceBetweenInteracted())
		{
			InteractionTime = 0;
			bIsInteracting = false;
			InterruptInteract();
		}
		// Finish interaction when time done.
		else if (Interactable->GetInteractDuration() <= InteractionTime)
		{
			InteractionTime = 0;
			bIsInteracting = false;
			Interactable->Execute_BeInteracted(InteractedActor, this);
			InterruptInteract();
		}

	}
}

float ARitualPlayerController::GetInteractionProgress() const
{
	IInteractable* Interactable = Cast<IInteractable>(InteractedActor);
	if (Interactable == nullptr)
	{
		return 0.0f;
	}
	return InteractionTime / Interactable->GetInteractDuration();
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
	if (CharacterSelectionHUD)
	{
		CharacterSelectionHUD->AddToViewport();
	}
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	SetInputMode(FInputModeUIOnly());
}

void ARitualPlayerController::HideCharacterSelection()
{
	if (CharacterSelectionHUD)
	{
		CharacterSelectionHUD->RemoveFromViewport();
	}
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	SetInputMode(FInputModeGameOnly());
}

AActor* ARitualPlayerController::GetInteractedActor() const
{
	return InteractedActor;
}

float ARitualPlayerController::GetDistanceBetweenInteracted() const
{
	if (!bIsInteracting || !InteractedActor || !GetPawn())
	{
		return 0.0f;
	}
	return FVector::Dist(GetPawn()->GetActorLocation(), InteractedActor->GetActorLocation());
}

bool ARitualPlayerController::CanInteract() const
{
	//See if targeted actor is interactable
	AActor* Actor = GetTargetedActor();
	IInteractable* Interactable = Cast<IInteractable>(Actor);
	if (Interactable == nullptr)
	{
		return false;
	}

	//See if it's interactable range
	float Distance = FVector::Dist(GetPawn()->GetActorLocation(),  Actor->GetActorLocation());
	if (Interactable->GetInteractDistance() < Distance)
	{
		return false;
	}

	//See if it's fine interation
	if (!Interactable->CanInteractWithController(this))
	{
		return false;
	}

	return true;
}

AActor* ARitualPlayerController::GetTargetedActor() const
{
	//See if pawn exists as character
	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(GetPawn());
	if (OgnamCharacter == nullptr)
	{
		return nullptr;
	}

	FHitResult HitResult;
	//See if something's blocking hit from camera
	OgnamCharacter->GetAimHitResult(HitResult, 0.f, 10000.f);
	if (!HitResult.bBlockingHit)
	{
		return nullptr;
	}

	return HitResult.Actor.Get();
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

void ARitualPlayerController::ServerStartInteract_Implementation()
{
	if (CanInteract())
	{
		bIsInteracting = true;
		InteractedActor = GetTargetedActor();
		InteractionTime = 0;
	}
	else
	{
		StopInteract();
	}
}

void ARitualPlayerController::ServerStopInteract_Implementation()
{
	bIsInteracting = false;
	InteractedActor = nullptr;
	InteractionTime = 0;
}

void ARitualPlayerController::StartInteract()
{
	if (CanInteract())
	{
		bIsInteracting = true;
		InteractedActor = GetTargetedActor();
		InteractionTime = 0;
		if (InteractionBar)
		{
			InteractionBar->AddToViewport();
		}
		ServerStartInteract();
	}
}

void ARitualPlayerController::StopInteract()
{
	if (InteractionBar && InteractionBar->IsInViewport())
	{
		InteractionBar->RemoveFromViewport();
	}
	bIsInteracting = false;
	InteractedActor = nullptr;
	InteractionTime = 0;
	ServerStopInteract();
}

void ARitualPlayerController::InterruptInteract_Implementation()
{
	if (InteractionBar && InteractionBar->IsInViewport())
	{
		InteractionBar->RemoveFromViewport();
	}
	bIsInteracting = false;
	InteractedActor = nullptr;
	InteractionTime = 0;
}
