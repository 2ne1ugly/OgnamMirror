// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientCreateAccount.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"

ULaytonClientCreateAccount* ULaytonClientCreateAccount::LaytonClientCreateAccount(UObject* WorldContextObject, const FString& Username)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientCreateAccount* Proxy = NewObject<ULaytonClientCreateAccount>(LaytonClient);
	Proxy->Request.set_username(casts::Proto_Cast<std::string>(Username));
	Proxy->Client = LaytonClient;
	return Proxy;
}

void ULaytonClientCreateAccount::OnResponseReceived()
{
	FString ErrorMsg;
	if (!ULaytonBlueprintLibrary::CheckGrpcStatus(Status, ErrorMsg))
	{
		OnFailure.Broadcast(ErrorMsg);
		return;
	}

	FLaytonResult Result = casts::Proto_Cast<FLaytonResult>(Response);

	switch (Result.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		OnSuccess.Broadcast("Create Account Successful");
		return;
	case ELaytonResultCode::RC_ERROR:
		OnFailure.Broadcast("Error");
		return;
	case ELaytonResultCode::RC_FAIL:
		OnFailure.Broadcast("Fail");
		return;
	default:
		OnFailure.Broadcast("Unknown");
		return;
	}
}
