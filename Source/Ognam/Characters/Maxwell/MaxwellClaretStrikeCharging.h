// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "MaxwellClaretStrikeCharging.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellClaretStrikeCharging : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UMaxwellClaretStrikeCharging();

	virtual bool ShouldEnd() override;

protected:
	virtual void EndModifier() override;
};
