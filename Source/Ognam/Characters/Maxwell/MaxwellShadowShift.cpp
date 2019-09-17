// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellShadowShift.h"
#include "MaxwellShadowForm.h"
#include "Ognam/OgnamCharacter.h"
#include "TimerManager.h"

UMaxwellShadowShift::UMaxwellShadowShift()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 3.5f;
}

void UMaxwellShadowShift::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ShadowShiftCooldown))
	{
		return;
	}
	ServerCastShadowShift(Target->GetLastMovementInputVector().GetSafeNormal());
}

void UMaxwellShadowShift::ServerCastShadowShift_Implementation(FVector Direction)
{
	if (Target->GetWorldTimerManager().IsTimerActive(ShadowShiftCooldown))
	{
		return;
	}
	UMaxwellShadowForm* ShadowForm = NewObject<UMaxwellShadowForm>(Target);
	ShadowForm->SetDirection(Direction);
	ShadowForm->RegisterComponent();
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
