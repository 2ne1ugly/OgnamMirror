// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OgnamCharacter.generated.h"

UCLASS()
class OGNAM_API AOgnamCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, category = Camera)
	class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AOgnamCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Jump() override;

	virtual void Landed(const FHitResult & Hit) override;

	virtual void Crouch();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, Replicated)
	int TeamID;

	UPROPERTY(EditAnywhere, Replicated)
	float Health;

	UPROPERTY(EditAnywhere, Replicated)
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	bool IsJumping;

	virtual void MoveForward(float amount);
	virtual void MoveRight(float amount);
};
