// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OgnamEnum.h"
#include "OgnamCharacter.generated.h"

USTRUCT(Blueprintable)
struct FCharacterInfo {
	GENERATED_USTRUCT_BODY()
	// character name
	UPROPERTY(BlueprintReadWrite)
	FText	CharacterName;
	// character image
	UPROPERTY(BlueprintReadWrite)
	class UTexture2D*	CharacterImage;
	//character description

	UPROPERTY(BlueprintReadWrite)
	FText	CharacterDescription;
	// ability icons

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D*	MobilityIcon;

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D*	UniqueIcon;

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D*	SpecialIcon;

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D*	UtilityIcon;

	// ability descriptions
	UPROPERTY(BlueprintReadWrite)
	FText	MobilityDes;

	UPROPERTY(BlueprintReadWrite)
	FText	UniqueDes;

	UPROPERTY(BlueprintReadWrite)
	FText	SpecialDes;

	UPROPERTY(BlueprintReadWrite)
	FText	UtilityDes;
};

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
	void MoveForwardAction();
	void MoveBackwardAction();
	void MoveRightAction();
	void MoveLeftAction();
	void MoveForwardActionRelease();
	void MoveBackwardActionRelease();
	void MoveRightActionRelease();
	void MoveLeftActionRelease();
	void TacticalPressed();
	void TacticalReleased();

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
	const FCharacterInfo& GetInfo() const;

	FCharacterInfo Info;

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

	bool HasStatusEffect(EStatusEffect Query) const;
	void TakeAction(EActionNotifier ActionType);
	void ApplyStatusEffect(const TSet<EStatusEffect>& Effects);
	void RemoveStatusEffect(const TSet<EStatusEffect>& Effects);
	/*
	**	Exported Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere)
	float BaseMaxHealth;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth;

	//Per second
	UPROPERTY(VisibleAnywhere)
	float BaseHealthRegen;

	UPROPERTY(VisibleAnywhere)
	float HealthRegen;

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
	TMap<EStatusEffect, int> StatusEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHitResult> CameraHits;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlane CameraBlockingPlane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTexture2D* CharacterIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTexture2D* CharacterImage;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetIcon() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetImage() const;

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
	void PlayerStateReady();

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsJumping;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsAlive;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bForward;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bBackward;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bRight;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bLeft;

	UPROPERTY(Transient, VisibleAnywhere)
	bool bTactical;

	UPROPERTY(Transient, VisibleAnywhere)
	float TacticalAmount;

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


	UPROPERTY(VisibleAnywhere)
	class UMaterial* DamageRecievedMaterial;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* TacticalModeMaterial;

	UPROPERTY(VisibleAnywhere)
	class UMaterialInstanceDynamic* DamageInstance;

	UPROPERTY(VisibleAnywhere)
	class UMaterialInstanceDynamic* TacticalInstance;

	UPROPERTY(VisibleAnywhere)
	class UTextBlock* NameTag;

	UPROPERTY(VisibleAnywhere)
	class UOgnamWidgetComponent* NameTagComponent;

	UPROPERTY()
	class USoundCue* WalkingSoundCue;

	UPROPERTY()
	class UAudioComponent* JumpStart;

	UPROPERTY()
	class UAudioComponent* JumpEnd;

	UFUNCTION(NetMulticast, Reliable)
	void NetJumpStart();
	virtual void NetJumpStart_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void NetJumpLand();
	virtual void NetJumpLand_Implementation();
};
