// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ClipWeapon.h"
#include "Ognam/OgnamEnum.h"
#include "SemiAutoClipWeapon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API USemiAutoClipWeapon : public UClipWeapon
{
	GENERATED_BODY()

public:
	USemiAutoClipWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere)
	bool bFireOnRelease;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool bCharging;

	UPROPERTY(EditAnywhere)
	bool bReloadOnNoAmmo;

protected:
	virtual void BasicPressed() override;
	virtual void BasicReleased() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerBasicPressed();
	bool ServerBasicPressed_Validate() { return true; }
	virtual void ServerBasicPressed_Implementation();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerBasicReleased();
	bool ServerBasicReleased_Validate() { return true; }
	virtual void ServerBasicReleased_Implementation();

	//Server call
	virtual void PreFireBullet();
	virtual void FireBullet();
	virtual void PostFireBullet();

	virtual void EndPostDelay();

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	float RoundsPerSecond;

	FTimerHandle PostDelay;

	UPROPERTY(Transient, EditAnywhere, Replicated)
	bool bCanFire;

	EStatusEffect UnacceptedStatusEffects;
};
