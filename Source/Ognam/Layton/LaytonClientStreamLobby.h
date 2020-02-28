// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonClientStreamLobby.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChatMessageReceived, FString, Username, FString, ChatMessage);

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API ULaytonClientLobbyStream : public ULaytonClientLobbyStreamBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnChatMessageReceived OnChatMessageReceived;

    UPROPERTY(BlueprintReadWrite)
    FString LobbyName;

    UPROPERTY(BlueprintReadWrite)
    FName MapName;

    UPROPERTY(BlueprintReadWrite)
    int32 MaxPlayers;

    UPROPERTY(BlueprintReadWrite)
    TArray<class ULaytonPlayer*> Players;

    UPROPERTY(BlueprintReadWrite)
    ELaytonLobbyState LobbyState;

    void SendChatMessage(const FString& ChatMessage, UTagDelegateWrapper* Delegate);

    virtual void OnMessageSent(bool Ok, lgrpc::LobbyStreamClient Request) override;
    virtual void OnMessageReceived(bool Ok, lgrpc::LobbyStreamServer* Response) override;
};

UCLASS(Blueprintable)
class OGNAM_API ULaytonClientStartLobbyStream : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UPROPERTY()
    class UOgnamLaytonClient* Client;

    TArray<uint8> LobbyUuid;

    lgrpc::LobbyStreamServer FirstMessage;

    UPROPERTY()
    UTagDelegateWrapper* Delegate;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientStartLobbyStream* LaytonClientStartLobbyStream(UObject* WorldContextObject, const TArray<uint8>& Lobby);

    virtual void Activate() override;

    void OnStreamStarted(bool Ok);

    void OnFirstMessage(bool Ok);
};

UCLASS(Blueprintable)
class OGNAM_API ULaytonClientLobbyStreamSendChat : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UPROPERTY()
    UOgnamLaytonClient* Client;

    FString ChatMessage;

    UPROPERTY()
    UTagDelegateWrapper* Delegate;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientLobbyStreamSendChat* LaytonClientLobbyStreamSendChat(UObject* WorldContextObject, const FString& InChatMessage);

    virtual void Activate() override;

    void OnChatSent(bool Ok);
};