// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundHuntingHourAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHourAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHourAction();

	virtual void EndChannel() override;
};
