// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "BloodhoundWithholdAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Bloodhound.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamPlayerstate.h"

UBloodhoundWithholdAction::UBloodhoundWithholdAction()
{
	PreDelayDuration = .5f;
	ChannelDuration = 2.5f;
	PostDelayDuration = .5f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UBloodhoundWithholdAction::BeginChannel()
{
	//Hide Bloodhound and pop the metals
	Target->GetMesh()->SetVisibility(false);

	AOgnamPlayerState* SelfState = Target->GetPlayerState<AOgnamPlayerState>();
	SelfState->SetShouldHideName(true);

	//Save the locations of metals
	ABloodhound* Bloodhound = CastChecked<ABloodhound>(Target);
	TArray<UActorComponent*> Components = Bloodhound->GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("Metal"));
	Metals.Empty();
	for (UActorComponent* Component : Components)
	{
		UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component);
		if (!Mesh)
		{
			O_LOG(TEXT("This Metal is not static mesh"));
			continue;
		}
		Metals.Add(Mesh);
	}
	if (Metals.Num() != 3)
	{
		O_LOG_E(TEXT("Metal count is not 3"));
	}

	for (int i = 0; i < 3; i++)
	{
		Metals[i]->SetSimulatePhysics(true);
		Metals[i]->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		Metals[i]->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Metals[i]->AddRadialImpulse(Bloodhound->GetActorLocation(), 500.f, 1200.f, ERadialImpulseFalloff::RIF_Linear);
	}

	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	//Damaging
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	TArray<FOverlapResult> Overlaps;
	TSet<AOgnamCharacter*> Characters;
	GetWorld()->OverlapMultiByObjectType(Overlaps, GetOwner()->GetActorLocation(), FQuat(), ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(320.f), Params);
	for (FOverlapResult& Overlap : Overlaps)
	{
		O_LOG(TEXT("Overlap!"));
		AOgnamCharacter* Character = Cast<AOgnamCharacter>(Overlap.GetActor());
		if (!Character)
		{
			continue;
		}

		//Add team check.
		bool bIsIn;
		Characters.Add(Character, &bIsIn);
		AOgnamPlayerState* OtherPlayerState = Character->GetPlayerState<AOgnamPlayerState>();
		AOgnamPlayerState* PlayerState = Target->GetPlayerState<AOgnamPlayerState>();
		if (!bIsIn && OtherPlayerState && PlayerState && OtherPlayerState->GetTeam() != PlayerState->GetTeam())
		{
			UGameplayStatics::ApplyDamage(Character, 30.f, Target->GetController(), Target, nullptr);
		}
	}
}

void UBloodhoundWithholdAction::TickChannel(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed * .5f;
}

void UBloodhoundWithholdAction::BeginPostDelay()
{
	SavedLocations.Empty();
	SavedRotations.Empty();

	for (int i = 0; i < 3; i++)
	{
		SavedLocations.Add(Metals[i]->GetComponentLocation());
		SavedRotations.Add(Metals[i]->GetComponentRotation());
		Metals[i]->SetSimulatePhysics(false);
		Metals[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UBloodhoundWithholdAction::TickPostDelay(float DeltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		Metals[i]->SetWorldLocation(FMath::Lerp(SavedLocations[i], Target->GetMesh()->GetComponentTransform().TransformPosition(ABloodhound::MetalPositions[i]),
			GetWorld()->GetTimerManager().GetTimerElapsed(PostDelayTimer) / PostDelayDuration));
		Metals[i]->SetWorldRotation(FMath::Lerp(SavedRotations[i], FRotator::ZeroRotator,
			GetWorld()->GetTimerManager().GetTimerElapsed(PostDelayTimer) / PostDelayDuration));
	}

}

void UBloodhoundWithholdAction::EndPostDelay()
{
	Target->GetMesh()->SetVisibility(true);

	AOgnamPlayerState* SelfState = Target->GetPlayerState<AOgnamPlayerState>();
	SelfState->SetShouldHideName(false);
	for (int i = 0; i < 3; i++)
	{
		Metals[i]->AttachToComponent(Target->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		Metals[i]->SetRelativeLocation(ABloodhound::MetalPositions[i]);
		Metals[i]->SetRelativeRotation(FRotator::ZeroRotator);
	}
}
