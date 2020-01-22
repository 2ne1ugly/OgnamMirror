// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSnapshot.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "ConstructorHelpers.h"
#include "OgnamMacro.h"
#include "Kismet/GameplayStatics.h"
#include "OgnamCharacter.h"

// Sets default values
ASoundSnapshot::ASoundSnapshot()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetDepthPriorityGroup(SDPG_Foreground);
	//Mesh->SetRenderCustomDepth(true);
	//Mesh->SetCustomDepthStencilValue(3);

	InitialLifeSpan = .5f;
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UMaterial> SnapshotMaterialCH(TEXT("Material'/Game/Material/SoundSnapshot.SoundSnapshot'"));
	SnapshotMaterial = SnapshotMaterialCH.Object;
}

void ASoundSnapshot::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SnapshotDynamicMaterial = UMaterialInstanceDynamic::Create(SnapshotMaterial, this);
}

// Called every frame
void ASoundSnapshot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) {
		return;
	}
	float TacticalAmount = Character->GetTacticalAmount();
	SnapshotDynamicMaterial->SetScalarParameterValue(TEXT("Lifespan"), GetLifeSpan() / 0.5f * TacticalAmount);
}

void ASoundSnapshot::Snapshot(USkeletalMeshComponent* SkeletalMesh)
{
	if (!SkeletalMesh)
	{
		O_LOG_E(TEXT("No skeletal mesh found!"));
		return;
	}

	Mesh->SetSkeletalMesh(SkeletalMesh->SkeletalMesh);
	Mesh->CopyPoseFromSkeletalComponent(SkeletalMesh);
	Mesh->SetWorldTransform(SkeletalMesh->GetComponentTransform());
	int MaterialCount = Mesh->GetNumMaterials();
	for (int i = 0; i < MaterialCount; i++)
	{
		Mesh->SetMaterial(i, SnapshotDynamicMaterial);
	}
}

