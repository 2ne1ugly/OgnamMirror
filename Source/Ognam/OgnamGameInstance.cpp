// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "ServerBrowser.h"
#include "Ognam/OgnamMacro.h"

UOgnamGameInstance::UOgnamGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOgnamGameInstance::CreateSessionComplete);
}

void UOgnamGameInstance::Init()
{
	ServerBrowser = NewObject<UServerBrowser>(this);
}

bool UOgnamGameInstance::CreateSession(FName SessionName, bool bIsLAN, int32 MaxNumPlayers, FString MapName)
{
	return PrefferedName;
}

void UOgnamGameInstance::SetPrefferedName(FString Name)
{
	PrefferedName = Name;
}

bool UOgnamGameInstance::CreateSession(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			SessionSettings = MakeShared<FOnlineSessionSettings>();

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString("air_station_2"), EOnlineDataAdvertisementType::ViaOnlineService);

			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			return Sessions->CreateSession(0, SessionName, *SessionSettings);
		}
		else
		{
			O_MSG_E(TEXT("Session is invalid!"))
		}
	}
	else
	{
		O_MSG_E(TEXT("No online subsystem"))
	}

	return false;
}

void UOgnamGameInstance::CreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	O_MSG(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful)

	//IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	//if (OnlineSub)
	//{
	//	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	//	if (Sessions.IsValid())
	//	{
	//		Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
	//		if (bWasSuccessful)
	//		{
	//			OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
	//			Sessions->StartSession(SessionName);
	//		}
	//	}
	//	else
	//	{
	//		O_MSG_E(TEXT("Session is invalid!"))
	//	}
	//}
	//else
	//{
	//	O_MSG_E(TEXT("No online subsystem"))
	//}
}

void UOgnamGameInstance::HostSession()
{
	ULocalPlayer* const Player = GetFirstGamePlayer();

	CreateSession(TEXT("Session"), true, true, 4);
}

UServerBrowser* UOgnamGameInstance::GetServerBrowser() const
{
	return ServerBrowser;
}
