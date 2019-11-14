// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelFireball.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamProjectileComponent.h"

AHazelFireball::AHazelFireball()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(17.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(0.33f));

	Movement = CreateDefaultSubobject<UOgnamProjectileComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 2000.f;
	Movement->OnProjectileStop.AddDynamic(this, &AHazelFireball::ProjectileStop);
	Movement->ProjectileGravityScale = 0.f;
	Movement->DirecitionalAcceleration = 2000.f;

	//Stop happens only when two collision is blocking eachother.

	BaseDamage = 30.f;
	InitialLifeSpan = 3.f;
}

void AHazelFireball::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(Instigator);	
}

void AHazelFireball::ProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();
	if (!HasAuthority())
	{
		return;
	}
	if (!Instigator)
	{
		O_LOG(TEXT("No Instigator!"));
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(ImpactResult.GetActor());
	if (!Character)
	{
		return;
	}
	AOgnamPlayerState* OtherPlayerState = Character->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		UGameplayStatics::ApplyPointDamage(Character, BaseDamage, ImpactResult.ImpactNormal, ImpactResult, Controller, this, nullptr);
	}
}
