// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "OgnamLaytonClient.generated.h"

struct FLaytonAccount
{
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

    void InitializeClientContext(grpc::ClientContext& ClientContext);

    void SetAccount(const std::string& Username, const std::string& AuthToken);
};
