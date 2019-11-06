// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraThrowMolotov.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "HereiraMolotov.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"

UHereiraThrowMolotov::UHereiraThrowMolotov()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 10.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Hereira/Molotov.Molotov'"));
	Icon = IconTexture.Object;
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
