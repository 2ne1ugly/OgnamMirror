// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundImpactShotgunAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundImpactShotgunAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundImpactShotgunAction();

protected:
	virtual void EndChannel() override;

	UFUNCTION(NetMulticast, Unreliable)
	void NetDrawTrajectory(FVector From, const TArray<FVector>& Tos);
	virtual void NetDrawTrajectory_Implementation(FVector From, const TArray<FVector>& Tos);

	/*
	**	Props
	*/
	int32 NumPellets;
	float Spread;
};
