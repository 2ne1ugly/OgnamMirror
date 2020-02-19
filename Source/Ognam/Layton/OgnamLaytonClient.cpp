// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamLaytonClient.h"
#include "CastUtils.h"

void UOgnamLaytonClient::InitializeClientContext(grpc::ClientContext& ClientContext)
{
	if (Account)
	{
		ClientContext.AddMetadata("custom-username", Account->Username);
		ClientContext.AddMetadata("custom-auth-token-bin", Account->AuthToken);
	}
}

void UOgnamLaytonClient::SetAccount(const std::string& Username, const std::string& AuthToken)
{
	Account = MakeShared<FLaytonAccount>();
	Account->Username = Username;
	Account->AuthToken = AuthToken;
}
