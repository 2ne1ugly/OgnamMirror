// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellVaultModifier.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

UMaxwellVaultModifier::UMaxwellVaultModifier()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> VaultCueFinder(TEXT("SoundCue'/Game/Sounds/Maxwell/Maxwell_jump_Cue.Maxwell_jump_Cue'"));
	VaultCue = VaultCueFinder.Object;
}

void UMaxwellVaultModifier::BeginModifier()
{
	Super::BeginModifier();

	UAudioComponent* JumpAudio = NewObject<UAudioComponent>(Target);
	JumpAudio->SetupAttachment(Target->GetRootComponent());
	JumpAudio->SetRelativeLocation(FVector::ZeroVector);
	JumpAudio->SetAutoActivate(false);
	JumpAudio->SetSound(VaultCue);
	JumpAudio->Activate();
	JumpAudio->bAutoDestroy = true;
	JumpAudio->RegisterComponent();
}

bool UMaxwellVaultModifier::ShouldEnd()
{
	return bInterrupt || (!Target->GetCharacterMovement()->IsFalling() && Target->GetVelocity().Z <= 0);
}

void UMaxwellVaultModifier::TickModifier(float DeltaTime)
{
	Target->Gravity += Target->BaseGravity;
	Target->AirControl += Target->BaseAirControl * 3;
}

void UMaxwellVaultModifier::StatusEffectApplied(EStatusEffect AppliedStatusEffect)
{
}

void UMaxwellVaultModifier::ActionTaken(EActionNotifier ActionType)
{
	if ((ActionType & EActionNotifier::SpecialMovement) != EActionNotifier::None)
	{
		bInterrupt = true;
	}
}
