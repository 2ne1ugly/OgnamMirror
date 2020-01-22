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
	GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat(), ECollisionChannel::ECC_Pawn, Shape);
	for (FOverlapResult& Result : Overlaps)
	{
		ACharacter* Character = Cast<ACharacter>(Result.Actor);
		if (!Character || Affected.Contains(Character))
		{
			continue;
		}
		if (UOgnamStatics::CanDamage(GetWorld(), GetInstigator(), Character, EDamageMethod::DamagesEnemy))
		{
			UGameplayStatics::ApplyDamage(Character, 75.f, GetInstigatorController(), this, nullptr);
			if (Character->GetMesh()->IsSimulatingPhysics())
			{
				Character->GetMesh()->AddImpulse(FVector::UpVector * 50000.f);
			}
			else if (HasAuthority())
			{
				Character->GetCharacterMovement()->AddImpulse(FVector::UpVector * 100000.f);
			}
			Affected.Add(Character);
		}
	}
}
