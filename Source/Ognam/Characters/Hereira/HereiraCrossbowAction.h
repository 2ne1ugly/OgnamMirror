// Copyright 2019 Ognam Studios. All Rights Reserved.
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
