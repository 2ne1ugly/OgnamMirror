// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraArrow.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "HereiraCanFastReload.h"

// Sets default values
AHereiraArrow::AHereiraArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Game/Meshes/StaticArrow.StaticArrow'"));
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetStaticMesh(ArrowObj.Object);
	
	Arrow->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);
	Arrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);
	Arrow->OnComponentBeginOverlap.AddDynamic(this, &AHereiraArrow::BeginOverlap);
	Arrow->SetRelativeScale3D(FVector(0.66, 0.66, .66f));
	//Arrow->SetWorldLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	Gravity = 100;
	RootComponent = Arrow;
	bIsTraveling = true;
}

// Called when the game starts or when spawned
void AHereiraArrow::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraArrow::EndLifeSpan, 3., false);
}

// Called every frame
void AHereiraArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsTraveling)
	{
		return;
	}
	
	float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
	FVector Acceleration = Gravity * FVector::DownVector;
	FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;
	FVector Position = InitialPosition + ElapsedTime * InitialVelocity + ElapsedTime * ElapsedTime * Acceleration * 1 / 2;

	FRotator Rotator = FRotationMatrix::MakeFromX(Velocity).Rotator();
	Rotator.Pitch -= 90.f;
	SetActorRotation(Rotator);

	FHitResult HitResult;
	SetActorLocation(Position, true, &HitResult);
	if (HitResult.bBlockingHit)
	{
		bIsTraveling = false;
		OnActorHit(HitResult.GetActor(), HitResult);
		UE_LOG(LogTemp, Warning, TEXT("Blocking!"));
	}
}

void AHereiraArrow::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHereiraArrow, LifeSpan);
	DOREPLIFETIME(AHereiraArrow, InitialPosition);
	DOREPLIFETIME(AHereiraArrow, InitialVelocity);
	DOREPLIFETIME(AHereiraArrow, Gravity);
}

void AHereiraArrow::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	if (OtherActor == Instigator)
	{
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (Character == nullptr)
	{
		return;
	}
	OnCharacterHit(Character, SweepResult);
}

void AHereiraArrow::SetInitialPosition(FVector Value)
{
	InitialPosition = Value;
}

void AHereiraArrow::SetInitialVelocity(FVector Value)
{
	InitialVelocity = Value;
}

void AHereiraArrow::SetGravity(float Value)
{
	Gravity = Value;
}

void AHereiraArrow::EndLifeSpan()
{
	Destroy();
}

void AHereiraArrow::OnCharacterHit(AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
		FVector Acceleration = Gravity * FVector::DownVector;
		FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

		UGameplayStatics::ApplyPointDamage(OtherCharacter, 45, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);

		//Apply Fast reload if close range
		FVector Disposition = InitialVelocity * ElapsedTime + Acceleration * .5f * ElapsedTime * ElapsedTime;
		if (Disposition.Size() < 700.f)
		{
			AOgnamCharacter* Character = Cast<AOgnamCharacter>(Instigator);
			if (Character != nullptr)
			{
				if (Character->GetModifier<UHereiraCanFastReload>() == nullptr)
				{
					Character->ApplyModifier(NewObject<UHereiraCanFastReload>(this));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Not Ognam Character"), __FUNCTIONW__);
			}
		}
	}
	Destroy();

}

void AHereiraArrow::OnActorHit(AActor* OtherActor, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AController* Controller = Instigator->GetController();
	float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
	FVector Acceleration = Gravity * FVector::DownVector;
	FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

	UGameplayStatics::ApplyPointDamage(OtherActor, 45, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);
}

