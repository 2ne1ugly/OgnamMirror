// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/AutoWeapon.h"
#include "JeraCrystalArms.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraCrystalArms : public UAutoWeapon
{
	GENERATED_BODY()

public:
	UJeraCrystalArms();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	//Client Call
	virtual void SubPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSubPressed();
	virtual bool ServerSubPressed_Validate() { return true; }
	virtual void ServerSubPressed_Implementation();

	//Server Call
	virtual void ChargeShard();
	virtual void FireShard();

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 ShardCharge;

	int32 MaxShardCharge;
	float ChargePeriod;

	FTimerHandle ShardChargeTimer;
	FTimerHandle BoxVisualizeTimer;
};
