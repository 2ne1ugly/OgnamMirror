// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "HazelEnhancedFlamePilarBurning.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelEnhancedFlamePilarBurning : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UHazelEnhancedFlamePilarBurning();

	void SetInstigator(APawn* _Instigator);

protected:
	virtual void BeginModifier() override;


	void DamageTick();

	/*
	**	Props
	*/
	float TickPeriod;

	FTimerHandle DamageTickTimer;

	APawn* Instigator;
};
