// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "MaxwellSniperRifleAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifleAction : public UWeaponActionModifier
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifleAction();

	virtual void BeginPlay() override;

protected:
	virtual void BeginChannel() override;

	UFUNCTION(NetMulticast, Unreliable)
	void NetDrawTrajectory(FVector From, FVector To);
	void NetDrawTrajectory_Implementation(FVector From, FVector To);

	UFUNCTION(NetMulticast, Unreliable)
	void NetPlayShotSound();
	void NetPlayShotSound_Implementation();

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
