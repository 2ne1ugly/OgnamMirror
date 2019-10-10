// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoWeapon.h"
#include "MaxwellSniperRifle.generated.h"

/**
 *	Vampire Sniper
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifle : public USemiAutoWeapon
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifle();

	virtual void BeginPlay() override;

protected:
	//Basic
	//Server call
	virtual void FireBullet();

	UFUNCTION(NetMulticast, Unreliable)
	void NetDrawTrajectory(FVector From, FVector To);
	void NetDrawTrajectory_Implementation(FVector From, FVector To);

	UFUNCTION(NetMulticast, Unreliable)
	void NetPlayShotSound();
	void NetPlayShotSound_Implementation();

	friend class AOgnamCharacter;

	//Sub
	//Client call
	virtual void SubPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerToggleAimDown();
	bool ServerToggleAimDown_Validate() { return true; };
	void ServerToggleAimDown_Implementation();

	/*
	**	Props
	*/
	float BaseDamage;

	UPROPERTY()
	class UParticleSystem* ParticleSystem;

	UPROPERTY()
	class USoundCue* ShotSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* ShotSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ShotTrail;
};
