// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelBurstAction.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"
#include "HazelFireball.h"

UHazelBurstAction::UHazelBurstAction()
{
	PreDelayDuration = 0.25f;
	PostDelayDuration = 0.f;

	ChannelDuration = 1.f;
	TotalCount = 15;
	Count = TotalCount;
	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UHazelBurstAction::ReleaseFireBall()
{
	if (!Target->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetActorLocation() + FVector(0.f, 0.f, 60.f);
	FVector To;
	if (Aim.bBlockingHit)
		To = Aim.ImpactPoint;
	else
		To = Aim.TraceEnd;

	FVector Direction = To - From;
	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AHazelFireball>(From, Direction.Rotation(), Params)->SetReplicates(true);

	//Check if this releases lower number of fire balls sometimes
	Count--;
	if (Count > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ReleaseTimer, this, &UHazelBurstAction::ReleaseFireBall, ChannelDuration / (TotalCount - 1), false);
	}
}

void UHazelBurstAction::BeginChannel()
{
	GetWorld()->GetTimerManager().SetTimer(ReleaseTimer, this, &UHazelBurstAction::ReleaseFireBall, ChannelDuration / (TotalCount - 1), false);
}
