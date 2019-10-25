// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	void ClientFeedbackUsed(float TimeStamp);
	void ClientFeedbackUsed_Implementation(float TimeStamp);
	/*
	**	Props
	*/
	float Cooldown;

	FTimerHandle CooldownTimer;

	EStatusEffect UnacceptedStatusEffects;
};
