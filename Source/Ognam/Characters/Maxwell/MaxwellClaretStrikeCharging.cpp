// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellClaretStrikeCharging.h"
#include "MaxwellClaretStrikeCharged.h"
#include "MaxwellAimDowned.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "GameFramework/PlayerController.h"

UMaxwellClaretStrikeCharging::UMaxwellClaretStrikeCharging()
{
	StatusEffect |= EStatusEffect::Unarmed;
	Duration = 1.f;

	ConstructorHelpers::FObjectFinder<USoundCue> SoundCueStart(TEXT("SoundCue'/Game/Sounds/Maxwell/maxwell_charge_start_Cue.maxwell_charge_start_Cue'"));
	ChargeSoundCueStart = SoundCueStart.Object;

	ConstructorHelpers::FObjectFinder<USoundCue> SoundCueEnd(TEXT("SoundCue'/Game/Sounds/Maxwell/maxwell_charge_end_Cue.maxwell_charge_end_Cue'"));
	ChargeSoundCueEnd = SoundCueEnd.Object;
}

bool UMaxwellClaretStrikeCharging::ShouldEnd()
{
	return !Target->GetModifier<UMaxwellAimDowned>() || Super::ShouldEnd();
}

void UMaxwellClaretStrikeCharging::EndModifier()
{
	if (!Target->GetModifier<UMaxwellAimDowned>() || !Target->HasAuthority())
	{
		return;
	}
	APlayerController *Controller = Cast<APlayerController>(Target->GetController());
	if (!Controller)
	{
		return;
	}
	Controller->ClientPlaySound(ChargeSoundCueStart, 25.f, 1.f);
	NewObject<UMaxwellClaretStrikeCharged>(Target)->RegisterComponent();
}

void UMaxwellClaretStrikeCharging::BeginModifier()
{
	Super::BeginModifier();

	APlayerController *Controller = Cast<APlayerController>(Target->GetController());
	if (!Controller)
	{
		return;
	}
	Controller->ClientPlaySound(ChargeSoundCueStart, 25.f, 1.f);
}
