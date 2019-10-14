// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerController.h"
#include "RitualGameState.h"
#include "RitualPlayerState.h"
#include "RitualGameMode.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Ognam/OgnamCharacter.h"
#include "Interfaces/Interactable.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "Camera/CameraActor.h"
#include "Ognam/OgnamMacro.h"

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
		if (InteractionBarClass)
		{
			InteractionBar = CreateWidget<UUserWidget>(this, InteractionBarClass);
		}
		return;
	}
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
			O_LOG(TEXT("Not Interactable"));
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

void ARitualPlayerController::ServerChangeCharacter_Implementation(UClass* CharacterClass)
{
	//Set pawn class
	ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(PlayerState);
	RitualPlayerState->SetSelectedPawnClass(CharacterClass);
}

void ARitualPlayerController::ShowCharacterSelection()
{
	if (IsLocalPlayerController())
	{
		if (!CharacterSelectionHUD && CharacterSelectionHUDClass)
		{
			CharacterSelectionHUD = CreateWidget<UUserWidget>(this, CharacterSelectionHUDClass);
		}
	}
	if (CharacterSelectionHUD)
	{
		CharacterSelectionHUD->AddToViewport();
	}
	if (GetPawn())
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

void ARitualPlayerController::HideCharacterSelection()
{
	if (CharacterSelectionHUD)
	{
		CharacterSelectionHUD->RemoveFromViewport();
	}
	if (GetPawn())
	{
		AOgnamCharacter* Character = Cast<AOgnamCharacter>(GetCharacter());
		// This is a placeholder to prevent cheating
		// We need a spectator to actually prevent real life cheating involving code changes
		if (Character && Character->IsAlive())
		{
			GetPawn()->EnableInput(this);
		}
	}
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
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

void ARitualPlayerController::PreRoundBegin_Implementation()
{
	ShowCharacterSelection();
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(GetCharacter());
	if (Character)
	{
		Character->SetCanMove(false);
		Character->DisableInput(this);
	}
}

void ARitualPlayerController::PreRoundEnd_Implementation()
{
	HideCharacterSelection();
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(GetCharacter());
	if (Character)
	{
		Character->SetCanMove(true);
		Character->EnableInput(this);
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

bool ARitualPlayerController::IsInteracting() const
{
	return bIsInteracting;
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
	float Distance = FVector::Dist(GetPawn()->GetActorLocation(), Actor->GetActorLocation());
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

float ARitualPlayerController::GetInteractionProgress() const
{
	IInteractable* Interactable = Cast<IInteractable>(InteractedActor);
	if (Interactable == nullptr)
	{
		return 0.0f;
	}
	return InteractionTime / Interactable->GetInteractDuration();
}
