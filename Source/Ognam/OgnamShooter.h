// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamCharacter.h"
#include "OgnamShooter.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamShooter : public AOgnamCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Replicated)
	int32 Ammo;

	UPROPERTY(EditAnywhere, Replicated)
	int32 MaxAmmo;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo() const;

public:
	AOgnamShooter();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
