// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraExplosiveArrow.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HereiraExplosion.h"
#include "HereiraWillExplode.h"
#include "HereiraCanFastReload.h"
#include "ParticleDefinitions.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AHereiraExplosiveArrow::AHereiraExplosiveArrow()
{
	ConstructorHelpers::FObjectFinder<UParticleSystem> Emitter(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Emitter"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->SetRelativeLocation(FVector::ZeroVector);
	ParticleSystem->SetTemplate(Emitter.Object);
	ParticleSystem->bAutoActivate = true;

	Movement->OnProjectileStop.AddDynamic(this, &AHereiraExplosiveArrow::OnActorHit);

	ConstructorHelpers::FObjectFinder<USoundCue> SparkFizzleCue(TEXT("SoundCue'/Game/Sounds/Arrow/SparkFizzle_Cue.SparkFizzle_Cue'"));
	AudioSystem = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSystem"));
	AudioSystem->SetupAttachment(RootComponent);
	AudioSystem->SetRelativeLocation(FVector::ZeroVector);
	AudioSystem->SetSound(SparkFizzleCue.Object);
	AudioSystem->bAutoActivate = true;
}

void AHereiraExplosiveArrow::EndLifeSpan()
{
	if (!HasAuthority())
	{
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	AHereiraExplosion* Explosion = GetWorld()->SpawnActor<AHereiraExplosion>(GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	Explosion->SetReplicates(true);
	Destroy();
}

void AHereiraExplosiveArrow::OnCharacterHit(AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult)
{
	if (!HasAuthority() || OtherCharacter == Instigator)
	{
		return;
	}
	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		UGameplayStatics::ApplyPointDamage(OtherCharacter, 30, SweepResult.ImpactNormal, SweepResult, Controller, this, nullptr);
		ApplyWillExplode(OtherCharacter);
	}
	Destroy();
}

void AHereiraExplosiveArrow::OnActorHit(const FHitResult& ImpactResult)
{
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraExplosiveArrow::EndLifeSpan, .5f, false);
}

void AHereiraExplosiveArrow::ApplyWillExplode_Implementation(AOgnamCharacter* OtherCharacter)
{
	if (!OtherCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot apply will explode cuz it's nullptr"));
		return;
	}
	UHereiraWillExplode* Explosion = NewObject<UHereiraWillExplode>(this);
	Explosion->SetInstigator(Instigator);
	OtherCharacter->ApplyModifier(Explosion);
}
