// Fill out your copyright notice in the Description page of Project Settings.


#include "Modifier.h"
#include "OgnamCharacter.h"

void UModifier::GetApplied(AOgnamCharacter* Character)
{
	Target = Character;
	bActive = true;
	BeginModifier();
}

void UModifier::GetDetached()
{
	EndModifier();
	Target = nullptr;
	bActive = false;
}

bool UModifier::IsActive() const
{
	return bActive;
}

bool UModifier::ShouldEnd()
{
	return false;
}

void UModifier::TickModifier(float DeltaTime)
{
}

void UModifier::BeginModifier()
{
}

void UModifier::EndModifier()
{
}
