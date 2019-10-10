// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Weapon.h"
#include "Interfaces/Dispellable.h"
#include "TimerManager.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMeleeWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	UMeleeWeapon();
	virtual void BeginPlay() override;

protected:
	//Client Call
	virtual void BasicPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerBasicPressed();
	virtual bool ServerBasicPressed_Validate() { return true; };
	virtual void ServerBasicPressed_Implementation();

	//Client Call
	virtual void BasicReleased() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerBasicReleased();
	virtual bool ServerBasicReleased_Validate() { return true; };
	virtual void ServerBasicReleased_Implementation();

	/*
	**	Props
	*/
	//One that you must set.
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UWeaponActionModifier> SwingClass;

	UPROPERTY(Transient, VisibleAnywhere)
	class UWeaponActionModifier* Swing;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bWantsToSwing;
};
