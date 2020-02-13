// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraBulletImpact.generated.h"

UCLASS()
class OGNAM_API AHereiraBulletImpact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHereiraBulletImpact();

	UFUNCTION()
	void OnNiagaraCompleted(class UNiagaraComponent* PSystem);

protected:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* BulletImpactSystem;

	virtual void Tick(float DeltaTime) override;

};
