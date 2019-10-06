// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "BloodhoundLeap.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundLeap : public UModifier
{
	GENERATED_BODY()

public:
	UBloodhoundLeap();

	virtual bool ShouldEnd() override;
	virtual void BeginModifier() override;
	virtual void TickModifier(float DeltaTime) override;
	virtual void EndModifier() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

protected:
	bool bHit;
	FDelegateHandle HitHandle;
};
