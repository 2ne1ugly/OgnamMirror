// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellAimDowned.h"
#include "Ognam/OgnamCharacter.h"

bool UMaxwellAimDowned::ShouldEnd()
{
	return bInterrupted;
}

void UMaxwellAimDowned::TickModifier(float DeltaTime)
{
	Target->Speed *= .5f;
}

void UMaxwellAimDowned::Interrupt()
{
	bInterrupted = true;
}

void UMaxwellAimDowned::BeginModifier()
{
}

void UMaxwellAimDowned::EndModifier()
{
}
