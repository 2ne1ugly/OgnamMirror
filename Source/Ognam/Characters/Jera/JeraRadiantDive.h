// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "JeraRadiantDive.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraRadiantDive : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UJeraRadiantDive();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
