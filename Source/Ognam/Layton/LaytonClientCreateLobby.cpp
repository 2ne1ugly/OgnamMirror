// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientCreateLobby.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"
#include "LaytonLobby.h"

ULaytonClientCreateLobby* ULaytonClientCreateLobby::LaytonClientCreateLobby(UObject* WorldContextObject, const FString& LobbyName, const FString& MapName, int32 MaxPlayers)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientCreateLobby* Proxy = NewObject<ULaytonClientCreateLobby>(LaytonClient);
	Proxy->Client = LaytonClient;
	LaytonClient->InitializeClientContext(Proxy->ClientContext);
	Proxy->Request.set_lobby_name(casts::Proto_Cast<std::string>(LobbyName));
	Proxy->Request.set_map_name(casts::Proto_Cast<std::string>(MapName));
	Proxy->Request.set_max_players(MaxPlayers);
	return Proxy;
}

void ULaytonClientCreateLobby::OnResponseReceived(bool Ok)
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
		OnSuccess.Broadcast(casts::Proto_Cast<TArray<uint8>>(Response.lobby_uuid()));
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
