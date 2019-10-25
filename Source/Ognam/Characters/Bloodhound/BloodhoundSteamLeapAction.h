// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundSteamLeapAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundSteamLeapAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundSteamLeapAction();

protected:
	virtual void TickChannel(float DeltaTime) override;
	virtual void BeginPostDelay() override;
};
