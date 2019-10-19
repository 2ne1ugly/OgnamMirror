// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraMolotovEmber.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraMolotovBurning.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AHereiraMolotovEmber::AHereiraMolotovEmber()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetSphereRadius(5.f);
	//Collision->bHiddenInGame = false;
	RootComponent = Collision;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Tirgger"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(FVector::ZeroVector);
	Trigger->SetSphereRadius(64.f);
	//Trigger->bHiddenInGame = false;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHereiraMolotovEmber::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AHereiraMolotovEmber::EndOverlap);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 700.f;
	Movement->ProjectileGravityScale = 1.5f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Flame(TEXT("ParticleSystem'/Game/StarterContent/Particles/Fire.Fire'"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Flame"));
	ParticleSystem->SetTemplate(Flame.Object);
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->SetRelativeLocation(FVector::ZeroVector);

	//static ConstructorHelpers::FObjectFinder<USoundCue> GlassBreak(TEXT("SoundCue'/Game/Sounds/Hereira/molotov_break_Cue.molotov_break_Cue'"));
	//BreakingAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("GlassAudioComponent"));
	//BreakingAudio->SetSound(GlassBreak.Object);
	//BreakingAudio->SetupAttachment(RootComponent);
	//BreakingAudio->SetRelativeLocation(FVector::ZeroVector);
	//BreakingAudio->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundCue> Burning(TEXT("SoundCue'/Game/StarterContent/Audio/Fire01_Cue.Fire01_Cue'"));
	BurningAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BurningAudioComponent"));
	BurningAudio->SetSound(Burning.Object);
	BurningAudio->SetupAttachment(RootComponent);
	BurningAudio->SetRelativeLocation(FVector::ZeroVector);
	BurningAudio->bAutoActivate = false;

	InitialLifeSpan = 7.f;
}

void AHereiraMolotovEmber::BeginPlay()
{
	Super::BeginPlay();

	BurningAudio->Play();
	//BreakingAudio->Play();
}

void AHereiraMolotovEmber::Tick(float DeltaTime)
{
	if (HasAuthority())
	{
		for (AOgnamCharacter* Character : AffectedCharacters)
		{
			if (Character->IsValidLowLevel())
			{
				UHereiraMolotovBurning* Modifier = Character->GetModifier<UHereiraMolotovBurning>();
				if (!Modifier)
				{
					Modifier = NewObject<UHereiraMolotovBurning>(Character);
					Modifier->UpdateTimeStamp();
					Modifier->RegisterComponent();
				}
				else
				{
					Modifier->ResetDuration();
				}
				Modifier->SetInstigator(Instigator);
			}
		}
	}
}

void AHereiraMolotovEmber::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (!Character)
	{
		return;
	}
	AffectedCharacters.Add(Character);
}

void AHereiraMolotovEmber::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (!Character)
	{
		return;
	}
	AffectedCharacters.Remove(Character);
}


