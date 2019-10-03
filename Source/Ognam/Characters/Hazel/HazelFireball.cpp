// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelFireball.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"

AHazelFireball::AHazelFireball()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(40.f, 5.f, 5.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Game/Meshes/Arrow/M_Arrow_Static.M_Arrow_Static'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(0.66, 0.66, .66f));
	Mesh->SetRelativeLocationAndRotation(FVector(-20.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 4000.f;
	Movement->OnProjectileStop.AddDynamic(this, &AHazelFireball::ProjectileStop);
	Movement->ProjectileGravityScale = 0.f;
	//Stop happens only when two collision is blocking eachother.

	BaseDamage = 20.f;
	InitialLifeSpan = 3.f;
}

void AHazelFireball::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(Instigator);	
}

void AHazelFireball::ProjectileStop(const FHitResult& ImpactResult)
{
	if (!Instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(ImpactResult.GetActor());
	if (!Character)
	{
		return;
	}
	Collision->AttachToComponent(ImpactResult.GetComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), ImpactResult.BoneName);

	if (!HasAuthority())
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
