// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraSuppressiveImpactBackSwing.h"
#include "Ognam/OgnamCharacter.h"
#include "JeraCrystalSpear.h"
#include "Engine/World.h"

UJeraSuppressiveImpactBackSwing::UJeraSuppressiveImpactBackSwing()
{
	StatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;
	Duration = .75f;
}

void UJeraSuppressiveImpactBackSwing::EndModifier()
{
	Super::EndModifier();
	if (!Target->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetActorLocation();
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
