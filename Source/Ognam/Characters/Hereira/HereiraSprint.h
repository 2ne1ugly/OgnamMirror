// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "TimerManager.h"
#include "HereiraSprint.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraSprint : public UActiveAbility
{
	GENERATED_BODY()

public:
	UHereiraSprint();

	virtual bool ShouldShowNumber() const;
	virtual float GetNumber() const;

	UFUNCTION(Client, Unreliable)
	void ClientEndSprint();
	void ClientEndSprint_Implementation();

protected:
	virtual void OnButtonPressed() override;
	virtual void OnButtonReleased() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStartSprint();
	bool ServerStartSprint_Validate() { return true; };
	void ServerStartSprint_Implementation();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStopSprint();
	bool ServerStopSprint_Validate() { return true; };
	void ServerStopSprint_Implementation();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle SprintCooldown;
};
