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
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AHereiraExplosiveArrow::AHereiraExplosiveArrow()
{
	ConstructorHelpers::FObjectFinder<UParticleSystem> Emitter(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Emitter"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->SetRelativeLocation(FVector::ZeroVector);
	ParticleSystem->SetTemplate(Emitter.Object);
	ParticleSystem->bAutoActivate = false;
	ParticleSystem->SetHiddenInGame(false);

	ConstructorHelpers::FObjectFinder<USoundCue> SparkFizzleCue(TEXT("SoundCue'/Game/Sounds/Arrow/SparkFizzle_Cue.SparkFizzle_Cue'"));

	AudioSystem = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSystem"));
	AudioSystem->SetupAttachment(RootComponent);
	AudioSystem->SetupAttachment(RootComponent);
	AudioSystem->SetRelativeLocation(FVector::ZeroVector);
	AudioSystem->SetSound(SparkFizzleCue.Object);
	AudioSystem->bAutoActivate = false;
}

void AHereiraExplosiveArrow::BeginPlay()
{
	Super::BeginPlay();
	AudioSystem->Activate();
	ParticleSystem->Activate();
}

void AHereiraExplosiveArrow::EndLifeSpan()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	AHereiraExplosion* Explosion = GetWorld()->SpawnActor<AHereiraExplosion>(GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	Explosion->SetReplicates(true);
	Destroy();
}

void AHereiraExplosiveArrow::OnCharacterHit(AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}
	if (!bIsTraveling)
	{
		return;
	}


	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
		FVector Acceleration = Gravity * FVector::DownVector;
		FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

		UGameplayStatics::ApplyPointDamage(OtherCharacter, 30, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);
		UHereiraWillExplode* Explosion = NewObject<UHereiraWillExplode>(this);
		Explosion->SetInstigator(Instigator);
		OtherCharacter->ApplyModifier(Explosion);

		//Apply Fast reload if close range
		FVector Disposition = InitialVelocity * ElapsedTime + Acceleration * .5f * ElapsedTime * ElapsedTime;
		if (Disposition.Size() < 700.f)
		{
			AOgnamCharacter* Character = Cast<AOgnamCharacter>(Instigator);
			if (Character != nullptr)
			{
				if (Character->GetModifier<UHereiraCanFastReload>() == nullptr)
				{
					Character->ApplyModifier(NewObject<UHereiraCanFastReload>(this));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Not Ognam Character"), __FUNCTIONW__);
			}
		}
	}
	Destroy();
}

void AHereiraExplosiveArrow::OnActorHit(AActor* OtherCharacter, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AController* Controller = Instigator->GetController();
	float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
	FVector Acceleration = Gravity * FVector::DownVector;
	FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

	UGameplayStatics::ApplyPointDamage(OtherCharacter, 45, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraExplosiveArrow::EndLifeSpan, 0.5f, false);
}
