// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Modifier.h"
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
	virtual void Tick(float DeltaTime) override;
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
	void ApplyModifier(class UModifier* Modifier);

	template<typename T>
	T* GetModifier()
	{
		for (UModifier* Modifier : Modifiers)
		{
			T* Casted = Cast<T>(Modifier);
			if (Casted != nullptr)
			{
				return Casted;
			}
		}
		return nullptr;
	}

	/*
	**	Exported Props
	*/
	UPROPERTY(VisibleAnywhere, Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere, Replicated)
	float BaseMaxHealth;

	UPROPERTY(VisibleAnywhere, Replicated)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Replicated)
	float BaseDefense;

	UPROPERTY(VisibleAnywhere, Replicated)
	float Defense;

	UPROPERTY(VisibleAnywhere, Replicated)
	float BaseSpeed;

	UPROPERTY(VisibleAnywhere, Replicated)
	float Speed;

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
	UPROPERTY(VisibleAnywhere, Replicated)
	bool bIsJumping;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool bIsAlive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly	)
	TArray<UModifier*> Modifiers;
};
