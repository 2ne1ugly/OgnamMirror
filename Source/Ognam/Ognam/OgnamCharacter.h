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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Jump() override;
	virtual void Landed(const FHitResult & Hit) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	virtual void MoveForward(float amount);
	virtual void MoveRight(float amount);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsJumping() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	/*
	**	Exported functions
	*/
	UFUNCTION(NetMulticast, Reliable)
	void Die();
	virtual void Die_Implementation();

	void GetAimHitResult(FHitResult& HitResult, float near, float far);

	/*
	**	Exported Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterSpecificHUDClass;

protected:
	/*
	**	Internal functions
	*/
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerJump();
	virtual bool ServerJump_Validate() { return true; };
	virtual void ServerJump_Implementation();

	float GetDamageAfterDefense(float Damage);

	/*
	**	Props
	*/
	UPROPERTY(Replicated)
	float Health;

	UPROPERTY(Replicated)
	float MaxHealth;

	UPROPERTY(Replicated)
	float Defense;

	UPROPERTY(Replicated)
	bool bIsJumping;

	UPROPERTY(Replicated)
	bool bIsAlive;
};
