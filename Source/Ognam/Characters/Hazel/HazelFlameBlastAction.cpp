// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelFlameBlastAction.h"
#include "HazelFlamePillar.h"
#include "HazelEnhancedFlamePillar.h"
#include "HazelBlazed.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"

UHazelFlameBlastAction::UHazelFlameBlastAction()
{
	PreDelayDuration = 0.1f;
	PostDelayDuration = 0.25f;
	ChannelDuration = 0.f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UHazelFlameBlastAction::BeginChannel()
{
	FHitResult AimHit;
	Target->GetAimHitResult(AimHit, 0.f, 2000.f);
	FVector From;
	if (AimHit.bBlockingHit)
		From = AimHit.ImpactPoint;
	else
		From = AimHit.TraceEnd;

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FHitResult DropHit;
	GetWorld()->LineTraceSingleByObjectType(DropHit, From, From + FVector::DownVector * 10000.f, ObjectParams);


	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;

	if (Target->GetModifier<UHazelBlazed>())
	{
		GetWorld()->SpawnActor<AHazelEnhancedFlamePillar>(DropHit.Location, FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
	else
	{
		GetWorld()->SpawnActor<AHazelFlamePillar>(DropHit.Location, FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
}
