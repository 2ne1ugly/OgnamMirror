// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientFindLobbies.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"

ULaytonClientFindLobbies* ULaytonClientFindLobbies::LaytonClientFindLobbies(UObject* WorldContextObject)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientFindLobbies* Proxy = NewObject<ULaytonClientFindLobbies>(LaytonClient);
	Proxy->Client = LaytonClient;
	LaytonClient->InitializeClientContext(Proxy->ClientContext);
	return Proxy;
}

void ULaytonClientFindLobbies::OnResponseReceived(bool Ok)
{
	FString ErrorMsg;
	if (!ULaytonBlueprintLibrary::CheckGrpcStatus(Status, ErrorMsg))
	{
		OnFailure.Broadcast(ErrorMsg);
		return;
	}

	TArray<ULaytonLobby*> Lobbies;

	switch (casts::Proto_Cast<ELaytonResultCode>(Response.result_code()))
	{
	case ELaytonResultCode::RC_SUCCESS:
		for (int i = 0; i < Response.lobbies_size(); i++)
		{
			ULaytonLobby* Lobby = NewObject<ULaytonLobby>(this);
			Lobby->LobbyInfo = casts::Proto_Cast<FLaytonLobbyInfo>(Response.lobbies(i));
			Lobbies.Add(Lobby);
		}
		OnSuccess.Broadcast(Lobbies);
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
