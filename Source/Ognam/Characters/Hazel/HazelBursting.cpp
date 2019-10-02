// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelBursting.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"
#include "HazelFireball.h"
UHazelBursting::UHazelBursting()
{
	TotalCount = 15;
	Count = TotalCount;
	Duration = 1.f;
	StatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

bool UHazelBursting::ShouldEnd()
{
	return Count <= 0;
}

void UHazelBursting::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(ReleaseTimer, this, &UHazelBursting::ReleaseFireBall, Duration / (TotalCount - 1), false);
}

void UHazelBursting::ReleaseFireBall()
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

	Count--;
	if (Count > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ReleaseTimer, this, &UHazelBursting::ReleaseFireBall, Duration / (TotalCount - 1), false);
	}
}
