// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundImpactShotgunAction.h"
#include "Ognam/OgnamCharacter.h"
#include "DrawDebugHelpers.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamPlayerstate.h"

UBloodhoundImpactShotgunAction::UBloodhoundImpactShotgunAction()
{
	PreDelayDuration = .0f;
	ChannelDuration = .0f;
	PostDelayDuration = .3f;

	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;

	NumPellets = 16;
	Spread = PI / 16.f;
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

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Target);

	TArray<FVector> Tos;
	TMap<AOgnamCharacter*, float> Damage;
	for (int i = 0; i < NumPellets; i++)
	{
		float RandAngle = FMath::RandRange(0.f, PI * 2.f);
		float RandSpread = FMath::Tan(FMath::RandRange(0.f, Spread));
		FVector BulletDirection = FVector(1, FMath::Cos(RandAngle) * RandSpread, FMath::Sin(RandAngle) * RandSpread).GetSafeNormal();
		To = From + Direction.Rotation().RotateVector(BulletDirection) * 700.f;

		FHitResult BulletHit;
		GetWorld()->LineTraceSingleByChannel(BulletHit, From, To, ECollisionChannel::ECC_GameTraceChannel1, Params);
		Tos.Add((BulletHit.bBlockingHit ? BulletHit.ImpactPoint : BulletHit.TraceEnd));

		//Calculate Damaging
		AOgnamCharacter* OtherCharacter = Cast<AOgnamCharacter>(BulletHit.Actor);
		if (!OtherCharacter)
		{
			continue;
		}
		AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
		AOgnamPlayerState* PlayerState = Target->GetPlayerState<AOgnamPlayerState>();
		if (!OtherPlayerState || !PlayerState || OtherPlayerState->GetTeam() == PlayerState->GetTeam())
		{
			continue ;
		}
		Damage.FindOrAdd(OtherCharacter) += 7.f;
	}
	NetDrawTrajectory(From, Tos);

	for (const TPair<AOgnamCharacter*, float>& Pair : Damage)
	{
		UGameplayStatics::ApplyDamage(Pair.Key, Pair.Value, Target->GetController(), Target, nullptr);
	}

	//Pushback
	Target->LaunchCharacter(-GetOwner()->GetActorForwardVector() * 800.f, false, true);
}

void UBloodhoundImpactShotgunAction::NetDrawTrajectory_Implementation(FVector From, const TArray<FVector>& Tos)
{
	for (int i = 0; i < Tos.Num(); i++)
	{
		DrawDebugLine(GetWorld(), From, Tos[i], FColor::Red, false, .5f);
	}
}
