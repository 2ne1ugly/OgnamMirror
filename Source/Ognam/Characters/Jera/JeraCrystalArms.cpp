// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraCrystalArms.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "JeraCrystalShard.h"
#include "JeraCrystalArmsAction.h"

UJeraCrystalArms::UJeraCrystalArms()
{
	WeaponActionClass = UJeraCrystalArmsAction::StaticClass();
	bInfiniteAmmo = true;

	bBindSub = true;

	MaxShardCharge = 2;
	ShardCharge = MaxShardCharge;
	ChargePeriod = 1.f;
}

void UJeraCrystalArms::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJeraCrystalArms, ShardCharge);
}

void UJeraCrystalArms::SubPressed()
{
	if (ShardCharge <= 0 || WeaponAction->IsRunning())
	{
		return;
	}
	ServerSubPressed();
}

void UJeraCrystalArms::ServerSubPressed_Implementation()
{
	if (ShardCharge <= 0 || WeaponAction->IsRunning())
	{
		return;
	}
	ShardCharge--;
	if (!GetWorld()->GetTimerManager().IsTimerActive(ShardChargeTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(ShardChargeTimer, this, &UJeraCrystalArms::ChargeShard, ChargePeriod, false);
	}
	FireShard();
}

void UJeraCrystalArms::ChargeShard()
{
	ShardCharge++;
	if (ShardCharge >= MaxShardCharge)
	{
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(ShardChargeTimer, this, &UJeraCrystalArms::ChargeShard, ChargePeriod, false);
}

void UJeraCrystalArms::FireShard()
{
	//Thinking of making this into an action.
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
	GetWorld()->SpawnActor<AJeraCrystalShard>(From, Direction.Rotation(), Params)->SetReplicates(true);
}
