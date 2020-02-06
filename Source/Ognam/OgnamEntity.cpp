// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamEntity.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamPlayerState.h"
#include "Ognam/OgnamGameState.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"

// Sets default values
AOgnamEntity::AOgnamEntity()
{
	bIsAlive = true;

	SetReplicates(true);
}


UFUNCTION(BluePrintCallable)
bool AOgnamEntity::IsAlive() const
{
	return bIsAlive;
}

void AOgnamEntity::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AOgnamEntity, bIsAlive);
}
