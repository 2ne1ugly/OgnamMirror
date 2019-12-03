// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "MaxwellVault.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellVault : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UMaxwellVault();

protected:
	virtual void ActivateAbility() override;
	virtual void ApplyModifier();

private:
	class USoundCue* VaultCue;
};
