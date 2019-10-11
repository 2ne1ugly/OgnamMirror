// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoWeapon.h"
#include "Interfaces/Dispellable.h"
#include "HereiraCrossbow.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraCrossbow : public USemiAutoWeapon, public IDispellable
{
	GENERATED_BODY()

public:
	UHereiraCrossbow();

	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;

};
