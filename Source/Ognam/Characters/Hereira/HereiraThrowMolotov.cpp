// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraThrowMolotov.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "HereiraMolotov.h"
#include "Camera/CameraComponent.h"

UHereiraThrowMolotov::UHereiraThrowMolotov()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 10.f;
}

void UHereiraThrowMolotov::ActivateAbility()
{
	Target->TakeAction(EActionType::Focus);

	float UpRatio = 0.1f;
	FVector Direction = Target->Camera->GetForwardVector().GetSafeNormal();
	FVector MolotovDirection = UpRatio * FVector::UpVector + (1 - UpRatio) * Direction;

	FActorSpawnParameters SpawnParam;
	SpawnParam.bNoFail = true;
	SpawnParam.Instigator = Target;
	AHereiraMolotov* Molotov = GetWorld()->SpawnActor<AHereiraMolotov>(Target->GetActorLocation(), MolotovDirection.Rotation(), SpawnParam);
	Molotov->SetReplicates(true);
}
