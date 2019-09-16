// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "MaxwellShadowShift.generated.h"

/**
 * 
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
	void ServerCastShadowShift();
	bool ServerCastShadowShift_Validate() { return true; };
	void ServerCastShadowShift_Implementation();

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackShadowShift();
	void ClientFeedbackShadowShift_Implementation();

	/*
	**	Props
	*/
	float Cooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ShadowShiftCooldown;
};
