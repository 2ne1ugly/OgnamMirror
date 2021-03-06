// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeraPunchImpact.generated.h"

UCLASS()
class OGNAM_API AJeraPunchImpact : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* BulletImpactSystem;

public:	
	// Sets default values for this actor's properties
	AJeraPunchImpact();

	UFUNCTION()
	void OnNiagaraCompleted(class UNiagaraComponent* PSystem);

protected:


	virtual void Tick(float DeltaTime) override;
};
