// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundHuntingHourAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHourAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHourAction();

	virtual void EndChannel() override;
};
