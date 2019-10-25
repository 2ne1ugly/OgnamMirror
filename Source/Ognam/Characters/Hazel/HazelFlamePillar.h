// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazelFlamePillar.generated.h"

UCLASS()
class OGNAM_API AHazelFlamePillar : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Collision;

public:
	AHazelFlamePillar();

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ActivateCollision();

	virtual void DealDamage(class AOgnamCharacter* Character);

	/*
	**	Props
	*/
	float BaseDamage;
	float ActivationTime;
	FTimerHandle ActivationTimer;

	TSet<class AOgnamCharacter*> AffectedCharacters;
};
