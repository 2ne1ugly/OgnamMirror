// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "Layton/Layton.h"
//#include "Kismet/BlueprintFunctionLibrary.h"
//#include "LaytonBlueprintLibrary.generated.h"
//
//UENUM()
//enum class EBlueprintParameterCheck : uint8
//{
//    OnOk,
//    OnError
//};
//
//UENUM()
//enum class EBlueprintExecutionResult : uint8
//{
//    OnSuccess,
//    OnFailure
//};
//
///**
// * 
// */
//UCLASS()
//class OGNAM_API ULaytonBlueprintLibrary : public UBlueprintFunctionLibrary
//{
//	GENERATED_BODY()
//
//public:
//    /*
//    **  Common
//    */
//    UFUNCTION(BlueprintPure, Meta=(WorldContext="WorldContextObject"))
//    static class ULaytonRpcClient* GetLaytonClient(UObject* WorldContextObject);
//
//    UFUNCTION(BlueprintCallable, Meta=(ExpandEnumAsExecs="Result"))
//    static void ProcessGrpcStatus(const FGrpcStatus& Status, FString& ErrorMsg, EBlueprintParameterCheck& Result);
//
//    /*
//    **  Identity
//    */
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessLoginResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result);
//
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessCreateAccountResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result);
//
//    /*
//    **  Session
//    */
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessCreateSessionResponse(const FLaytonCreateSessionResponse& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result);
//
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result", WorldContext = "WorldContextObject"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessFindSessionsResponse(UObject* WorldContextObject, const FLaytonFindSessionsResponse& Response, const FGrpcStatus& Status, TArray<ULaytonSession*>& OutSessions, FString& Reason, EBlueprintExecutionResult& Result);
//
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessJoinSessionResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result);
//
//    UFUNCTION(BlueprintCallable, Meta = (ExpandEnumAsExecs = "Result"), Category = "Ognam Studios|RPC Response|Layton")
//    static void ProcessStartSessionResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result);
//
//};
