// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraRadiantDiveDropPoint.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Ognam/OgnamMacro.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

// Sets default values
AJeraRadiantDiveDropPoint::AJeraRadiantDiveDropPoint()
{
	InitialLifeSpan = 3.f;
	PlaceHolder = CreateDefaultSubobject<USphereComponent>(TEXT("Place Holder"));
	PlaceHolder->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//PlaceHolder->bHiddenInGame = false;
	RootComponent = PlaceHolder;

	static ConstructorHelpers::FObjectFinder<USoundCue> LandingSoundCue(TEXT("SoundCue'/Game/Sounds/Jera/Jera_Land_Cue.Jera_Land_Cue'"));
	LandingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Landing Sound"));
	LandingSound->SetSound(LandingSoundCue.Object);
	LandingSound->SetupAttachment(RootComponent);
	LandingSound->SetRelativeLocation(FVector::ZeroVector);
	LandingSound->SetAutoActivate(false);
}

void AJeraRadiantDiveDropPoint::BeginPlay()
{
	Super::BeginPlay();

	LandingSound->Activate();

	//Test Overlaps.
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Shape;
	Shape.SetSphere(300.f);

	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn); 
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat(), Params, Shape);
	for (FOverlapResult& Result : Overlaps)
	{
		ACharacter* Character = Cast<ACharacter>(Result.Actor);
		IKillable* Killable = Cast<IKillable>(Result.Actor);
		if (!Killable || Affected.Contains(Killable))
		{
			continue;
		}
		if (Killable)
		{
			if (UOgnamStatics::CanDamage(GetWorld(), GetInstigator(), Killable, EDamageMethod::DamagesEnemy))
			{
				AActor* KillableActor = Cast<AActor>(Killable);
				UGameplayStatics::ApplyDamage(KillableActor, 75.f, GetInstigatorController(), this, nullptr);
				if (Character)
				{
					if (Character->GetMesh()->IsSimulatingPhysics())
					{
						Character->GetMesh()->AddImpulse(FVector::UpVector * 50000.f);
					}
					else if (HasAuthority())
					{
						Character->GetCharacterMovement()->AddImpulse(FVector::UpVector * 100000.f);
					}
				}
				Affected.Add(Killable);
			}
		}
	}
}
