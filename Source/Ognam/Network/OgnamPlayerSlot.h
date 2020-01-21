// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OgnamPlayerSlot.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API UOgnamPlayerSlot : public UObject
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FString PlayerName;
};
