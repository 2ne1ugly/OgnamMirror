// Fill out your copyright notice in the Description page of Project Settings.


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
#include "HereiraCanFastReload.h"

// Sets default values
AHereiraArrow::AHereiraArrow()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(40.f, 5.f, 5.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHereiraArrow::OnBeginOverlap);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Game/Meshes/StaticArrow.StaticArrow'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetRelativeScale3D(FVector(0.66, 0.66, .66f));
	Mesh->SetRelativeLocationAndRotation(FVector(-20.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 4000.f;
	Movement->ProjectileGravityScale = 1.5f;

	RootComponent = Collision;
}

// Called when the game starts or when spawned
void AHereiraArrow::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(Instigator);
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraArrow::EndLifeSpan, 3., false);
}

void AHereiraArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Instigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}
	if (!bFromSweep)
	{
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (Character)
	{
		OnCharacterHit(Character, SweepResult);
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
		UGameplayStatics::ApplyPointDamage(OtherCharacter, 30, SweepResult.ImpactNormal, SweepResult, Controller, this, nullptr);
	}
	Destroy();
}


