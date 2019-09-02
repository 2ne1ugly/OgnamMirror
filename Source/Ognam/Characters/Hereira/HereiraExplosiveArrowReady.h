// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "HereiraExplosiveArrowReady.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraExplosiveArrowReady : public UModifier
{
	GENERATED_BODY()

public:
	virtual bool ShouldEnd() override;

	/*
	**	Exported Function
	*/
	bool Use();

protected:
	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	bool bUsed;
};
