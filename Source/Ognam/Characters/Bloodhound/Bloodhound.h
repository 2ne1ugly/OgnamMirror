// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Bloodhound.generated.h"

/**
 *	Cthulhu/demon possessed? Steampunk robot machine thing.
 */
UCLASS()
class OGNAM_API ABloodhound : public AOgnamCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Metals[3];

public:
	static const FVector MetalPositions[3];
	static const FVector MetalScales[3];

public:
	ABloodhound();

	virtual void BeginPlay() override;
};
