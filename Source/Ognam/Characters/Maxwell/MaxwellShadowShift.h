// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "MaxwellShadowShift.generated.h"

/**
 *	Issue: Fix the jitter from client side(Maybe find a way to sync modifier timers)
 */
UCLASS()
class OGNAM_API UMaxwellShadowShift : public UActiveAbility
{
	GENERATED_BODY()

public:
	UMaxwellShadowShift();

	virtual bool ShouldShowNumber() const override;
	virtual float GetNumber() const override;

protected:
	//Client call
	virtual void OnButtonPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerCastShadowShift(FVector Direction);
	bool ServerCastShadowShift_Validate(FVector Direction) { return true; }
	void ServerCastShadowShift_Implementation(FVector Direction);

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackShadowShift();
	void ClientFeedbackShadowShift_Implementation();

	/*
	**	Props
	*/
	float Cooldown;

	FTimerHandle ShadowShiftCooldown;
	UAnimMontage* RootMotion;
};
