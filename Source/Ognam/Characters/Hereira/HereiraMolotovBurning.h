// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "HereiraMolotovBurning.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraMolotovBurning : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UHereiraMolotovBurning();

	void ResetDuration();
	void SetInstigator(APawn* _Instigator);
	virtual bool ShouldEnd() override;

protected:
	virtual void BeginModifier() override;
	void TickDamage();

	FTimerHandle TickTimer;

	//UPROPERTY(Replicated)
	APawn* Instigator;
};
