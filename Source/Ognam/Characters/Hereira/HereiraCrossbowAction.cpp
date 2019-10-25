// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "HereiraCrossbowAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "HereiraArrow.h"
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

	FVector Location = Target->GetActorLocation() + FVector(0.f, 0.f, 60.f);

	GetWorld()->SpawnActor<AHereiraArrow>(Location, Rotator, SpawnParameters)->SetReplicates(true);
}
