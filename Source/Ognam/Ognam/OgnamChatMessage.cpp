// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamChatMessage.h"
#include "OgnamPlayerState.h"

FString UOgnamChatMessage::GetFormattedMessage()
{
	if (!Sender)
	{
		return FString("");
	}
	return FString::Printf(TEXT("%s: %s"), *Sender->GetPlayerName(), *Message);
}
