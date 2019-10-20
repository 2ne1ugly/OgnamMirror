// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinimapAnchor.generated.h"

UCLASS()
class OGNAM_API AMinimapAnchor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinimapAnchor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FVector2D FindScaledOffset(AActor* FromActor);

	UPROPERTY(EditAnywhere)
	float Scale;

	UPROPERTY(EditAnywhere)
	FVector2D Offset;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* AnchorMesh;

};
