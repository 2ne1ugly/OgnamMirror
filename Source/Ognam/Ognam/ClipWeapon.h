// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Weapon.h"
#include "ClipWeapon.generated.h"

/**
 *	Weapon With reloads that makes its ammo full.
 *	It is also automatically reloaded when ammo is out.
 *	Reload always takes some interval. And handled equally.
 */
UCLASS()
class OGNAM_API UClipWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	UClipWeapon();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BluePrintCallable)
	bool IsReloading() const;

	UFUNCTION(BluePrintCallable)
	int32 GetAmmo() const;

	UFUNCTION(BluePrintCallable)
	int32 GetMaxAmmo() const;

protected:
	//ClientCall
	virtual void Reload();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerReload();
	bool ServerReload_Validate() { return true; };
	virtual void ServerReload_Implementation();

	//ServerCall
	virtual void EndReload();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ReloadTimer;

	UPROPERTY(VisibleAnywhere)
	float ReloadTime;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool bReloading;

	FDelegateHandle ReloadPressHandle;
};
