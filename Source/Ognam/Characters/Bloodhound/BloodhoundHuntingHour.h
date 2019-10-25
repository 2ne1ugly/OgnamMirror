// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundHuntingHour.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHour : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHour();

	virtual void ActivateAbility() override;
};
