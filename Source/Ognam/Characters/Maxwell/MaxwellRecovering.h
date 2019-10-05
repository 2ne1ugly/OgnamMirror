// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "MaxwellRecovering.generated.h"

/**
 *	Recovering from unique
 */
UCLASS()
class OGNAM_API UMaxwellRecovering : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UMaxwellRecovering();

protected:
	virtual void BeginModifier() override;

	void HealTick();

	/*
	**	Props
	*/
	float HealthPenalty;
	float TickPeriod;

	FTimerHandle HealTickTimer;
};
