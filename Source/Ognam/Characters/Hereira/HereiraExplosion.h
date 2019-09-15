// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraExplosion.generated.h"

UCLASS()
class OGNAM_API AHereiraExplosion : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USphereComponent* Range;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* AudioSystem;

public:	
	AHereiraExplosion();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnCharacterHit(class AOgnamCharacter* OtherCharacter);
	void OnActorHit(class AActor* OtherActor);

	/*
	**	Props
	*/
	void EndLifeSpan();
	void EndTriggerLifeSpan();

	UPROPERTY(VisibleAnywhere)
	FTimerHandle LifeSpan;

	UPROPERTY(VisibleAnywhere)
	FTimerHandle TriggerLifeSpan;

	UPROPERTY()
	TSet<AActor*> AffectedActors;

	float BaseDamage;
};
