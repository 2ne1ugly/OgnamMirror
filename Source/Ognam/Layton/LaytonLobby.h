// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Layton.h"
#include "LaytonLobby.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API ULaytonLobby: public UObject
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FLaytonLobbyInfo LobbyInfo;
};
