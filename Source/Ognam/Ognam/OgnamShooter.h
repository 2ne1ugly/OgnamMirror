// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamCharacter.h"
#include "OgnamShooter.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamShooter : public AOgnamCharacter
{
	GENERATED_BODY()
	
public:
	AOgnamShooter();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Shoot();
	void StopShoot();
	void Reload();
	void StopReload();
	void Aim();
	void StopAim();
	virtual void MoveForward(float Amount) override;
	virtual void MoveRight(float Amount) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;
	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsAiming() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsShooting() const;
	UFUNCTION(BlueprintCallable)
	bool GetIsReloading() const;

protected:
	/*
	**	Internal functions
	*/
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSetIsAiming(bool NewValue);
	virtual bool ServerSetIsAiming_Validate(bool NewValue) { return true; };
	virtual void ServerSetIsAiming_Implementation(bool NewValue);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSetIsShooting(bool NewValue);
	virtual bool ServerSetIsShooting_Validate(bool NewValue) { return true; };
	virtual void ServerSetIsShooting_Implementation(bool NewValue);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSetIsReloading(bool NewValue);
	virtual bool ServerSetIsReloading_Validate(bool NewValue) { return true; };
	virtual void ServerSetIsReloading_Implementation(bool NewValue);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerFireBullet();
	virtual bool ServerFireBullet_Validate() { return true; };
	virtual void ServerFireBullet_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void FireBullet(FVector From, FVector Direction);
	virtual void FireBullet_Implementation(FVector From, FVector Direction);

	/*
	**	Props
	*/
	UPROPERTY(Replicated)
	int32 Ammo;

	UPROPERTY(Replicated)
	int32 MaxAmmo;

	UPROPERTY(Replicated)
	bool bIsAiming;

	UPROPERTY(Replicated)
	bool bIsShooting;

	UPROPERTY(Replicated)
	bool bIsReloading;
};
