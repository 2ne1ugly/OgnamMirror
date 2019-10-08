// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OgnamPlayerState.generated.h"

/**
 *	Put things that are common
 */
UCLASS()
class OGNAM_API AOgnamPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOgnamPlayerState();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	virtual void OverrideWith(class APlayerState* PlayerState) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetTeam(FName name);

	UFUNCTION(BlueprintCallable)
	FName GetTeam() const;

	UFUNCTION(Netmulticast, Unreliable)
	void NetReceiveMessage(const FString& Message, class APlayerState* Sender);
	void NetReceiveMessage_Implementation(const FString& Message, class APlayerState* Sender);

	UFUNCTION(Server, Unreliable)
	void ServerSendMessage(const FString& Message);
	void ServerSendMessage_Implementation(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void DisplayMessage(const FString& Message, class APlayerState* Sender);

protected:

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	FString Name;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	FName Team;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 NumKill;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 NumDeath;
};
