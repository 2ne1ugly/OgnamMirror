// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HazelDisruptiveBurst.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelDisruptiveBurst : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UHazelDisruptiveBurst();

protected:
	virtual void ActivateAbility() override;
};
 