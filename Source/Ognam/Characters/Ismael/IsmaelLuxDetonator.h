// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IsmaelLuxDetonator.generated.h"

UCLASS()
class OGNAM_API AIsmaelLuxDetonator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIsmaelLuxDetonator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class USphereComponent* Range;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
