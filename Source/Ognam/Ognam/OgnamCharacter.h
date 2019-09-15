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

public:
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
	virtual void OnRep_PlayerState() override;

	void MobilityPressed();
	void MobilityReleased();
	void UniquePressed();
	void UniqueReleased();
	void UtilityPressed();
	void UtilityReleased();
	void SpecialPressed();
	void SpecialReleased();
	void ReloadPressed();
	void ReloadReleased();
	void BasicPressed();
	void BasicReleased();

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

	UFUNCTION(BlueprintCallable)
	class UWeapon* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	class UAbility* GetUnique() const;

	UFUNCTION(BlueprintCallable)
	class UAbility* GetUtility() const;

	UFUNCTION(BlueprintCallable)
	class UAbility* GetSpecial() const;

	UFUNCTION(BlueprintCallable)
	class UAbility* GetMobility() const;

	/*
	**	Exported functions
	*/
	UFUNCTION(NetMulticast, Reliable)
	void Die();
	virtual void Die_Implementation();

	void GetAimHitResult(FHitResult& HitResult, float near, float far);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UModifier*> Modifiers;

	DECLARE_MULTICAST_DELEGATE(FActionDelegate)
	FActionDelegate OnMobilityPressed;
	FActionDelegate OnMobilityReleased;
	FActionDelegate OnUniquePressed;
	FActionDelegate OnUniqueReleased;
	FActionDelegate OnUtilityPressed;
	FActionDelegate OnUtilityReleased;
	FActionDelegate OnSpecialPressed;
	FActionDelegate OnSpecialReleased;
	FActionDelegate OnBasicPressed;
	FActionDelegate OnBasicReleased;
	FActionDelegate OnReloadPressed;
	FActionDelegate OnReloadReleased;

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
	**	Auto-Register
	*/
	UFUNCTION()
	void OnRep_Weapon();

	UFUNCTION()
	void OnRep_Mobility();

	UFUNCTION()
	void OnRep_Unique();

	UFUNCTION()
	void OnRep_Utility();

	UFUNCTION()
	void OnRep_Special();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Replicated)
	bool bIsJumping;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool bIsAlive;

	FVector InputVector;
	float	InputSpeed;
	int		NumInputs;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Weapon)
	class UWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Mobility)
	class UAbility* Mobility;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Unique)
	class UAbility* Unique;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Utility)
	class UAbility* Utility;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Special)
	class UAbility* Special;
};
