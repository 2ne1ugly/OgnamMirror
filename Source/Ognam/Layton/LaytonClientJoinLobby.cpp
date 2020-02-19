// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientJoinLobby.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"

ULaytonClientJoinLobby* ULaytonClientJoinLobby::LaytonClientJoinLobby(UObject* WorldContextObject, const TArray<uint8>& LobbyUuid)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientJoinLobby* Proxy = NewObject<ULaytonClientJoinLobby>(LaytonClient);
	Proxy->Client = LaytonClient;
	LaytonClient->InitializeClientContext(Proxy->ClientContext);
	Proxy->Request.set_lobby_uuid(casts::Proto_Cast<std::string>(LobbyUuid));
	return Proxy;
}

void ULaytonClientJoinLobby::OnResponseReceived()
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
