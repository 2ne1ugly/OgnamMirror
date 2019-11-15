// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualShrine.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "RitualPlayerState.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"
#include "SceneView.h"

// Sets default values
ARitualShrine::ARitualShrine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetStaticMesh(Mesh.Object);
	StaticMesh->SetMobility(EComponentMobility::Static);
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh->SetWorldScale3D(FVector(1, 1, 5));
	StaticMesh->SetupAttachment(RootComponent);

	RootComponent = StaticMesh;

	CaptureField = CreateDefaultSubobject<UBoxComponent>(TEXT("Capture Point"));
	CaptureField->SetupAttachment(RootComponent);
	CaptureField->SetRelativeLocation(FVector::ZeroVector);
	CaptureField->SetCollisionProfileName(TEXT("Trigger"));
	CaptureField->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	CaptureField->bHiddenInGame = false;
	CaptureField->OnComponentBeginOverlap.AddDynamic(this, &ARitualShrine::OnEnterField);
	CaptureField->OnComponentEndOverlap.AddDynamic(this, &ARitualShrine::OnExitField);

	//bReplicates = true;

	CaptureDuration = 20.f;
	SpeedMultiplier = .15f;

	ShrineName = FText::FromString("Default");
}

void ARitualShrine::BeginPlay()
{
	Super::BeginPlay();
	CaptureProgress = 0.f;
}

void ARitualShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackerCount = 0;
	DefenderCount = 0;

	for (AOgnamPlayerState* State : Attackers)
	{
		if (State->IsAlive())
		{
			AttackerCount++;
		}
	}

	for (AOgnamPlayerState* State : Defenders)
	{
		if (State->IsAlive())
		{
			DefenderCount++;
		}
	}

	if (AttackerCount > DefenderCount)
	{
		CaptureProgress += DeltaTime + (AttackerCount - DefenderCount - 1) * DeltaTime * SpeedMultiplier;
	}
	else if (AttackerCount < DefenderCount && CaptureProgress > 0)
	{
		CaptureProgress -= DeltaTime + (DefenderCount - AttackerCount - 1) * DeltaTime * SpeedMultiplier;
	}
	else if (AttackerCount == 0 && DefenderCount == 0 && CaptureProgress > 0)
	{
		CaptureProgress -= DeltaTime;
	}
}

void ARitualShrine::Reset()
{
	Super::Reset();
	Attackers.Empty();
	Defenders.Empty();
	AttackerCount = 0;
	DefenderCount = 0;
	CaptureProgress = 0;
	//NetReset();
}

void ARitualShrine::NetReset_Implementation()
{
}

void ARitualShrine::OnEnterField(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);

	if (!Character)
		return;

	ARitualPlayerState* PlayerState = Character->GetPlayerState<ARitualPlayerState>();

	if (!PlayerState)
		return;

	if (PlayerState->GetSide() == TEXT("Offense"))
	{
		Attackers.Add(PlayerState);
	}
	if (PlayerState->GetSide() == TEXT("Defense"))
	{
		Defenders.Add(PlayerState);
	}
}

void ARitualShrine::OnExitField(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);

	if (!Character)
		return;

	ARitualPlayerState* PlayerState = Character->GetPlayerState<ARitualPlayerState>();

	if (!PlayerState)
		return;

	if (PlayerState->GetSide() == TEXT("Offense"))
	{
		Attackers.Remove(PlayerState);
	}
	if (PlayerState->GetSide() == TEXT("Defense"))
	{
		Defenders.Remove(PlayerState);
	}
}

bool ARitualShrine::ShouldRoundEnd() const
{
	return (CaptureProgress >= CaptureDuration);
}

bool ARitualShrine::IsBeingCaptured() const
{
	return GetProgressPercent() > 0 || AttackerCount > DefenderCount;
}

FVector4 ARitualShrine::GetScreenPosistion()
{
	FSceneView::WorldToScreen(GetActorLocation());
	return FVector4();
}

float ARitualShrine::GetProgressPercent() const
{
	return CaptureProgress / CaptureDuration;
}

