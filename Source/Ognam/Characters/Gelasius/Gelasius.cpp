// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "Gelasius.h"
#include "GelasiusShotgun.h"

AGelasius::AGelasius()
{

}

void AGelasius::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UGelasiusShotgun>(this);
	Weapon->RegisterComponent();
}