// Fill out your copyright notice in the Description page of Project Settings.


#include "Ismael.h"
#include "IsmaelLuxAeterna.h"

void AIsmael::BeginPlay()
{
	Super::BeginPlay();

	Mobility = NewObject<UIsmaelLuxAeterna>(this, TEXT("Mobility"));

	Mobility->RegisterComponent();

	BaseSpeed = 10000;
}
