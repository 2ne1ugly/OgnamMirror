// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OgnamEnum.h"
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

	UPROPERTY(EditAnywhere)
	class UOverwallHidden* OverwallHidden;


public:
	AOgnamCharacter();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void Jump() override;
	virtual void Landed(const FHitResult & Hit) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	virtual void MoveForward(float amount);
	virtual void MoveRight(float amount);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnRep_PlayerState() override;
	virtual void PossessedBy(AController* aController) override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

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
	void SubPressed();
	void SubReleased();

	/*
	**	Testing functions
	*/
	UFUNCTION(BlueprintCallable)
	void SetCamera(float ArmLength, FVector SocketOffset, float FOV);

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

	UFUNCTION(BlueprintCallable)
	bool CanMove() const;

	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool b);

	UFUNCTION(BlueprintCallable)
	class USoundCue* GetWalkingSound() const;

	UFUNCTION(BlueprintCallable)
	FVector GetInputVector() const;
	/*
	**	Exported functions
	*/
	UFUNCTION(NetMulticast, Reliable)
	void NetDie();
	virtual void NetDie_Implementation();

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

	bool HasStatusEffect(EStatusEffect StatusEffect);
	void TakeAction(EActionNotifier ActionType);
	void ApplyStatusEffect(EStatusEffect StatusEffect);
	/*
	**	Exported Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere)
	float BaseMaxHealth;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float BaseDefense;

	UPROPERTY(Transient, VisibleAnywhere)
	float Defense;

	UPROPERTY(VisibleAnywhere)
	float BaseSpeed;

	UPROPERTY(Transient, VisibleAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere)
	float BaseAcceleration;

	UPROPERTY(Transient, VisibleAnywhere)
	float Acceleration;

	UPROPERTY(VisibleAnywhere)
	float BaseAirControl;

	UPROPERTY(Transient, VisibleAnywhere)
	float AirControl;

	UPROPERTY(VisibleAnywhere)
	float BaseGravity;

	UPROPERTY(Transient, VisibleAnywhere)
	float Gravity;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bCanMove;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly)
	FText CharacterName;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterSpecificHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UModifier*> Modifiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHitResult> CameraHits;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlane CameraBlockingPlane;

	bool bCameraBlocked;

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
	FActionDelegate OnSubPressed;
	FActionDelegate OnSubReleased;
	FActionDelegate OnReloadPressed;
	FActionDelegate OnReloadReleased;

	FTimerHandle DamageTimer;

protected:
	/*
	**	Internal functions
	*/
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerJump();
	virtual bool ServerJump_Validate() { return true; };
	virtual void ServerJump_Implementation();

	float GetDamageAfterDefense(float Damage);
	float GetSpeedFromVector(FVector Vector);
	void UpdateCameraBlockingPlane();

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsJumping;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsAlive;

	FVector InputVector;
	float	InputAmount;
	int		NumInputs;

	UPROPERTY(VisibleAnywhere)
	class UWeapon* Weapon;

	UPROPERTY(VisibleAnywhere)
	class UAbility* Mobility;

	UPROPERTY(VisibleAnywhere)
	class UAbility* Unique;

	UPROPERTY(VisibleAnywhere)
	class UAbility* Utility;

	UPROPERTY(VisibleAnywhere)
	class UAbility* Special;

	class UMaterial* DamageRecievedMaterial;
	class UMaterialInstanceDynamic* DamageInstance;

	UPROPERTY(VisibleAnywhere)
	class UTextBlock* NameTag;

	UPROPERTY(VisibleAnywhere)
	class UOgnamWidgetComponent* NameTagComponent;

	UPROPERTY()
	class USoundCue* WalkingSoundCue;
};
