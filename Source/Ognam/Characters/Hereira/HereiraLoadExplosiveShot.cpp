// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraLoadExplosiveShot.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraExplosiveShotReady.h"
#include "TimerManager.h"

UHereiraLoadExplosiveShot::UHereiraLoadExplosiveShot()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 5.f;
}

bool UHereiraLoadExplosiveShot::ShouldShowNumber() const
{
	return Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown);
}

float UHereiraLoadExplosiveShot::GetNumber() const
{
	return Target->GetWorldTimerManager().GetTimerRemaining(ExplosiveShotCooldown);
}


void UHereiraLoadExplosiveShot::FiredExplosiveShot()
{
	ClientFiredExplosiveShot();
}

void UHereiraLoadExplosiveShot::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		Target->GetModifier<UHereiraExplosiveShotReady>() != nullptr)
	{
		return;
	}
	ServerLoadExplosiveShot();
}

void UHereiraLoadExplosiveShot::ServerLoadExplosiveShot_Implementation()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		Target->GetModifier<UHereiraExplosiveShotReady>() != nullptr)
	{
		return;
	}
	UHereiraExplosiveShotReady* ExplosiveShot = NewObject<UHereiraExplosiveShotReady>(Target);
	ExplosiveShot->SetAbility(this);
	ExplosiveShot->RegisterComponent();
}

void UHereiraLoadExplosiveShot::ClientFiredExplosiveShot_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(ExplosiveShotCooldown, Cooldown, false);
}