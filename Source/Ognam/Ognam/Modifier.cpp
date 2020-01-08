// Fill out your copyright notice in the Description page of Project Settings.


#include "Modifier.h"
#include "OgnamCharacter.h"
#include "Ognam/OgnamMacro.h"

UModifier::UModifier()
{
	SetIsReplicatedByDefault(true);
}
bool UModifier::ShouldEnd()
{
	return false;
}

void UModifier::TickModifier(float DeltaTime)
{
}

void UModifier::BeginPlay()
{
	Super::BeginPlay();

	bActivated = true;
	ExecuteModifier();
}

void UModifier::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!bActivated)
	{
		O_LOG_E(TEXT("Destroying Modifier that wasn't started"));
		return;
	}
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		EndModifier();
	}
	bActivated = false;
	Target->Modifiers.Remove(this);
	Target->RemoveStatusEffect(StatusEffects);
}

const TSet<EStatusEffect>& UModifier::GetStatusEffect() const
{
	return StatusEffects;
}

void UModifier::BeginModifier()
{
}

void UModifier::EndModifier()
{
}

void UModifier::ExecuteModifier()
{
	Target = Cast<AOgnamCharacter>(GetOwner());
	if (!Target)
	{
		O_LOG_F(TEXT("Modifier applied to non-ognam character"));
		return;
	}
	Target->ApplyStatusEffect(StatusEffects);
	BeginModifier();
	Target->Modifiers.Add(this);
}

void UModifier::SetStatusEffect(const TSet<EStatusEffect>& Effects)
{
	if (bActivated)
	{
		TSet<EStatusEffect> GoingOut = StatusEffects.Difference(Effects);
		TSet<EStatusEffect> GoingIn = Effects.Difference(StatusEffects);
		Target->RemoveStatusEffect(GoingOut);
		Target->ApplyStatusEffect(GoingIn);
	}
	StatusEffects = Effects;
}
