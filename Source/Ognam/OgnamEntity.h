// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Entity is just a thing in game

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Killable.h"
#include "OgnamEntity.generated.h"

UCLASS()
class OGNAM_API AOgnamEntity : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AOgnamEntity();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

protected:

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsAlive;


};
