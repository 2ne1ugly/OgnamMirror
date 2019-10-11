// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelPyromancyAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "HazelFireball.h"
#include "HazelBlazed.h"
#include "TimerManager.h"

UHazelPyromancyAction::UHazelPyromancyAction()
{
	float RoundsPerSecond = 4;

	PreDelayDuration = .0f;
	ChannelDuration = .0f;
	PostDelayDuration = 1.f / RoundsPerSecond;
}

void UHazelPyromancyAction::BeginChannel()
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
}

void UHazelPyromancyAction::TickPostDelay(float DeltaTime)
{
	Target->Speed *= 0.8f;
}

void UHazelPyromancyAction::ExecutePostDelay()
{
	Super::ExecutePostDelay();
	if (Target->GetModifier<UHazelBlazed>())
	{
		GetWorld()->GetTimerManager().SetTimer(PostDelayTimer, this, &UHazelPyromancyAction::FinishPostDelay, PostDelayDuration / 2.f, false);
	}
}

void UHazelPyromancyAction::StatusEffectApplied(EStatusEffect StatusEffect)
{
	if (Stage == EActionStage::PreDelay)
	{
		return;
	}
}

void UHazelPyromancyAction::ActionTaken(EActionNotifier ActionType)
{
	if (Stage == EActionStage::PreDelay)
	{
		return;
	}
	if ((ActionType & EActionNotifier::Death) != EActionNotifier::None)
	{
		Interrupt();
	}
}
