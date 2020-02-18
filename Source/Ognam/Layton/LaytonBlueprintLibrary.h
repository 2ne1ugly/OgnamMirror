// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/OgnamLaytonClient.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LaytonBlueprintLibrary.generated.h"

UENUM()
enum class EBlueprintParameterCheck : uint8
{
    OnOk,
    OnError
};

UENUM()
enum class EBlueprintExecutionResult : uint8
{
    OnSuccess,
    OnFailure
};

/**
 * 
 */
UCLASS()
class OGNAM_API ULaytonBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    /*
    **  Common
    */
    UFUNCTION(BlueprintPure, Meta=(WorldContext="WorldContextObject"))
    static class UOgnamLaytonClient* GetLaytonClient(UObject* WorldContextObject);

    UFUNCTION(BlueprintCallable, Meta=(ExpandEnumAsExecs="Result"))
    static void ProcessGrpcStatus(UGrpcStatus* Status, FString& ErrorMsg, EBlueprintParameterCheck& Result);

    /*
    **  Identity
    */
    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
    static void ProcessLoginResponse(const FLaytonLoginResponse& Response, UGrpcStatus* Status, const FLaytonLoginRequest& Request,  UOgnamLaytonClient* Client, FString& Reason, EBlueprintExecutionResult& Result);

    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
    static void ProcessCreateAccountResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result);

    /*
    **  Session
    */
    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
    static void ProcessCreateLobbyResponse(const FLaytonCreateLobbyResponse& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result);

    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"), Category = "Ognam Studios|RPC Response|Layton")
    static void ProcessFindLobbiesResponse(UObject* WorldContextObject, const FLaytonFindLobbiesResponse& Response, UGrpcStatus* Status, TArray<ULaytonLobby*>& OutSessions, FString& Reason, EBlueprintExecutionResult& Result);

    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
    static void ProcessLeaveLobbyResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result);

    //UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
    //static void ProcessStartSessionResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result);
    
protected:
    static void ProcessLaytonResultDefault(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result);
};
