// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundImpactShotgun.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundImpactShotgun : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundImpactShotgun();

protected:
	virtual void ActivateAbility() override;
};
