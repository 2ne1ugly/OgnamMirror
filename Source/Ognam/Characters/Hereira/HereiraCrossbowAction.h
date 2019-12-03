// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "HereiraCrossbowAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraCrossbowAction : public UWeaponActionModifier
{
	GENERATED_BODY()

public:
	UHereiraCrossbowAction();

	virtual void BeginChannel();
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UAudioComponent* ShotSound;

	UPROPERTY()
	class USoundCue* ShotSoundCue;
};
