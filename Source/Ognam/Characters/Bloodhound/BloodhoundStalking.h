// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "BloodhoundStalking.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundStalking : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UBloodhoundStalking();

	virtual void BeginModifier() override;
	virtual void EndModifier() override;

protected:
	TArray<class AOgnamCharacter*> StalkedCharacters;
	UMaterial* XRayMaterial;
};
