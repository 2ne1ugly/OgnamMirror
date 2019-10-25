// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Hazel.generated.h"

/**
 *	Flame Wizard
 */
UCLASS()
class OGNAM_API AHazel : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AHazel();

	virtual void BeginPlay() override;
};
