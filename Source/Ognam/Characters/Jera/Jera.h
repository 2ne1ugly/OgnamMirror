// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Jera.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AJera : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AJera();

	virtual void BeginPlay() override;
};
