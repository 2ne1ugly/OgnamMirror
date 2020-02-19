// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonClientCreateLobby.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULaytonClientCreateLobby : public ULaytonClientCreateLobbyBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientCreateLobby* LaytonClientCreateLobby(UObject* WorldContextObject, const FString& LobbyName, const FString& MapName, int32 MaxPlayers);

    virtual void OnResponseReceived() override;
};
