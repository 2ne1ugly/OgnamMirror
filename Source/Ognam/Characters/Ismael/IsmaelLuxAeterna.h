// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "IsmaelLuxAeterna.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UIsmaelLuxAeterna : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UIsmaelLuxAeterna();

protected:
	virtual void ActivateAbility() override;
};
