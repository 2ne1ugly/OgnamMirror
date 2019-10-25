// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/Ability.h"
#include "HazelLightenedWill.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelLightenedWill : public UAbility
{
	GENERATED_BODY()
	
public:
	UHazelLightenedWill();

	virtual void BeginPlay() override;
};
