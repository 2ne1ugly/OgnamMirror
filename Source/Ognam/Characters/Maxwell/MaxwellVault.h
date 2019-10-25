// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "MaxwellVault.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellVault : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UMaxwellVault();

protected:
	virtual void ActivateAbility() override;
	virtual void ApplyModifier();
};
