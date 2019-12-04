// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "Interfaces/Dispellable.h"
#include "MaxwellVaultModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellVaultModifier : public UModifier, public IDispellable
{
	GENERATED_BODY()

public:
	UMaxwellVaultModifier();

	virtual bool ShouldEnd() override;

	virtual void TickModifier(float DeltaTime) override;

	virtual void StatusEffectApplied(EStatusEffect StatusEffect);
	virtual void ActionTaken(EActionNotifier ActionType);

	virtual void BeginModifier() override;

protected:
	bool bInterrupt;

private:
	class USoundCue* VaultCue;
};
