// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "OverwallHidden.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OgnamCharacter.h"
#include "OgnamMacro.h"

UOverwallHidden::UOverwallHidden()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = false;
}

void UOverwallHidden::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Find local Ognam character
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController->IsLocalPlayerController())
	{
		O_LOG(TEXT("Overwall ticks on dedicated server"));
		return;
	}

	//If Ognam character is not there and this is hidden, show again.
	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(PlayerController->GetCharacter());
	if (!OgnamCharacter || OgnamCharacter == GetOwner())
	{
		if (bOverwallHidden)
		{
			ShowComponents();
		}
		return;
	}

	if (bOverwallHidden)
	{
		//if hidden
		if (!OgnamCharacter->bCameraBlocked || OgnamCharacter->CameraBlockingPlane.PlaneDot(GetOwner()->GetActorLocation()) > 0.f)
		{
			ShowComponents();
		}
	}
	else
	{
		//if not hidden
		if (OgnamCharacter->bCameraBlocked && OgnamCharacter->CameraBlockingPlane.PlaneDot(GetOwner()->GetActorLocation()) < 0.f)
		{
			HideComponents();
		}
	}
}

void UOverwallHidden::HideComponents()
{
	bOverwallHidden = true;
	for (int i = 0; i < TargetComponents.Num(); i++)
	{
		//This uses set visibility which may cause bugs in the future.
		//Find a better way some day.
		TargetComponents[i]->SetVisibility(false);
	}
}

void UOverwallHidden::ShowComponents()
{
	bOverwallHidden = false;
	for (int i = 0; i < TargetComponents.Num(); i++)
	{
		TargetComponents[i]->SetVisibility(true);
	}
}

void UOverwallHidden::AddTargetComponents(USceneComponent* SceneComponent)
{
	TargetComponents.Add(SceneComponent);
}
