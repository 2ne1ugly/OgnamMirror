// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraCrystalArms.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "JeraCrystalShard.h"

UJeraCrystalArms::UJeraCrystalArms()
{
	TriggerClass = UStaticMeshComponent::StaticClass();
	PreSwing = .25f;
	PeriSwing = .25f;
	PostSwing = .45f;
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	DamageBoxMaterial = Material.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	DamageBoxMesh = Mesh.Object;

	bBindSub = true;

	MaxShardCharge = 2;
	ShardCharge = MaxShardCharge;
	ChargePeriod = 1.f;
}

void UJeraCrystalArms::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger = Cast<UStaticMeshComponent>(Trigger);
	BoxTrigger->bHiddenInGame = false;

	BoxTrigger->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	BoxTrigger->SetStaticMesh(DamageBoxMesh);
	BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	BoxTrigger->SetRelativeScale3D(FVector(2.5f));
	BoxTrigger->SetMaterial(0, DamageBoxMaterial);
	BoxTrigger->SetVisibility(false);
}

void UJeraCrystalArms::StartPeriSwing()
{
	Super::StartPeriSwing();
	NetStartPeriSwing();
}

void UJeraCrystalArms::StartPostSwing()
{
	Super::StartPostSwing();
}

void UJeraCrystalArms::NetStartPeriSwing_Implementation()
{
	BoxTrigger->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(BoxVisualizeTimer, this, &UJeraCrystalArms::EndPeriSwing, PeriSwing, false);
}

void UJeraCrystalArms::EndPeriSwing()
{
	BoxTrigger->SetVisibility(false);
}

void UJeraCrystalArms::CharacterStrike(AOgnamCharacter* OtherCharacter)
{
	UGameplayStatics::ApplyDamage(OtherCharacter, 40.f, Target->GetController(), Target, nullptr);
}

void UJeraCrystalArms::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJeraCrystalArms, ShardCharge);
}

void UJeraCrystalArms::SubPressed()
{
	if (ShardCharge <= 0)
	{
		return;
	}
	ServerSubPressed();
}

void UJeraCrystalArms::ServerSubPressed_Implementation()
{
	if (ShardCharge <= 0)
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