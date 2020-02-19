// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonClientStreamLobby.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API ULaytonClientStreamLobby : public ULaytonClientStreamLobbyBase
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientStreamLobby* LaytonClientStreamLobby(UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable)
    void SendChatMessage(const FString& ChatMessage);

    virtual void OnMessageSent(lgrpc::LobbyStreamClient Request) override;
};
