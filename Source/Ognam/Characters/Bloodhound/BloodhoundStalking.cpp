// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundStalking.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "EngineUtils.h"
#include "Engine.h"

UBloodhoundStalking::UBloodhoundStalking()
{
	Duration = 6.f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/Material/XRay.XRay'"));
	XRayMaterial = Mat.Object;

	AquiringRange = 3500.f;
	TickingRange = 5000.f;
}

bool UBloodhoundStalking::ShouldEnd()
{
	return Target->HasAuthority() && (Super::ShouldEnd() || StalkedCharacters.Num() == 0);
}

void UBloodhoundStalking::BeginModifier()
{
	Super::BeginModifier();

	if (Target->Controller && Target->Controller->IsLocalPlayerController())
	{
		Target->Camera->PostProcessSettings.AddBlendable(XRayMaterial, 1.f);
	}

	if (!Target->HasAuthority())
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
		if ((Itr->GetActorLocation() - Target->GetActorLocation()).Size() > AquiringRange)
		{
			continue;
		}

		AOgnamPlayerState* OtherPlayerState = Itr->GetPlayerState<AOgnamPlayerState>();

		if (!OtherPlayerState || OtherPlayerState->GetTeam() == PlayerState->GetTeam())
		{
			continue;
		}
		StalkedCharacters.Push(*Itr);
	}
}

void UBloodhoundStalking::TickModifier(float DeltaTime)
{
	Target->Speed /= .8f;
	if (!Target->HasAuthority())
	{
		return;
	}
	for (auto Itr = StalkedCharacters.CreateIterator(); Itr; ++Itr)
	{
		if (!(*Itr)->IsValidLowLevel() ||
			((*Itr)->GetActorLocation() - Target->GetActorLocation()).Size() < TickingRange)
		{
			StalkedCharacters.Remove(*Itr);
		}
	}
}

void UBloodhoundStalking::EndModifier()
{
	if (Target->Controller && Target->Controller->IsLocalPlayerController())
	{	
		Target->Camera->PostProcessSettings.RemoveBlendable(XRayMaterial);
		for (AOgnamCharacter* Character : StalkedCharacters)
		{
			Character->GetMesh()->SetRenderCustomDepth(false);
		}
	}

	if (!Target->HasAuthority())
	{
		return;
	}
	if (StalkedCharacters.Num() > 0)
	{
		//NewObject<UBloodhoundHuntingHour>(Target);
	}
}
//
//void UBloodhoundStalking::ClientAddStalkedCharacter_Implementation(AOgnamCharacter* Character)
//{
//	StalkedCharacters.Add(Character);
//	Character->GetMesh()->SetRenderCustomDepth(true);
//}
//
//void UBloodhoundStalking::ClientRemoveStalkedCharacter_Implementation(AOgnamCharacter* Character)
//{
//	StalkedCharacters.Remove(Character);
//	if (Character->IsValidLowLevel())
//	{
//		Character->GetMesh()->SetRenderCustomDepth(false);
//	}
//}
