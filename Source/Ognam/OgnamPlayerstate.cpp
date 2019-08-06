// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealNetwork.h"
#include "OgnamPlayerstate.h"

int ID_COUNTER = -1;

AOgnamPlayerstate::AOgnamPlayerstate()
{
	this->ID = ID_COUNTER;
	ID_COUNTER++;
}

void AOgnamPlayerstate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamPlayerstate, ID);
}

int AOgnamPlayerstate::GetID() const
{
	return ID;
}
