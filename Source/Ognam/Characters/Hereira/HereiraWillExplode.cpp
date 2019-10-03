// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraWillExplode.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "HereiraExplosion.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "UnrealNetwork.h"

UHereiraWillExplode::UHereiraWillExplode()
{
	Duration = .5f;
}

void UHereiraWillExplode::EndModifier()
{
	if (!GetWorld()->GetGameState()->HasAuthority())
	{
		return;
	}
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTION__);
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
