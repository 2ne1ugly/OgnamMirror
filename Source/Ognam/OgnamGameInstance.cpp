// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameInstance.h"
//#include "OnlineSessionSettings.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Ognam/OgnamMacro.h"

#include "Layton/OgnamLaytonClient.h"

UOgnamGameInstance::UOgnamGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UOgnamGameInstance::GetPrefferedName() const
{
	return "NONE";
}

void UOgnamGameInstance::Init()
{
	if (!IsDedicatedServerInstance())
	{
		LaytonClient = NewObject<UOgnamLaytonClient>(this);
		LaytonClient->Init("10.10.134.224:50051", UChannelCredentials::MakeInsecureChannelCredentials());
	}
}

void UOgnamGameInstance::SetPrefferedName(FString Name)
{
	PrefferedName = Name;
}
