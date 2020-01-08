// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellShadowShift.h"
#include "MaxwellShadowForm.h"
#include "Ognam/OgnamCharacter.h"
#include "TimerManager.h"
#include "ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Components/SkeletalMeshComponent.h"

UMaxwellShadowShift::UMaxwellShadowShift()
{
	AbilityType = EAbilityType::Mobility;
	//Cooldown = 7.f;
	Cooldown = 4.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Maxwell/shadow_walk.shadow_walk'"));
	Icon = IconTexture.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RootMotionCH(TEXT("AnimMontage'/Game/Animation/Maxwell/Maxwell_Dash.Maxwell_Dash'"));
	RootMotion = RootMotionCH.Object;
}


void UMaxwellShadowShift::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ShadowShiftCooldown) ||
		Target->HasStatusEffect(EStatusEffect::Rooted) ||
		Target->HasStatusEffect(EStatusEffect::Silenced))
	{
		return;
	}
	ServerCastShadowShift(Target->GetLastMovementInputVector().GetSafeNormal());
}

void UMaxwellShadowShift::ServerCastShadowShift_Implementation(FVector Direction)
{
	if (Target->GetWorldTimerManager().IsTimerActive(ShadowShiftCooldown) ||
		Target->HasStatusEffect(EStatusEffect::Rooted) ||
		Target->HasStatusEffect(EStatusEffect::Silenced))
	{
		return;
	}
	Target->TakeAction(EActionNotifier::SpecialMovement);
	Target->PlayAnimMontage(RootMotion);
	//NewObject<UMaxwellShadowForm>(Target)->RegisterComponent();
	Target->GetWorldTimerManager().SetTimer(ShadowShiftCooldown, Cooldown, false);
	ClientFeedbackShadowShift();
}

void UMaxwellShadowShift::ClientFeedbackShadowShift_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(ShadowShiftCooldown, Cooldown, false);
}

bool UMaxwellShadowShift::ShouldShowNumber() const
{
	return Target->GetWorldTimerManager().IsTimerActive(ShadowShiftCooldown);
}

float UMaxwellShadowShift::GetNumber() const
{
	return Target->GetWorldTimerManager().GetTimerRemaining(ShadowShiftCooldown);
}
