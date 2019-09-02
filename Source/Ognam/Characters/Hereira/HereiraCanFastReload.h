// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "TimerManager.h"
#include "HereiraCanFastReload.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraCanFastReload : public UModifier
{
	GENERATED_BODY()

public:
	virtual bool ShouldEnd() override;
	virtual void BeginModifier() override;

	/*
	**	Exported Functions
	*/
	bool Use();

protected:
	UPROPERTY(VisibleAnywhere)
	FTimerHandle Duration;

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	bool bUsed;
};
