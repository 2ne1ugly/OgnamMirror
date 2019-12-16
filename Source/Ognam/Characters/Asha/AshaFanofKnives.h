// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "AshaFanofKnives.generated.h"

/**
 * Throws 5 knives in a cone in front of Asha
 */
UCLASS()
class OGNAM_API UAshaFanofKnives : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UAshaFanofKnives();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
