// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "IsmaelFlashedModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UIsmaelFlashedModifier : public UExpirableModifier
{
	GENERATED_BODY()
	
public:
	UIsmaelFlashedModifier();

	virtual void BeginModifier() override;
	virtual void EndModifier() override;

private:

	class UMaterial* Material;
};
