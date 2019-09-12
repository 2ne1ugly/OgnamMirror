// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualAcolyte.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RitualShrine.h"
#include "RitualPlayerState.h"
#include "RitualPlayerController.h"
#include "RitualGameState.h"

// Sets default values
ARitualAcolyte::ARitualAcolyte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComponent);
	//Capsule->SetMobility(EComponentMobility::Static);
	Capsule->SetCapsuleHalfHeight(88.f);
	Capsule->SetCapsuleRadius(34.f);
	Capsule->SetCollisionProfileName(TEXT("BlockAll"));
	Capsule->SetEnableGravity(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetSkeletalMesh(Mesh.Object);
	SkeletalMesh->SetRelativeLocation(FVector(0, 0, -90));
	SkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
	SkeletalMesh->SetWorldScale3D(FVector(.5, .5, .5));
	SkeletalMesh->SetupAttachment(Capsule);
	SkeletalMesh->SetCollisionProfileName(TEXT("CharacterMesh"));

	RootComponent = Capsule;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ARitualAcolyte::BeginPlay()
{
	Super::BeginPlay();
}

float ARitualAcolyte::GetInteractDistance() const
{
	return 300.f;
}

void ARitualAcolyte::BeInteracted_Implementation(APlayerController* PlayerController)
{
	//ParentShrine->RemoveAcolyte(this);
	Destroy();

	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Ritual Gamestate"), __FUNCTION__);
		return;
	}
	GameState->GiveAcolyteKillReward();
}

bool ARitualAcolyte::CanInteractWithController(const APlayerController* PlayerController) const
{
	ARitualPlayerState* RitualPlayerState = PlayerController->GetPlayerState<ARitualPlayerState>();
	if (RitualPlayerState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%¤¤ Not Ritual Player State"), __FUNCTION__);
		return false;
	}

	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not Ritual Game State"), __FUNCTION__);
		return false;
	}

	if (GameState->GetCurrentOffenseTeam() != RitualPlayerState->GetTeam())
	{
		return false;
	}

	return true;
}

float ARitualAcolyte::GetInteractDuration() const
{
	return 3.0f;
}

void ARitualAcolyte::SetParentShrine(ARitualShrine* Shrine)
{
	ParentShrine = Shrine;
}

// Called every frame
void ARitualAcolyte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ParentShrine != nullptr)
	{
		FRotator direction = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ParentShrine->GetActorLocation());
		direction.Pitch = 0;
		direction.Roll = 0;
		SetActorRotation(direction);
	}
}

