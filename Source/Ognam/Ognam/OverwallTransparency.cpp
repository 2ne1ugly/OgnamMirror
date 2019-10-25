// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "OverwallTransparency.h"
#include "Components/PrimitiveComponent.h"
#include "OgnamCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"

UOverwallTransparency::UOverwallTransparency()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DefaultTransparentWall.DefaultTransparentWall'"));
	DefaultMaterial = Material.Object;
}

void UOverwallTransparency::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Components = GetOwner()->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("Overwall Transparent"));
	for (UActorComponent* Component : Components)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component);
		if (PrimitiveComponent)
		{
			AddTargetComponent(PrimitiveComponent, DefaultMaterial);
		}
	}
}

void UOverwallTransparency::AddTargetComponent(UPrimitiveComponent* PrimitiveComponent, UMaterialInterface* BlockingMaterial)
{
	TargetComponents.Add(PrimitiveComponent);
	BlockingMaterials.Add(BlockingMaterial);
	SavedMaterials.Add(nullptr);
}

void UOverwallTransparency::ComponentsBlocked()
{
	bBlocked = true;
	for (int i = 0; i < TargetComponents.Num(); i++)
	{
		SavedMaterials[i] = TargetComponents[i]->GetMaterial(0);
		TargetComponents[i]->SetMaterial(0, BlockingMaterials[i]);
	}
}

void UOverwallTransparency::ComponentsUnBlocked()
{
	bBlocked = false;
	for (int i = 0; i < TargetComponents.Num(); i++)
	{
		TargetComponents[i]->SetMaterial(0, SavedMaterials[i]);
	}
}

bool UOverwallTransparency::IsActorInHitResults(TArray<FHitResult>& HitResults)
{
	for (FHitResult& Hit : HitResults)
	{
		if (Hit.GetActor() == GetOwner())
		{
			return true;
		}
	}
	return false;
}

// Called every frame
void UOverwallTransparency::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Find local Ognam character
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController || !PlayerController->IsLocalPlayerController())
	{
		return;
	}

	//If Ognam character is not there and this is hidden, show again.
	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(PlayerController->GetCharacter());
	if (!OgnamCharacter)
	{
		if (bBlocked)
		{
			ComponentsUnBlocked();
		}
		return;
	}

	if (bBlocked)
	{
		if (!OgnamCharacter->bCameraBlocked || !IsActorInHitResults(OgnamCharacter->CameraHits))
		{
			ComponentsUnBlocked();
		}
	}
	else
	{
		if (OgnamCharacter->bCameraBlocked && IsActorInHitResults(OgnamCharacter->CameraHits))
		{
			ComponentsBlocked();
		}
	}
}

