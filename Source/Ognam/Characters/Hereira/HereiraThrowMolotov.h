// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HereiraThrowMolotov.generated.h"

/**
 *	Potentially make this use actions
 */
UCLASS()
class OGNAM_API UHereiraThrowMolotov : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UHereiraThrowMolotov();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
