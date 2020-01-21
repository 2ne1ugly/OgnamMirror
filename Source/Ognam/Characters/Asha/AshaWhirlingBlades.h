// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "AshaWhirlingBlades.generated.h"

/**
 * 
 */

UCLASS()
class OGNAM_API UAshaWhirlingBlades : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UAshaWhirlingBlades();

protected:
	virtual void ActivateAbility() override;
};
