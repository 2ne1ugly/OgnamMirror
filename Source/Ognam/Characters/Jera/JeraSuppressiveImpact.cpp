// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraSuppressiveImpact.h"
#include "JeraSuppressiveImpactAction.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

UJeraSuppressiveImpact::UJeraSuppressiveImpact()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 4.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Jera/icicle_throw.icicle_throw'"));
	Icon = IconTexture.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> BuildupSoundFinder(TEXT("SoundCue'/Game/Sounds/Jera/ice_forming_Cue.ice_forming_Cue'"));
	BuildupSound = BuildupSoundFinder.Object;
}

void UJeraSuppressiveImpact::ActivateAbility()
{
	NewObject<UJeraSuppressiveImpactAction>(Target)->RegisterComponent();

	UAudioComponent* IceForming = NewObject<UAudioComponent>(Target);
	IceForming->SetupAttachment(Target->GetRootComponent());
	IceForming->SetRelativeLocation(FVector::ZeroVector);
	IceForming->SetAutoActivate(false);
	IceForming->SetSound(BuildupSound);
	IceForming->Activate();
	IceForming->bAutoDestroy = true;
	IceForming->RegisterComponent();
}
