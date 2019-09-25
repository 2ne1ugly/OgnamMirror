// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "JeraSuppressiveImpactBackSwing.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraSuppressiveImpactBackSwing : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UJeraSuppressiveImpactBackSwing();

protected:
	virtual void EndModifier() override;
};
