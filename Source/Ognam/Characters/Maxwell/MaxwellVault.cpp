// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellVault.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellVaultModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

UMaxwellVault::UMaxwellVault()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 10.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Maxwell/Vault.Vault'"));
	Icon = IconTexture.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> VaultCueFinder(TEXT("SoundCue'/Game/Sounds/Maxwell/Maxwell_jump_Cue.Maxwell_jump_Cue'"));
	VaultCue = VaultCueFinder.Object;
}

void UMaxwellVault::ActivateAbility()
{
	float HorizontalRatio = 0.2f;
	FVector Direction = FVector::UpVector * (1 - HorizontalRatio) + Target->GetActorForwardVector() * HorizontalRatio;
	Target->LaunchCharacter(Direction * 2200.f, false, true);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMaxwellVault::ApplyModifier);
}

void UMaxwellVault::ApplyModifier()
{
	NewObject<UMaxwellVaultModifier>(Target)->RegisterComponent();

	UAudioComponent* JumpAudio = NewObject<UAudioComponent>(Target);
	JumpAudio->SetupAttachment(Target->GetRootComponent());
	JumpAudio->SetRelativeLocation(FVector::ZeroVector);
	JumpAudio->SetAutoActivate(false);
	JumpAudio->SetSound(VaultCue);
	JumpAudio->Activate();
	JumpAudio->bAutoDestroy = true;
	JumpAudio->RegisterComponent();
}
