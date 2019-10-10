// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCrossbowAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "HereiraExplosiveShotReady.h"
#include "HereiraArrow.h"
#include "HereiraExplosiveArrow.h"
#include "Engine/World.h"

UHereiraCrossbowAction::UHereiraCrossbowAction()
{
	float RoundsPerSecond = 4.f;

	PreDelayDuration = 0.f;
	ChannelDuration = 0.f;
	PostDelayDuration = 1 / RoundsPerSecond;
}

void UHereiraCrossbowAction::BeginChannel()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	float UpRatio = 0.06f;
	FVector Direction = Target->Camera->GetForwardVector() * (1 - UpRatio) + FVector::UpVector * UpRatio;
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction.GetSafeNormal()).Rotator();

	//Set Spawner
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Instigator = Target;

	UHereiraExplosiveShotReady* ExplosiveReady = Target->GetModifier<UHereiraExplosiveShotReady>();
	FVector Location = Target->GetActorLocation() + FVector(0.f, 0.f, 60.f);

	AHereiraArrow* Arrow;
	if (ExplosiveReady && ExplosiveReady->Use())
	{
		Arrow = GetWorld()->SpawnActor<AHereiraExplosiveArrow>(Location, Rotator, SpawnParameters);
	}
	else
	{
		Arrow = GetWorld()->SpawnActor<AHereiraArrow>(Location, Rotator, SpawnParameters);
	}
	Arrow->SetReplicates(true);
}
