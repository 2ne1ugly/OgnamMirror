// Copyright 2019 Ognam Studios. All Rights Reserved.

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