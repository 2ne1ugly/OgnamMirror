// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "MaxwellShadowForm.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellShadowForm : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UMaxwellShadowForm();

	virtual void TickModifier(float DeltaTime) override;
	virtual void BeginModifier() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UAudioComponent* ShiftSound;

	UPROPERTY()
	class USoundCue* ShiftSoundCue;
};
