// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "OgnamLaytonClient.generated.h"

USTRUCT(Blueprintable)
struct FLaytonAccount
{
    GENERATED_BODY()

    std::string Username;
    std::string AuthToken;
};

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamLaytonClient : public ULaytonClientRpcClient
{
	GENERATED_BODY()

public:
    TSharedPtr<FLaytonAccount> Account;

    UFUNCTION(BlueprintPure)
    UGrpcClientContext* CreateClientContext();

    UFUNCTION(BlueprintCallable)
    void SetAccount(const FString& Username, const TArray<uint8>& AuthToken);

    void SetAccount(const std::string& Username, const std::string& AuthToken);
};
