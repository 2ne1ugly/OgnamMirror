// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HereiraArrow.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/ImpactDamage.h"
#include "Ognam/OgnamMacro.h"

// Sets default values
AHereiraArrow::AHereiraArrow()
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

	GravityScale = 1.f;
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 6000.f;
	Movement->OnProjectileStop.AddDynamic(this, &AHereiraArrow::ProjectileStop);
	//Stop happens only when two collision is blocking eachother.

	BaseDamage = 75.f;
}

void AHereiraArrow::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Movement->ProjectileGravityScale = GravityScale;
}

// Called when the game starts or when spawned
void AHereiraArrow::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(Instigator);
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraArrow::EndLifeSpan, 3., false);
}

void AHereiraArrow::ProjectileStop(const FHitResult& ImpactResult)
{
	if (!Instigator)
	{
		O_LOG(TEXT("No Instigator!"));
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(ImpactResult.GetActor());
	if (Character)
	{
		OnCharacterHit(Character, ImpactResult);
		Collision->AttachToComponent(ImpactResult.GetComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), ImpactResult.BoneName);
	}
}

void AHereiraArrow::EndLifeSpan()
{
	Destroy();
}

void AHereiraArrow::OnCharacterHit(AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult)
{
	if (!HasAuthority() || OtherCharacter == Instigator)
	{
		return;
	}
	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		UGameplayStatics::ApplyPointDamage(OtherCharacter, BaseDamage, SweepResult.ImpactNormal, SweepResult, Controller, this, UImpactDamage::StaticClass());
	}
	//Destroy();
}


