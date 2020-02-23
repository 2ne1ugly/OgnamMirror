// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientStreamLobby.h"
#include "LaytonBlueprintLibrary.h"
#include "LaytonLobby.h"
#include "LaytonPlayer.h"
#include "OgnamLaytonClient.h"

#define META_LOBBY_UUID "custom-lobby-uuid-bin"

void ULaytonClientLobbyStream::SendChatMessage(const FString& ChatMessage, UTagDelegateWrapper* Delegate)
{
	lgrpc::LobbyStreamClient Message;
	Message.mutable_chat_message()->set_message(casts::Proto_Cast<std::string>(ChatMessage));
	SendMessage(Message, Delegate);
}

void ULaytonClientLobbyStream::OnMessageSent(bool Ok, lgrpc::LobbyStreamClient Request)
{
	Super::OnMessageSent(Ok, Request);
	UE_LOG(LogTemp, Warning, TEXT("Message Sent!"));
}

void ULaytonClientLobbyStream::OnMessageReceived(bool Ok, lgrpc::LobbyStreamServer* Response)
{
	Super::OnMessageReceived(Ok, Response);
	switch (Response->message_case())
	{
	case lgrpc::LobbyStreamServer::MessageCase::kInit:
		if (Response->init().result_code() != lgrpc::ResultCode::RC_SUCCESS)
		{
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("INIT!!!"));
		LobbyName = casts::Proto_Cast<FString>(Response->init().lobby_name());
		MapName = *casts::Proto_Cast<FString>(Response->init().lobby_name());
		MaxPlayers = Response->init().max_players();
		LobbyState = casts::Proto_Cast<ELaytonLobbyState>(Response->init().lobby_state());
		Players.Empty();
		for (const lgrpc::PlayerInfo& PlayerInfo : Response->init().players())
		{
			ULaytonPlayer* Player = NewObject<ULaytonPlayer>(this);
			Player->PlayerName = casts::Proto_Cast<FString>(PlayerInfo.username());
			Players.Add(Player);
		}
		UE_LOG(LogTemp, Warning, TEXT("players: %d"), Players.Num());
		break;
	}
}

ULaytonClientStartLobbyStream* ULaytonClientStartLobbyStream::LaytonClientStartLobbyStream(UObject* WorldContextObject, const TArray<uint8>& Lobby)
{
	ULaytonClientStartLobbyStream* Proxy = NewObject<ULaytonClientStartLobbyStream>(WorldContextObject);
	Proxy->LobbyUuid = Lobby;
	Proxy->Client = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	return Proxy;
}

void ULaytonClientStartLobbyStream::Activate()
{
	Client->StreamedLobby = NewObject<ULaytonClientLobbyStream>(Client);
	Client->InitializeClientContext(Client->StreamedLobby->ClientContext);
	Client->StreamedLobby->ClientContext.AddMetadata(META_LOBBY_UUID, casts::Proto_Cast<std::string>(LobbyUuid));
	Client->StreamedLobby->Client = Client;
	Delegate = NewObject<UTagDelegateWrapper>(this);
	Delegate->Delegate.AddUObject(this, &ULaytonClientStartLobbyStream::OnStreamStarted);
	Client->StreamedLobby->StartStream(Delegate);
}

void ULaytonClientStartLobbyStream::OnStreamStarted(bool Ok)
{
	if (Ok)
	{
		Delegate->Delegate.Clear();
		Delegate->Delegate.AddUObject(this, &ULaytonClientStartLobbyStream::OnFirstMessage);
		Client->StreamedLobby->ReceiveMessage(&FirstMessage, Delegate);
	}
	else
	{
		OnFailure.Broadcast("Starting lobby stream failed");
	}
}

void ULaytonClientStartLobbyStream::OnFirstMessage(bool Ok)
{
	if (!FirstMessage.has_init())
	{
		OnFailure.Broadcast("Bad server message");
		Client->StreamedLobby = nullptr;
		return;
	}
	switch (casts::Proto_Cast<ELaytonResultCode>(FirstMessage.init().result_code())) {
	case ELaytonResultCode::RC_SUCCESS:
		OnSuccess.Broadcast("");
		break;
	default:
		OnFailure.Broadcast("Joining Server failed");
		Client->StreamedLobby = nullptr;
		break;
	}
}

ULaytonClientLobbyStreamSendChat* ULaytonClientLobbyStreamSendChat::LaytonClientLobbyStreamSendChat(UObject* WorldContextObject, const FString& InChatMessage)
{
	ULaytonClientLobbyStreamSendChat* Proxy = NewObject<ULaytonClientLobbyStreamSendChat>(WorldContextObject);
	Proxy->Client = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	Proxy->ChatMessage = InChatMessage;
	return Proxy;
}

void ULaytonClientLobbyStreamSendChat::Activate()
{
	Delegate = NewObject<UTagDelegateWrapper>(this);
	Delegate->Delegate.AddUObject(this, &ULaytonClientLobbyStreamSendChat::OnChatSent);
	Client->StreamedLobby->SendChatMessage(ChatMessage, Delegate);
}

void ULaytonClientLobbyStreamSendChat::OnChatSent(bool Ok)
{
	if (Ok)
	{
		OnSuccess.Broadcast("");
	}
	else
	{
		OnFailure.Broadcast("Failed to send chat message");
	}
}
