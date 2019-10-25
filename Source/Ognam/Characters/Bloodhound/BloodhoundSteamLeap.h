// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundSteamLeap.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundSteamLeap : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundSteamLeap();

protected:
	virtual void ActivateAbility() override;
};
