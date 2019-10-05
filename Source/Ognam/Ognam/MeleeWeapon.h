// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Weapon.h"
#include "Interfaces/Dispellable.h"
#include "TimerManager.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMeleeWeapon : public UWeapon, public IDispellable
{
	GENERATED_BODY()

public:
	UMeleeWeapon();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	//Client Call
	virtual void BasicPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerBasicPressed();
	virtual bool ServerBasicPressed_Validate() { return true; };
	virtual void ServerBasicPressed_Implementation();

	//Client Call
	virtual void BasicReleased() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerBasicReleased();
	virtual bool ServerBasicReleased_Validate() { return true; };
	virtual void ServerBasicReleased_Implementation();

	//Server Call
	virtual void StartPreSwing();

	//Server Call
	virtual void StartPeriSwing();

	//Server Call
	virtual void StartPostSwing();

	//Server Call
	virtual void EndPostSwing();

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void CharacterStrike(class AOgnamCharacter* OtherCharacter);

	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;

	/*
	**	Props
	*/

	float PreSwing;
	float PeriSwing;
	float PostSwing;

	//One that you must set.
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UPrimitiveComponent> TriggerClass;

	//One that is a component.
	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* Trigger;

	FTimerHandle PreSwingTimer;
	FTimerHandle PeriSwingTimer;
	FTimerHandle PostSwingTimer;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bSwinging;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bWantsToSwing;

	TSet<AOgnamCharacter*> StrikedCharacters;
};
