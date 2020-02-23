// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientLogin.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"

ULaytonClientLogin* ULaytonClientLogin::LaytonClientLogin(UObject* WorldContextObject, const FString& Username)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientLogin* Proxy = NewObject<ULaytonClientLogin>(LaytonClient);
	Proxy->Request.set_username(casts::Proto_Cast<std::string>(Username));
	Proxy->Client = LaytonClient;
	return Proxy;
}

void ULaytonClientLogin::OnResponseReceived(bool Ok)
{
	FString ErrorMsg;
	if (!ULaytonBlueprintLibrary::CheckGrpcStatus(Status, ErrorMsg))
	{
		OnFailure.Broadcast(ErrorMsg);
		return;
	}

	switch (casts::Proto_Cast<ELaytonResultCode>(Response.result_code()))
	{
	case ELaytonResultCode::RC_SUCCESS:
		Cast<UOgnamLaytonClient>(Client)->SetAccount(Request.username(), Response.auth_token());
		OnSuccess.Broadcast("Login Successful");
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
