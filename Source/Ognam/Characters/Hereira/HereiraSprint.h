// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "TimerManager.h"
#include "Interfaces/Dispellable.h"
#include "HereiraSprint.generated.h"

/**
 *	Potentially make it use action modifier.
 */
UCLASS()
class OGNAM_API UHereiraSprint : public UActiveAbility, public IDispellable
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
	**	Dispellable interface
	*/
	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;

	/*
	**	Props
	*/
	float Cooldown;

	FTimerHandle SprintCooldown;
};
