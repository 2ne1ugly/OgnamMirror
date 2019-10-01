// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ClipWeapon.h"
#include "AutoClipWeapon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UAutoClipWeapon : public UClipWeapon
{
	GENERATED_BODY()

public:
	UAutoClipWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	virtual void StartFireBullet();
	virtual void RepeatFireBullet();
	virtual void EndFireBullet();

	virtual void PreFireBullet();
	virtual void FireBullet();
	virtual void PostFireBullet();

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	float RoundsPerSecond;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	FTimerHandle PostDelay;

	UPROPERTY(EditAnywhere, Replicated)
	bool bFiring;

	bool bWantsToFire;
	bool bInfiniteAmmo;

	EStatusEffect UnacceptedStatusEffects;
};
