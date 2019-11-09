// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/AimDownModifier.h"
#include "HazelPyromancyAimDown.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelPyromancyAimDown : public UAimDownModifier
{
	GENERATED_BODY()

public:
	UHazelPyromancyAimDown();

	virtual void TickModifier(float DeltaTime) override;

protected:
	class UCurveFloat* FovCurve;
	class UCurveFloat* SpeedCurve;
};
