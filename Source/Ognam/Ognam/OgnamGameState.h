// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "OgnamGameState.generated.h"



/**
 *	This state should never be used.
 *	Not even meant for inheritance
 */
UCLASS()
class OGNAM_API AOgnamGameState : public AGameState
{
	GENERATED_BODY()

public:
	AOgnamGameState();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyDamageEvent(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage);
	virtual void NotifyKillEvent(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	FString GetServerIP() const;

	UFUNCTION(NetMulticast, Reliable)
	void AddPlayerKilled(class AOgnamPlayerState* Killer, class AOgnamPlayerState* Receiver);
	void AddPlayerKilled_Implementation(class AOgnamPlayerState* Killer, class AOgnamPlayerState* Receiver);

	UFUNCTION()
	void RemoveFromKillFeed();

	virtual float GetServerWorldTimeSeconds() const override;

protected:
	UPROPERTY(Transient, Replicated)
	FString ServerAddress;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UKillFeed*> KillFeed;
};
