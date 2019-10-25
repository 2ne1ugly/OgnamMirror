// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "HazelFlameBlastAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelFlameBlastAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UHazelFlameBlastAction();

protected:
	virtual void BeginChannel() override;
};
