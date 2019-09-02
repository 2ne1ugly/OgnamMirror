// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "TimerManager.h"
#include "HereiraSprint.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraSprint : public UModifier
{
	GENERATED_BODY()

public:
	/*
	**	Inherited Funcitons
	*/
	virtual bool ShouldEnd() override;
	virtual void TickModifier(float DeltaTime) override;

	/*
	**	Exported Functions
	*/
	void Interrupt();

protected:
	virtual void BeginModifier() override;
	virtual void EndModifier() override;

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	FTimerHandle Duration;

	UPROPERTY(VisibleAnywhere)
	bool bInterrupted;
};
