// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OgnamStatics.generated.h"

enum class EDamageMethod : uint64;

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    static bool CanDamage(const UObject* WorldContextObject, class AOgnamPlayerState* DamageInstigator, class AOgnamPlayerState* Reciever, EDamageMethod DamageMethod);
    static bool CanDamage(const UObject* WorldContextObject, class APawn* DamageInstigator, class APawn* Reciever, EDamageMethod DamageMethod);

    UFUNCTION(BlueprintCallable, Category = "Audio", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "3", UnsafeDuringActorConstruction = "true", Keywords = "play"))
    static void PlaySnapshotableSoundAtLocation(const UObject* WorldContextObject, class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr, AActor* OwningActor = nullptr);
};
