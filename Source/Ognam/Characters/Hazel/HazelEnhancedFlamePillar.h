// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Characters/Hazel/HazelFlamePillar.h"
#include "HazelEnhancedFlamePillar.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AHazelEnhancedFlamePillar : public AHazelFlamePillar
{
	GENERATED_BODY()

public:
	virtual void DealDamage(class AOgnamCharacter* Character) override;
};
