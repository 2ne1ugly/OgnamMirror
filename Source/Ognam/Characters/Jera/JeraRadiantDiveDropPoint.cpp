// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraRadiantDiveDropPoint.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AJeraRadiantDiveDropPoint::AJeraRadiantDiveDropPoint()
{
	InitialLifeSpan = 3.f;
	PlaceHolder = CreateDefaultSubobject<USphereComponent>(TEXT("Place Holder"));
	//PlaceHolder->bHiddenInGame = false;
	RootComponent = PlaceHolder;
}

void AJeraRadiantDiveDropPoint::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		AOgnamPlayerState* PlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
		if (!PlayerState)
		{
			UE_LOG(LogTemp, Warning, TEXT("No player state in %s"), __FUNCTIONW__);
			return;
		}

		//Test Overlaps.
		TArray<FOverlapResult> Overlaps;
		TSet<AOgnamCharacter*> Affected;
		FCollisionShape Shape;
		Shape.SetSphere(300.f);
		GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat(), ECollisionChannel::ECC_Pawn, Shape);
		for (FOverlapResult& Result : Overlaps)
		{
			AOgnamCharacter* Character = Cast<AOgnamCharacter>(Result.Actor);
			if (!Character)
			{
				continue;
			}
			AOgnamPlayerState* OverlappedPlayerState = Character->GetPlayerState<AOgnamPlayerState>();
			//if not on same team, push them up and deal damage
			if ((!OverlappedPlayerState || OverlappedPlayerState->GetTeam() != PlayerState->GetTeam()) && !Affected.Contains(Character))
			{
				Character->GetCharacterMovement()->AddImpulse(FVector::UpVector * 100000.f);
				UGameplayStatics::ApplyDamage(Character, 50.f, Instigator->GetController(), this, nullptr);
				Affected.Add(Character);
			}
		}
	}
}


