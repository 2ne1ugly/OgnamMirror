// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	virtual void TickPostDelay(float DeltaTime) override;

	virtual void ExecutePostDelay() override;



	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;
};
