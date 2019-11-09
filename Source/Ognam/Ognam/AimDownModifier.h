// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "AimDownModifier.generated.h"

/**
 *	Used with weapons
 */
UCLASS()
class OGNAM_API UAimDownModifier : public UModifier
{
	GENERATED_BODY()

public:
	UAimDownModifier();

	void StartAimDown();
	void StopAimDown();

	virtual void TickModifier(float DeltaTime) override;
	virtual bool IsSupportedForNetworking() const override;

protected:

	/*
	**	Props
	*/
	bool bAimDowned;
	float FocusTime;
	float MaxFocusTime;
};
