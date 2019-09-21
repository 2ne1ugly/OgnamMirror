// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraThrowMolotov.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "HereiraMolotov.h"
#include "Camera/CameraComponent.h"

UHereiraThrowMolotov::UHereiraThrowMolotov()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 1.f;
}

bool UHereiraThrowMolotov::ShouldShowNumber() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(MolotovCooldown);
}

float UHereiraThrowMolotov::GetNumber() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(MolotovCooldown);
}

void UHereiraThrowMolotov::OnButtonPressed()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(MolotovCooldown))
	{
		return;
	}
	ServerThrowMolotov();
}

void UHereiraThrowMolotov::ServerThrowMolotov_Implementation()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(MolotovCooldown))
	{
		return;
	}
	float UpRatio = 0.1f;
	FVector Direction = Target->Camera->GetForwardVector().GetSafeNormal();
	FVector MolotovDirection = UpRatio * FVector::UpVector + (1 - UpRatio) * Direction;

	FActorSpawnParameters SpawnParam;
	SpawnParam.bNoFail = true;
	SpawnParam.Instigator = Target;
	AHereiraMolotov* Molotov = GetWorld()->SpawnActor<AHereiraMolotov>(Target->GetActorLocation(), MolotovDirection.Rotation(), SpawnParam);
	Molotov->SetReplicates(true);
	Target->GetWorldTimerManager().SetTimer(MolotovCooldown, Cooldown, false);
	ClientFeedbackThrowMolotov();
}

void UHereiraThrowMolotov::ClientFeedbackThrowMolotov_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(MolotovCooldown, Cooldown, false);
}
