// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "Ismael.h"
#include "IsmaelLuxAeterna.h"

void AIsmael::BeginPlay()
{
	Super::BeginPlay();

	Mobility = NewObject<UIsmaelLuxAeterna>(this, TEXT("Mobility"));

	Mobility->RegisterComponent();

	BaseSpeed = 10000;
}
