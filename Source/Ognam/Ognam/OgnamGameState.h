// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "OgnamGameState.generated.h"

/**
 *	This state should never be used.
 *	Not even meant for inheritance
 */
UCLASS()
class OGNAM_API AOgnamGameState : public AGameState
{
	GENERATED_BODY()

public:
	AOgnamGameState();

	virtual void NotifyDamageEvent(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage);
	virtual void NotifyKillEvent(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController);
};
