// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelEnhancedFlamePillar.h"
#include "HazelEnhancedFlamePilarBurning.h"
#include "Ognam/OgnamCharacter.h"

void AHazelEnhancedFlamePillar::DealDamage(class AOgnamCharacter* Character)
{
	Super::DealDamage(Character);
	UHazelEnhancedFlamePilarBurning* Modifier = NewObject<UHazelEnhancedFlamePilarBurning>(Character);
	Modifier->SetInstigator(Instigator);
	Modifier->RegisterComponent();
}