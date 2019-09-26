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

protected:
	virtual void BasicPressed() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerBasicPressed();
	bool ServerBasicPressed_Validate() { return true; }
	virtual void ServerBasicPressed_Implementation();

	//Server call
	virtual void FireBullet();

	virtual void EndPostDelay();

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	float RoundsPerSecond;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	FTimerHandle PostDelay;

	UPROPERTY(EditAnywhere, Replicated)
	bool bCanFire;

	EStatusEffect UnacceptedStatusEffects;
};
