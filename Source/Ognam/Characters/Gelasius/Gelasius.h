// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Gelasius.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AGelasius : public AOgnamCharacter
{
	GENERATED_BODY()
	
public:
	AGelasius();

	virtual void BeginPlay() override;
};
