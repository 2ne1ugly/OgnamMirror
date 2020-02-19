// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonClientJoinLobby.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULaytonClientJoinLobby : public ULaytonClientJoinLobbyBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientJoinLobby* LaytonClientJoinLobby(UObject* WorldContextObject, const TArray<uint8>& LobbyUuid);

    virtual void OnResponseReceived() override;
};
