// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "JeraDescending.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraDescending : public UModifier
{
	GENERATED_BODY()

public:
	UJeraDescending();

	virtual bool ShouldEnd() override;

	virtual void TickModifier(float DeltaTime) override;
	virtual void EndModifier() override;
};
