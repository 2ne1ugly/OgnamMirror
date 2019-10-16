// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundImpactShotgunAction.h"
#include "Ognam/OgnamCharacter.h"
#include "DrawDebugHelpers.h"

UBloodhoundImpactShotgunAction::UBloodhoundImpactShotgunAction()
{
	PreDelayDuration = .0f;
	ChannelDuration = .0f;
	PostDelayDuration = .3f;

	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;

	NumPellets = 16;
	Spread = PI / 8.f;
}

void UBloodhoundImpactShotgunAction::EndChannel()
{
	if (!Target->HasAuthority())
	{
		return;
	}

	FVector From = Target->GetActorLocation();
	FVector To;
	FVector Direction = Target->GetActorForwardVector();
	for (int i = 0; i < NumPellets; i++)
	{
		float RandAngle = FMath::RandRange(0.f, PI * 2.f);
		float RandSpread = FMath::Tan(FMath::RandRange(0.f, Spread));
		FVector BulletDirection = FVector(1, FMath::Cos(RandAngle) * RandSpread, FMath::Sin(RandAngle) * RandSpread).GetSafeNormal();
		To = From + Direction.Rotation().RotateVector(BulletDirection) * 500.f;
		NetDrawTrajectory(From, To);
	}

	Target->LaunchCharacter(-GetOwner()->GetActorForwardVector() * 1000.f, false, true);
}

void UBloodhoundImpactShotgunAction::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	DrawDebugLine(GetWorld(), From, To, FColor::Red, false, .5f);
}
