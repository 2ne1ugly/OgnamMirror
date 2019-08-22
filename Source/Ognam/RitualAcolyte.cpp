// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualAcolyte.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "RitualShrine.h"
#include "InteractComponent.h"

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

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact"));
	AddOwnedComponent(InteractComponent);

	RootComponent = Capsule;
}

// Called when the game starts or when spawned
void ARitualAcolyte::BeginPlay()
{
	Super::BeginPlay();
	
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

