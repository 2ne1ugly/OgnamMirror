// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraWillExplode.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "HereiraExplosion.h"
#include "Ognam/OgnamCharacter.h"

void UHereiraWillExplode::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(Duration, .5f, false);
}

void UHereiraWillExplode::EndModifier()
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	AHereiraExplosion* Explosion = GetWorld()->SpawnActor<AHereiraExplosion>(Target->GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	Explosion->SetReplicates(true);
}

void UHereiraWillExplode::SetInstigator(APawn* Pawn)
{
	Instigator = Pawn;
}
