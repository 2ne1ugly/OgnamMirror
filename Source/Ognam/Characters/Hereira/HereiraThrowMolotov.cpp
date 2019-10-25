// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	Target->TakeAction(EActionNotifier::Focus);

	float UpRatio = 0.1f;
	FVector Direction = Target->Camera->GetForwardVector().GetSafeNormal();
	FVector MolotovDirection = UpRatio * FVector::UpVector + (1 - UpRatio) * Direction;

	FActorSpawnParameters SpawnParam;
	SpawnParam.bNoFail = true;
	SpawnParam.Instigator = Target;
	AHereiraMolotov* Molotov = GetWorld()->SpawnActor<AHereiraMolotov>(Target->GetActorLocation(), MolotovDirection.Rotation(), SpawnParam);
	Molotov->SetInitialVelocity(Target->GetVelocity());
	Molotov->SetReplicates(true);
}
