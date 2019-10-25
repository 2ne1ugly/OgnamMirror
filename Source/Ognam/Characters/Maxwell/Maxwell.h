// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Maxwell.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AMaxwell : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AMaxwell();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
};
