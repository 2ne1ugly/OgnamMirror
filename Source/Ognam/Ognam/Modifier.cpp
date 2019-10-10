// Fill out your copyright notice in the Description page of Project Settings.


#include "Modifier.h"
#include "OgnamCharacter.h"
#include "Ognam/OgnamMacro.h"

UModifier::UModifier()
{
	SetIsReplicated(true);
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

	Target = Cast<AOgnamCharacter>(GetOwner());
	if (!Target)
	{
		O_LOG_E(TEXT("Modifier applied to non-ognam character"));
		return;
	}
	if (StatusEffect != EStatusEffect::None)
	{
		Target->ApplyStatusEffect(StatusEffect);
	}
	BeginModifier();
	Target->Modifiers.Add(this);
}

void UModifier::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!Target)
	{
		O_LOG_E(TEXT("Modifier applied to non-ognam character"));
		return;
	}
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		EndModifier();
	}
	Target->Modifiers.Remove(this);
}

EStatusEffect UModifier::GetStatusEffect() const
{
	return StatusEffect;
}

void UModifier::BeginModifier()
{
}

void UModifier::EndModifier()
{
}
