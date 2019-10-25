// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Hereira.generated.h"

/**
 *	A Masked Woman
 */
UCLASS()
class OGNAM_API AHereira : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AHereira();
	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
};
