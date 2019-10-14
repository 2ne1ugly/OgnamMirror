// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraSuppressiveImpactAction.h"
#include "Ognam/OgnamCharacter.h"
#include "JeraCrystalSpear.h"
#include "Engine/World.h"

UJeraSuppressiveImpactAction::UJeraSuppressiveImpactAction()
{
	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;

	PreDelayDuration = .3f;
	ChannelDuration = .0f;
	PostDelayDuration = .2f;
}

void UJeraSuppressiveImpactAction::EndChannel()
{
	Super::EndModifier();
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
	GetWorld()->SpawnActor<AJeraCrystalSpear>(From, Direction.Rotation(), Params)->SetReplicates(true);
}
