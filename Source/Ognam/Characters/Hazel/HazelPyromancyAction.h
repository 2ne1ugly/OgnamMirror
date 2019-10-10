// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "Interfaces/Dispellable.h"
#include "HazelPyromancyAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelPyromancyAction : public UWeaponActionModifier, public IDispellable
{
	GENERATED_BODY()

public:
	UHazelPyromancyAction();

protected:
	virtual void BeginChannel() override;
	virtual void ExecutePostDelay() override;

	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;
};
