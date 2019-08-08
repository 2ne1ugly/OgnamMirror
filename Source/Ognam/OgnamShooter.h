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

	void Shoot();
	void StopShoot();
	void Reload();
	void Aim();
	void StopAim();

	virtual void MoveForward(float Amount) override;
	virtual void MoveRight(float Amount) override;

	UPROPERTY(BlueprintReadOnly)
	bool IsAiming;
	UPROPERTY(BlueprintReadOnly)
	bool IsShooting;
	UPROPERTY(BlueprintReadOnly)
	bool IsReloading;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
