// Fill out your copyright notice in the Description page of Project Settings.


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