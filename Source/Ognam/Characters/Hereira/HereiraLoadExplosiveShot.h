// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "HereiraLoadExplosiveShot.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraLoadExplosiveShot : public UActiveAbility
{
	GENERATED_BODY()

public:
	UHereiraLoadExplosiveShot();

	virtual bool ShouldShowNumber() const;
	virtual float GetNumber() const;

	//Server Side
	void FiredExplosiveShot();

protected:
	//Client Side
	virtual void OnButtonPressed() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerLoadExplosiveShot();
	bool ServerLoadExplosiveShot_Validate() { return true; };
	void ServerLoadExplosiveShot_Implementation();

	UFUNCTION(Client, Unreliable)
	void ClientFiredExplosiveShot();
	void ClientFiredExplosiveShot_Implementation();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ExplosiveShotCooldown;
};
