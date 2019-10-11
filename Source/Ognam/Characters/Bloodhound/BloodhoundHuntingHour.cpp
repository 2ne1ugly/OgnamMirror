// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundHuntingHour.h"
#include "Ognam/OgnamCharacter.h"
#include "BloodhoundLeap.h"

UBloodhoundHuntingHour::UBloodhoundHuntingHour()
{
	Duration = 5.f;
}

void UBloodhoundHuntingHour::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed;
}

bool UBloodhoundHuntingHour::ShouldEnd()
{
	return Super::ShouldEnd() || bConsumed;
}

void UBloodhoundHuntingHour::Consume()
{
	bConsumed = true;
	NewObject<UBloodhoundLeap>(Target)->RegisterComponent();
}
