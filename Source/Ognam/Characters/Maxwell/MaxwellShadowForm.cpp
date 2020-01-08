// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellShadowForm.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"

UMaxwellShadowForm::UMaxwellShadowForm()
{
	SetStatusEffect({ EStatusEffect::Unarmed, EStatusEffect::Silenced, EStatusEffect::Unbreakable });
	Duration = .4f;

	static ConstructorHelpers::FObjectFinder<USoundCue> ShiftSoundCueObject(TEXT("SoundCue'/Game/Sounds/Maxwell/Maxwell_dash_Cue.Maxwell_dash_Cue'"));
	ShiftSoundCue = ShiftSoundCueObject.Object;
}

void UMaxwellShadowForm::TickModifier(float DeltaTime)
{
	Target->Acceleration += Target->BaseAcceleration * 1;
	Target->Speed += Target->BaseSpeed * 1;
}

void UMaxwellShadowForm::BeginModifier()
{
	Super::BeginModifier();
	Target->GetCharacterMovement()->Velocity.Z = 0.f;
	Target->GetCharacterMovement()->MovementMode = MOVE_Falling;
	ShiftSound = NewObject<UAudioComponent>(Target);
	ShiftSound->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	ShiftSound->SetRelativeLocation(FVector::ZeroVector);
	ShiftSound->SetAutoActivate(false);
	ShiftSound->SetSound(ShiftSoundCue);
	ShiftSound->Activate();
	ShiftSound->bAutoDestroy = true;
	ShiftSound->RegisterComponent();
}
