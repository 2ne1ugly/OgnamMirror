// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "HereiraSprint.h"
#include "HereiraSprinting.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraSprinting : public UModifier
{
	GENERATED_BODY()


public:
	UHereiraSprinting();

	/*
	**	Inherited Funcitons
	*/
	virtual bool ShouldEnd() override;
	virtual void TickModifier(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	**	Exported Functions
	*/
	void SetAbility(UHereiraSprint* SprintAbility);
	void Interrupt();

protected:
	virtual void BeginModifier() override;
	virtual void EndModifier() override;

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	FTimerHandle Duration;

	UPROPERTY(VisibleAnywhere, Replicated)
	UHereiraSprint* Ability;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool bInterrupted;

};
