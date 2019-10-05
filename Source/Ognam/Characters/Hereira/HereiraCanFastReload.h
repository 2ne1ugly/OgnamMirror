// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "TimerManager.h"
#include "HereiraCanFastReload.generated.h"

/**
 *	This class is not used!
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
	FTimerHandle Duration;

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere)
	bool bUsed;
};
