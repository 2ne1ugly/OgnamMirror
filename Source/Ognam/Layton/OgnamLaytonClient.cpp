// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamLaytonClient.h"
#include "CastUtils.h"

UGrpcClientContext* UOgnamLaytonClient::CreateClientContext()
{
	UGrpcClientContext* ClientContext = NewObject<UGrpcClientContext>(this);
	if (Account)
	{
		ClientContext->ClientContext->AddMetadata("custom-username", Account->Username);
		ClientContext->ClientContext->AddMetadata("custom-auth-token-bin", Account->AuthToken);
	}
	return ClientContext;
}

void UOgnamLaytonClient::SetAccount(const FString& Username, const TArray<uint8>& AuthToken)
{
	SetAccount(casts::Proto_Cast<std::string>(Username), casts::Proto_Cast<std::string>(AuthToken));
}

void UOgnamLaytonClient::SetAccount(const std::string& Username, const std::string& AuthToken)
{
	Account = MakeShared<FLaytonAccount>();
	Account->Username = Username;
	Account->AuthToken = AuthToken;
}
