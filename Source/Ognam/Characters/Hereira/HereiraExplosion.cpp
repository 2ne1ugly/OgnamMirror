// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraExplosion.h"
#include "ConstructorHelpers.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AHereiraExplosion::AHereiraExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Range = CreateDefaultSubobject<USphereComponent>(TEXT("Range"));
	Range->SetCollisionProfileName(TEXT("Trigger"));
	Range->bHiddenInGame = false;
	Range->OnComponentBeginOverlap.AddDynamic(this, &AHereiraExplosion::OnBeginOverlap);
	Range->SetSphereRadius(125.f);
	RootComponent = Range;
}

// Called when the game starts or when spawned
void AHereiraExplosion::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(LifeSpan, this, &AHereiraExplosion::EndLifeSpan, 0.25f, false);
}

// Called every frame
void AHereiraExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHereiraExplosion::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bIsAlreadyIn;
	AffectedActors.Add(OtherActor, &bIsAlreadyIn);
	if (bIsAlreadyIn)
	{
		return;
	}

	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (Character != nullptr)
	{
		OnCharacterHit(Character);
	}
	else
	{
		OnActorHit(OtherActor);
	}
}

void AHereiraExplosion::OnCharacterHit(AOgnamCharacter* OtherCharacter)
{
	AOgnamPlayerState* PlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	if (PlayerState && OtherPlayerState && PlayerState->GetTeam() != OtherPlayerState->GetTeam())
	{
		UGameplayStatics::ApplyDamage(OtherCharacter, 45, Instigator->GetController(), this, nullptr);
	}
}

void AHereiraExplosion::OnActorHit(AActor* OtherActor)
{
	UGameplayStatics::ApplyDamage(OtherActor, 45, Instigator->GetController(), this, nullptr);
}

void AHereiraExplosion::EndLifeSpan()
{
	Destroy();
}

