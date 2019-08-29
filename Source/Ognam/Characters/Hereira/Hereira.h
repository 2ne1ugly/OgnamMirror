// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Hereira.generated.h"

/**
 *	A Masked Woman
 */
UCLASS()
class OGNAM_API AHereira : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AHereira();

	/*
	**	Binded Function
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/*
	**	Abilities
	*/
	//Basic
	void FireArrow();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerFireArrow();
	bool ServerFireArrow_Validate() { return true; };
	void ServerFireArrow_Implementation();

	//Mobility
	void StartSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStartSprint();
	bool ServerStartSprint_Validate() { return true; };
	void ServerStartSprint_Implementation();

	void StopSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStopSprint();
	bool ServerStopSprint_Validate() { return true; };
	void ServerStopSprint_Implementation();

	void EndSprint();

	//Unique
	void LoadExplosiveShot();

	/*
	**	Props
	*/

	UPROPERTY(VisibleAnywhere, Category = Ability)
	bool bIsExplosiveShot;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	bool bIsReloadingExplosiveShot;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	bool bWillFastReload;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	FTimerHandle SprintDuration;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle BasicReload;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle SprintCooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ExplosiveShotCooldown;
};
