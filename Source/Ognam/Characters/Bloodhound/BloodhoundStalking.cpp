// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundStalking.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "EngineUtils.h"
#include "Engine.h"

UBloodhoundStalking::UBloodhoundStalking()
{
	Duration = 10.f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/Material/XRay.XRay'"));
	XRayMaterial = Mat.Object;
}

void UBloodhoundStalking::BeginModifier()
{
	Super::BeginModifier();
	if (!Target->GetController() || !Target->GetController()->IsLocalPlayerController())
	{
		return;
	}

	AOgnamPlayerState* PlayerState = Target->GetPlayerState<AOgnamPlayerState>();
	if (!PlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ognam player state"));
		return;
	}
	for (TActorIterator<AOgnamCharacter> Itr(GetWorld()); Itr; ++Itr)
	{
		AOgnamPlayerState* OtherPlayerState = Itr->GetPlayerState<AOgnamPlayerState>();
		if (!OtherPlayerState || OtherPlayerState->GetTeam() == PlayerState->GetTeam())
		{
			continue;
		}
		UE_LOG(LogTemp, Warning, TEXT(":("));
		Itr->GetMesh()->SetRenderCustomDepth(true);
		StalkedCharacters.Add(*Itr);
	}
	Target->Camera->PostProcessSettings.AddBlendable(XRayMaterial, 1.f);
}

void UBloodhoundStalking::EndModifier()
{
	if (!Target->GetController() || !Target->GetController()->IsLocalPlayerController())
	{
		return;
	}

	for (AOgnamCharacter* Character : StalkedCharacters)
	{
		Character->GetMesh()->SetRenderCustomDepth(false);
	}
	if (Target->Controller && Target->Controller->IsLocalController())
	{
		Target->Camera->PostProcessSettings.RemoveBlendable(XRayMaterial);
	}
}
