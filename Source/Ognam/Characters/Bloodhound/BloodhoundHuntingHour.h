// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "BloodhoundHuntingHour.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHour : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHour();

	virtual void TickModifier(float DeltaTime) override;
protected:
};
