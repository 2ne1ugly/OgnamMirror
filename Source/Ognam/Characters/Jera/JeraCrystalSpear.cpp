// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "JeraCrystalSpear.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ognam/OgnamMacro.h"

AJeraCrystalSpear::AJeraCrystalSpear()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(100.f, 10.f, 10.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(.2f, .2f, 2.f));
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 6000.f;
	Movement->ProjectileGravityScale = 0.f;
	Movement->OnProjectileStop.AddDynamic(this, &AJeraCrystalSpear::ProjectileStop);

	InitialLifeSpan = 5.f;

	BaseDamage = 60.f;
}

void AJeraCrystalSpear::BeginPlay()
{
	Super::BeginPlay();

	Collision->MoveIgnoreActors.Add(Instigator);
}

void AJeraCrystalSpear::ProjectileStop(const FHitResult& ImpactResult)
{
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
	Character->GetCharacterMovement()->AddImpulse(GetActorForwardVector().GetSafeNormal2D() * 500000.f);
}
