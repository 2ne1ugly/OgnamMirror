// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/MeleeWeapon.h"
#include "BloodhoundClaws.generated.h"

/**
 *	Todo: make leap attack.
 */
UCLASS()
class OGNAM_API UBloodhoundClaws : public UMeleeWeapon
{
	GENERATED_BODY()

public:
	UBloodhoundClaws();

	virtual void BeginPlay() override;

protected:
	virtual void ServerBasicPressed_Implementation() override;

	virtual void StartPeriSwing() override;

	UFUNCTION(NetMulticast, Unreliable)
	void NetStartPeriSwing();
	void NetStartPeriSwing_Implementation();

	void EndPeriSwing();

	virtual void CharacterStrike(class AOgnamCharacter* OtherCharacter) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* DamageBoxMaterial;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* DamageBoxMesh;

	FTimerHandle BoxVisualizeTimer;
};
