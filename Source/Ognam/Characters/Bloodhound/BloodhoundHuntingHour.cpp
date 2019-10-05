// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundHuntingHour.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundHuntingHour::UBloodhoundHuntingHour()
{
	Duration = 5.f;
}

void UBloodhoundHuntingHour::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed;
}
