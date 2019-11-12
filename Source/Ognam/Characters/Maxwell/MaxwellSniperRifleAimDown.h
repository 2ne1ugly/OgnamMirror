// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/AimDownModifier.h"
#include "MaxwellSniperRifleAimDown.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifleAimDown : public UAimDownModifier
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifleAimDown();

	virtual void TickModifier(float DeltaTime) override;

protected:
	class UCurveFloat* FovCurve;
	class UCurveFloat* SpeedCurve;
};
