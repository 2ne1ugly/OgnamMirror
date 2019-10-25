// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HazelFlameBlast.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelFlameBlast : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UHazelFlameBlast();

protected:
	virtual void ActivateAbility() override;
};
