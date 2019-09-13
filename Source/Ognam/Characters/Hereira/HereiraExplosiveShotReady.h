// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "HereiraExplosiveShotReady.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraExplosiveShotReady : public UModifier
{
	GENERATED_BODY()

public:
	virtual bool ShouldEnd() override;
	void SetAbility(class UHereiraLoadExplosiveShot* LoadShot);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	**	Exported Function
	*/
	bool Use();

protected:
	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Replicated)
	bool bUsed;

	UPROPERTY(VisibleAnywhere)
	UHereiraLoadExplosiveShot* Ability;
};
