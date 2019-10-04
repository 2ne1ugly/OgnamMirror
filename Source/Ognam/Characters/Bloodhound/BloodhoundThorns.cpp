// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundThorns.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "TimerManager.h"
#include "ConstructorHelpers.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABloodhoundThorns::ABloodhoundThorns()
{
	MaxThorns = 12;
	NumThorns = MaxThorns;
	Period = .1f;
	ThornLiveTime = .5f;
	ThornInterval = 100.f;

	StartingPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Starting Point"));
	StartingPoint->bHiddenInGame = false;
	RootComponent = StartingPoint;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	ThornMesh = Mesh.Object;
	InitialLifeSpan = Period * MaxThorns + ThornLiveTime;
}

void ABloodhoundThorns::BeginPlay()
{
	Super::BeginPlay();
	SpawnThorn();
	GetWorld()->GetTimerManager().SetTimer(RemoveTimer, this, &ABloodhoundThorns::RemoveThorn, ThornLiveTime, false);
}

void ABloodhoundThorns::SpawnThorn()
{
	ThornLocation += ThornInterval;

	UStaticMeshComponent* NewThorn = NewObject<UStaticMeshComponent>(this);
	NewThorn->SetStaticMesh(ThornMesh);

	NewThorn->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	NewThorn->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	NewThorn->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	NewThorn->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	NewThorn->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);

	NewThorn->SetRelativeLocation(FVector(1.f, 0.f, 0.f) * ThornLocation + FVector::UpVector * 1000.f);
	NewThorn->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	NewThorn->SetStaticMesh(ThornMesh);
	NewThorn->RegisterComponent();

	//Find a better way to deal with this issue.
	NewThorn->AddLocalOffset(FVector::DownVector * 2000.f, true);
	Thorns.Enqueue(NewThorn);

	NumThorns--;
	if (NumThorns > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(PeriodTimer, this, &ABloodhoundThorns::SpawnThorn, Period, false);
	}
}

void ABloodhoundThorns::RemoveThorn()
{
	if (Thorns.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Thorns remove wasn't proper"));
		return;
	}

	UStaticMeshComponent* NewThorn;
	Thorns.Dequeue(NewThorn);
	NewThorn->DestroyComponent();
	RemovedThorns++;
	if (RemovedThorns < MaxThorns)
	{
		GetWorld()->GetTimerManager().SetTimer(RemoveTimer, this, &ABloodhoundThorns::RemoveThorn, Period, false);
	}
}

