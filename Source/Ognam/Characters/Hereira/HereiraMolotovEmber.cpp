// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraMolotovEmber.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraMolotovBurning.h"

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

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Flame(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire_2.P_Fire_2'"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Flame"));
	ParticleSystem->SetTemplate(Flame.Object);
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->SetRelativeLocation(FVector::ZeroVector);

	InitialLifeSpan = 7.f;
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


