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
	TickingRange = 4000.f;
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
	if (StalkedCharacters.Num() > 0)
	{
		ClientInformStalk(StalkedCharacters);
	}
}

void UBloodhoundStalking::TickModifier(float DeltaTime)
{
	Target->Speed /= .8f;
	if (!Target->HasAuthority())
	{
		return;
	}

	for (int i = StalkedCharacters.Num() - 1; i >= 0; i--)
	{
		if (!StalkedCharacters[i]->IsValidLowLevel() ||
			(StalkedCharacters[i]->GetActorLocation() - Target->GetActorLocation()).Size() > TickingRange)
		{
			ClientStalkLost(StalkedCharacters[i]);
			StalkedCharacters.RemoveAt(i, 1, false);
		}
	}
}

void UBloodhoundStalking::EndModifier()
{
	if (Target->Controller && Target->Controller->IsLocalPlayerController())
	{	
		Target->Camera->PostProcessSettings.RemoveBlendable(XRayMaterial);
	}
	if (!Target->HasAuthority())
	{
		return;
	}

	if (StalkedCharacters.Num() > 0)
	{
		for (AOgnamCharacter* Character : StalkedCharacters)
		{
			ClientStalkLost(Character);
		}

	}
}

void UBloodhoundStalking::ClientInformStalk_Implementation(const TArray<class AOgnamCharacter*>& Stalked)
{
	for (AOgnamCharacter* Character : Stalked)
	{
		Character->GetMesh()->SetRenderCustomDepth(true);
	}
}

void UBloodhoundStalking::ClientStalkLost_Implementation(AOgnamCharacter* Character)
{
	Character->GetMesh()->SetRenderCustomDepth(false);
}
