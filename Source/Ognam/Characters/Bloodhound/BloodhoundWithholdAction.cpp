// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundWithholdAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Bloodhound.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamMacro.h"

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
	O_LOG(TEXT("EndPostDelay"));
	Target->GetMesh()->SetVisibility(true);
	for (int i = 0; i < 3; i++)
	{
		Metals[i]->AttachToComponent(Target->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		Metals[i]->SetRelativeLocation(ABloodhound::MetalPositions[i]);
		Metals[i]->SetRelativeRotation(FRotator::ZeroRotator);
	}
}
