// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "RitualAcolyte.generated.h"

UCLASS()
class OGNAM_API ARitualAcolyte : public AActor, public IInteractable
{
	GENERATED_BODY()

	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* Capsule;

public:	
	ARitualAcolyte();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual float GetInteractDistance() const override;
	virtual void BeInteracted_Implementation(APlayerController* PlayerController)  override;
	virtual bool CanInteractWithController(const APlayerController* PlayerController) const override;
	virtual float GetInteractDuration() const override;

	/*
	**	Getter, Setter
	*/
	UFUNCTION(BlueprintCallable)
	void SetParentShrine(class ARitualShrine* Shrine);

protected:
	/*
	**	Props
	*/
	UPROPERTY()
	class ARitualShrine* ParentShrine;
};
