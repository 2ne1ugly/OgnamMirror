// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "HazelBlazingSpiritsAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelBlazingSpiritsAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UHazelBlazingSpiritsAction();

protected:
	virtual void EndChannel() override;
};
