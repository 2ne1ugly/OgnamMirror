// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraMolotovEmber.generated.h"

UCLASS()
class OGNAM_API AHereiraMolotovEmber : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Trigger;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* BurningAudio;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* BreakingAudio;
public:	
	AHereiraMolotovEmber();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*
	**	Props
	*/
	TArray<class AOgnamCharacter*> AffectedCharacters;
};
