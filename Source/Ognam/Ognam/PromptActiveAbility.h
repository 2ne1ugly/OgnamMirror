// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "PromptActiveAbility.generated.h"

/**
 *	ActiveAbility that immediately reacts to button press and runs cooldown
 *	Takes no input when sent to server
 */
UCLASS()
class OGNAM_API UPromptActiveAbility : public UActiveAbility
{
	GENERATED_BODY()

public:
	UPromptActiveAbility();

	virtual bool ShouldShowNumber() const override final;
	virtual float GetNumber() const override final;

protected:
	//Client Call
	virtual void OnButtonPressed() override final;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerOnButtonPressed();
	virtual bool ServerOnButtonPressed_Validate() { return true; };
	virtual void ServerOnButtonPressed_Implementation();

	//Server Call
	virtual void ActivateAbility();

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackUsed();
	void ClientFeedbackUsed_Implementation();
	/*
	**	Props
	*/
	float Cooldown;

	FTimerHandle CooldownTimer;

	EStatusEffect UnacceptedStatusEffects;
};
