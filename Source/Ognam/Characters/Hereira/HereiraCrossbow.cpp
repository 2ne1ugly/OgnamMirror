// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCrossbow.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "HereiraExplosiveShotReady.h"
#include "HereiraArrow.h"
#include "HereiraExplosiveArrow.h"
#include "Engine/World.h"

UHereiraCrossbow::UHereiraCrossbow()
{
	MaxAmmo = 2;
	Ammo = MaxAmmo;
	RoundsPerSecond = 2.f;
	ReloadTime = 1.5f;
}

void UHereiraCrossbow::FireBullet()
{
	float UpRatio = 0.1f;
	FVector Direction = Target->Camera->GetForwardVector() * (1 - UpRatio) + FVector::UpVector * UpRatio;
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();

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
