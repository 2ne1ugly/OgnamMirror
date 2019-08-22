// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OgnamCharacter.generated.h"

// Contains What's common between every Character.
UCLASS()
class OGNAM_API AOgnamCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere, category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, category = Camera)
	class UCameraComponent* Camera;

public:
	AOgnamCharacter();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;

	virtual void Landed(const FHitResult & Hit) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	virtual void MoveForward(float amount);

	virtual void MoveRight(float amount);

	void OgnamCrouch();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	int32 GetTeamID() const;

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsJumping() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsCrouched() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool CanInteract() const;

	/*
	**	Exported functions
	*/
	UFUNCTION(NetMulticast, Reliable)
	void Die();
	virtual void Die_Implementation();

	void GetAimHitResult(FHitResult& HitResult, float Dist);

	/*
	** Uses GetAimHitResult() to attempt to find something it can interact with.
	** If it is successful, bCanInteract is set to true
	*/
	void CheckForInteract();


protected:
	/*
	**	Internal functions
	*/
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerJump();
	virtual bool ServerJump_Validate() { return true; };
	virtual void ServerJump_Implementation();

	/*
	**	Props
	*/
	UPROPERTY(Replicated)
	int32 TeamID;

	UPROPERTY(Replicated)
	float Health;

	UPROPERTY(Replicated)
	float MaxHealth;

	UPROPERTY(Replicated)
	bool bIsJumping;

	UPROPERTY(Replicated)
	bool bIsAlive;

	bool bCanInteract;
};
