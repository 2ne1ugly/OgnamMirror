// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "JeraSuppressiveImpact.generated.h"

/**
 *	Throws spear that will push away enemy pretty hard
 */
UCLASS()
class OGNAM_API UJeraSuppressiveImpact : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UJeraSuppressiveImpact();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
