// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelFlamePillar.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"

AHazelFlamePillar::AHazelFlamePillar()
{
	Collision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision"));
	Collision->SetVisibility(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);	//This will be on when activation
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHazelFlamePillar::BeginOverlap);
	Collision->SetWorldScale3D(FVector(7.f, 7.f, 8.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Collision->SetStaticMesh(Mesh.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	Collision->SetMaterial(0, Material.Object);

	RootComponent = Collision;

	ActivationTime = 1.f;
	InitialLifeSpan = 2.f;
	BaseDamage = 50.f;
}

void AHazelFlamePillar::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActivationTimer, this, &AHazelFlamePillar::ActivateCollision, ActivationTime, false);
}

void AHazelFlamePillar::ActivateCollision()
{
	Collision->SetVisibility(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);	//This will be on when activation
}

void AHazelFlamePillar::DealDamage(AOgnamCharacter* Character)
{
	UGameplayStatics::ApplyDamage(Character, BaseDamage, Instigator->GetController(), this, nullptr);

}

void AHazelFlamePillar::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (!Character || AffectedCharacters.Contains(Character))
	{
		return;
	}

	AOgnamPlayerState* OtherPlayerState = Character->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* PlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && PlayerState && OtherPlayerState->GetTeam() != PlayerState->GetTeam())
	{
		DealDamage(Character);
		AffectedCharacters.Add(Character);
	}
}
