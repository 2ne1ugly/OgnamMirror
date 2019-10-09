// Fill out your copyright notice in the Description page of Project Settings.


#include "IsmaelLuxDetonator.h"
#include "Components/SphereComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "IsmaelFlashedModifier.h"

// Sets default values
AIsmaelLuxDetonator::AIsmaelLuxDetonator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Range = CreateDefaultSubobject<USphereComponent>(TEXT("Range"));
	Range->SetSphereRadius(1000);
	Range->bHiddenInGame = false;

	InitialLifeSpan = .1f;

	RootComponent = Range;
}

// Called when the game starts or when spawned
void AIsmaelLuxDetonator::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority())
	{
		return;
	}
	FCollisionShape Sphere;
	Sphere.SetSphere(1000);
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat(), ECollisionChannel::ECC_Pawn, Sphere);

	TSet<AOgnamCharacter*> Effected;
	for (FOverlapResult& Result : Overlaps)
	{
		AOgnamCharacter *Character = Cast<AOgnamCharacter>(Result.Actor);

		if (Character)
		{
			AOgnamPlayerState* PlayerState = Character->GetPlayerState<AOgnamPlayerState>();
			AOgnamPlayerState* InstigatorState = Instigator->GetPlayerState<AOgnamPlayerState>();
			if (PlayerState && PlayerState->GetTeam() != InstigatorState->GetTeam() && !Effected.Contains(Character))
			{
				Effected.Add(Character);
				FVector From = GetActorLocation();
				FVector To = Character->GetActorLocation();
				FVector Direction = To - From;
				float Theta = FMath::Acos(GetActorForwardVector() | Direction.GetSafeNormal());
				if (Theta > FMath::DegreesToRadians(75.f))
				{
					continue;
				}
				
				FHitResult Hit;
				if (GetWorld()->LineTraceSingleByChannel(Hit, From, To, ECollisionChannel::ECC_Camera))
				{
					continue;
				}

				float Dot = Character->Camera->GetForwardVector() | (-GetActorForwardVector());
				float Ang = FMath::Acos(Dot);
				if (Ang < FMath::DegreesToRadians(45.f))
				{
					UIsmaelFlashedModifier* Mod = NewObject<UIsmaelFlashedModifier>(Character);
					Mod->RegisterComponent();
				}
			}
		}
	}
}

// Called every frame
void AIsmaelLuxDetonator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

