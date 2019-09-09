// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "MaxwellAimDowned.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellAimDowned : public UModifier
{
	GENERATED_BODY()

public:
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
	bool bInterrupted;
};
