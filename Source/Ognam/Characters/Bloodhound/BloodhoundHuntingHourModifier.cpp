// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundHuntingHourModifier.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Ognam/OgnamMacro.h"

UBloodhoundHuntingHourModifier::UBloodhoundHuntingHourModifier()
{
	Duration = 10.f;
	InitialRange = 6000.f;
	Range = InitialRange;

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/Material/XRay.XRay'"));
	XRayMaterial = Mat.Object;
}

bool UBloodhoundHuntingHourModifier::ShouldEnd()
{
	return Super::ShouldEnd() || (GetOwner()->HasAuthority() && StalkedCharacters.Num() == 0);
}

void UBloodhoundHuntingHourModifier::BeginModifier()
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

	AOgnamPlayerState* OgnamPlayerState = Target->GetPlayerState<AOgnamPlayerState>();
	if (!OgnamPlayerState)
	{
		O_LOG(TEXT("No ognam player state"));
		return;
	}

	for (APlayerState* OtherPlayerState : GetWorld()->GetGameState()->PlayerArray)
	{
		AOgnamPlayerState* OtherOgnamPlayerState = CastChecked<AOgnamPlayerState>(OtherPlayerState);
		if (OtherOgnamPlayerState->GetTeam() == OgnamPlayerState->GetTeam() ||
			!OtherOgnamPlayerState->IsAlive() ||
			OtherOgnamPlayerState->GetPawn()->GetDistanceTo(Target) > InitialRange)
		{
			continue;
		}

		AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherOgnamPlayerState->GetPawn());
		if (!Character)
		{
			O_LOG(TEXT("Not Ognam character"));
			continue;
		}

		StalkedCharacters.Add(Character);
		ClientInformStalk(Character);
	}
}

void UBloodhoundHuntingHourModifier::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed * .5f;

	if (!Target->HasAuthority())
	{
		return;
	}
	Range = InitialRange * GetWorld()->GetTimerManager().GetTimerRemaining(DurationTimer) / Duration;

	//Removes
	for (auto Itr = StalkedCharacters.begin(); Itr; ++Itr)
	{
		if ((*Itr)->IsValidLowLevel() &&
			(*Itr)->IsAlive() &&
			(*Itr)->GetDistanceTo(Target) <= Range)
		{
			continue;
		}

		ClientStalkLost(*Itr);
		StalkedCharacters.Remove(Itr.GetId());
	}

	//New inserts
	for (APlayerState* OtherPlayerState : GetWorld()->GetGameState()->PlayerArray)
	{
		AOgnamPlayerState* OtherOgnamPlayerState = CastChecked<AOgnamPlayerState>(OtherPlayerState);
		if (OtherOgnamPlayerState->GetTeam() == OtherOgnamPlayerState->GetTeam() ||
			!OtherOgnamPlayerState->IsAlive() ||
			OtherOgnamPlayerState->GetPawn()->GetDistanceTo(Target) > Range)
		{
			continue;
		}

		AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherOgnamPlayerState->GetPawn());
		if (!Character)
		{
			O_LOG(TEXT("Not Ognam character"));
			continue;
		}

		bool bAlreadySet;
		StalkedCharacters.Add(Character, &bAlreadySet);
		if (!bAlreadySet)
		{
			ClientInformStalk(Character);
		}
	}
}

void UBloodhoundHuntingHourModifier::EndModifier()
{
	if (Target->Controller && Target->Controller->IsLocalPlayerController())
	{
		Target->Camera->PostProcessSettings.RemoveBlendable(XRayMaterial);
	}
	if (!Target->HasAuthority())
	{
		return;
	}

	for (AOgnamCharacter* Character : StalkedCharacters)
	{
		ClientStalkLost(Character);
	}
}

void UBloodhoundHuntingHourModifier::ClientInformStalk_Implementation(AOgnamCharacter* Stalked)
{
	if (Stalked->IsValidLowLevel())
	{
		Stalked->GetMesh()->SetRenderCustomDepth(true);
		Stalked->GetMesh()->SetBoundsScale(1.15f);
	}
}

void UBloodhoundHuntingHourModifier::ClientStalkLost_Implementation(AOgnamCharacter* Character)
{
	if (Character->IsValidLowLevel())
	{
		Character->GetMesh()->SetRenderCustomDepth(false);
		Character->GetMesh()->SetBoundsScale(1.f);
	}
}
