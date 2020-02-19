// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonClientStreamLobby.h"
#include "LaytonBlueprintLibrary.h"
#include "OgnamLaytonClient.h"

ULaytonClientStreamLobby* ULaytonClientStreamLobby::LaytonClientStreamLobby(UObject* WorldContextObject)
{
	UOgnamLaytonClient* LaytonClient = ULaytonBlueprintLibrary::GetLaytonClient(WorldContextObject);
	ULaytonClientStreamLobby* Proxy = NewObject<ULaytonClientStreamLobby>(LaytonClient);
	Proxy->Client = LaytonClient;
	LaytonClient->InitializeClientContext(Proxy->ClientContext);
	return Proxy;
}

void ULaytonClientStreamLobby::SendChatMessage(const FString& ChatMessage)
{
	lgrpc::LobbyStreamClient Message;
	Message.mutable_chat_message()->set_message(casts::Proto_Cast<std::string>(ChatMessage));
	SendMessage(Message);
}

void ULaytonClientStreamLobby::OnMessageSent(lgrpc::LobbyStreamClient Request)
{
	UE_LOG(LogTemp, Warning, TEXT("Message Sent!"));
}