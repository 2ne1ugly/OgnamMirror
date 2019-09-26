// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/MeleeWeapon.h"
#include "JeraCrystalArms.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraCrystalArms : public UMeleeWeapon
{
	GENERATED_BODY()

public:
	UJeraCrystalArms();

	virtual void BeginPlay() override;

protected:
	virtual void StartPeriSwing() override;
	virtual void StartPostSwing() override;

	UFUNCTION(NetMulticast, Unreliable)
	void NetStartPeriSwing();
	void NetStartPeriSwing_Implementation();

	void EndPeriSwing();


	virtual void CharacterStrike(class AOgnamCharacter* OtherCharacter) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SubPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSubPressed();
	virtual bool ServerSubPressed_Validate() { return true; }
	virtual void ServerSubPressed_Implementation();

	//Server Call
	virtual void ChargeShard();

	//Server Call
	virtual void FireShard();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* DamageBoxMaterial;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* DamageBoxMesh;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 ShardCharge;

	int32 MaxShardCharge;
	float ChargePeriod;

	FTimerHandle ShardChargeTimer;
	FTimerHandle BoxVisualizeTimer;
};
