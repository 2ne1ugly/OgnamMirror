// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoWeapon.h"
#include "GelasiusShotgun.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UGelasiusShotgun : public USemiAutoWeapon
{
	GENERATED_BODY()
	
public:
	UGelasiusShotgun();
//
//	virtual void FireBullet() override;
//
//	UFUNCTION(NetMulticast, Reliable)
//	void NetDrawTrajectory(FVector From, FVector To);
//	void NetDrawTrajectory_Implementation(FVector From, FVector To);
//
//private:
//	float DamagePerPellet;
//	int32 PelletCount;
//	
//	UPROPERTY(EditAnywhere)
//	float Dist;
};
