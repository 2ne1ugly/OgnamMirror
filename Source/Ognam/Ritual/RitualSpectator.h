// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RitualSpectator.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualSpectator : public APawn
{
	GENERATED_BODY()

protected:
	class UCapsuleComponent* CapsuleComponent;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

public:
	ARitualSpectator();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NextPlayerPressed();
	virtual void PrevPlayerPressed();

	UFUNCTION(Server, Unreliable)
	void ServerGetPlayerStatePawn(class APlayerState* TargetPlayerState);
	virtual bool ServerGetPlayerStatePawn_Validate(class APlayerState* TargetPlayerState) { return true; };
	virtual void ServerGetPlayerStatePawn_Implementation(class APlayerState* TargetPlayerState);

	UFUNCTION(Client, Unreliable)
	void ClientRecievePawn(APawn* Pawn);
	virtual void ClientRecievePawn_Implementation(APawn* Pawn);

protected:
	void FindAlivePlayerStates();

	TArray<APlayerState*> AlivePlayerStates;
	int32 index;
};
