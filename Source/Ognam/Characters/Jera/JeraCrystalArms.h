// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/MeleeWeapon.h"
#include "JeraCrystalArms.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraCrystalArms : public UMeleeWeapon
{
	GENERATED_BODY()

public:
	UJeraCrystalArms();

	virtual void BeginPlay() override;

protected:
	virtual void StartPeriSwing() override;
	virtual void StartPostSwing() override;
	virtual void CharacterStrike(class AOgnamCharacter* OtherCharacter) override;

	class UBoxComponent* BoxTrigger;
};
