// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "MaxwellShadowForm.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellShadowForm : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UMaxwellShadowForm();

	virtual void TickModifier(float DeltaTime) override;
	virtual void BeginModifier() override;
};
