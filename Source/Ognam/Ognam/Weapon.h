// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ognam/OgnamEnum.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeapon();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override;

	//Action notify called from weapon action. consider changing this to accept where it is called from.
	virtual void ExecuteWeaponActionNotify();
	virtual void FinishWeaponActionNotify();

	//Defines if can attack.
	virtual bool CanBasic();

	//Cancel reload
	virtual void InterruptReloading();


	/*
	**	Getters, Setters
	*/
	UFUNCTION(BluePrintCallable)
	bool IsReloading() const;

	UFUNCTION(BluePrintCallable)
	int32 GetAmmo() const;

	UFUNCTION(BluePrintCallable)
	int32 GetMaxAmmo() const;

	UFUNCTION(BluePrintCallable)
	bool IsInfinteAmmo() const;

protected:
	virtual void BasicPressed();
	virtual void BasicReleased();
	virtual void SubPressed();
	virtual void SubReleased();

	virtual void ReloadPressed();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerReloadPressed();
	virtual bool ServerReloadPressed_Validate() { return true; };
	virtual void ServerReloadPressed_Implementation();

	virtual void EndReload();

	/*
	**	Props
	*/
	//Commons
	UPROPERTY(Transient, VisibleAnywhere)
	class AOgnamCharacter* Target;

	FDelegateHandle BasicPressHandle;
	FDelegateHandle BasicReleaseHandle;

	bool bBindSub;

	FDelegateHandle SubPressHandle;
	FDelegateHandle SubReleaseHandle;

	EStatusEffect BasicBlockingEffects;

	//Actions
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UWeaponActionModifier> WeaponActionClass;

	UPROPERTY(Transient, VisibleAnywhere)
	class UWeaponActionModifier* WeaponAction;

	//Reload & ammos
	//bInfinite should be set on init Phase
	UPROPERTY(EditAnywhere)
	bool bInfiniteAmmo;

	UPROPERTY(EditAnywhere)
	float ReloadTime;

	UPROPERTY(EditAnywhere, Replicated)
	int32 MaxAmmo;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 Ammo;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bReloading;

	UPROPERTY(EditAnywhere)
	bool bReloadOnNoAmmo;

	FDelegateHandle ReloadPressHandle;

	FTimerHandle ReloadTimer;


};
