// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Hereira/HereiraArrow.h"
#include "HereiraExplosiveArrow.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AHereiraExplosiveArrow : public AHereiraArrow
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY()
	class UAudioComponent* AudioSystem;

protected:
	/*
	**	Binded Functions
	*/
	virtual void EndLifeSpan() override;
	virtual void OnCharacterHit(class AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult) override;
	UFUNCTION()
	void OnActorHit(const FHitResult& ImpactResult);

public:
	AHereiraExplosiveArrow();
};
