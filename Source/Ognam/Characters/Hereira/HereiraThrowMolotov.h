// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "HereiraThrowMolotov.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraThrowMolotov : public UActiveAbility
{
	GENERATED_BODY()

public:
	UHereiraThrowMolotov();

	virtual bool ShouldShowNumber() const;
	virtual float GetNumber() const;

protected:
	virtual void OnButtonPressed() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerThrowMolotov();
	bool ServerThrowMolotov_Validate() { return true; };
	void ServerThrowMolotov_Implementation();

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackThrowMolotov();
	void ClientFeedbackThrowMolotov_Implementation();

	/*
	**	Props
	*/
	float Cooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle MolotovCooldown;
};
