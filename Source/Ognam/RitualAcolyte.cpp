// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualAcolyte.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
ARitualAcolyte::ARitualAcolyte()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetSkeletalMesh(Mesh.Object);
	SkeletalMesh->SetRelativeLocation(FVector(0, 0, -90));
	SkeletalMesh->SetRelativeRotation(FRotator(0, -90, 0));
	SkeletalMesh->SetVisibility(true);
	SkeletalMesh->SetupAttachment(RootComponent);

	RootComponent = SkeletalMesh;
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

}

