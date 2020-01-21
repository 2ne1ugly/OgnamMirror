// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Ognam/OgnamMacro.h"

UOgnamGameInstance::UOgnamGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UOgnamGameInstance::GetPrefferedName() const
{
	return PrefferedName;
}
//
//void UOgnamGameInstance::HostSession(FOnHostSessionCompleteDelegate& Delegate)
//{
//	ULocalPlayer* const Player = GetFirstGamePlayer();
//
//	CreateSession(Delegate, TEXT("Session"), true, true, 4);
//}
//
void UOgnamGameInstance::SetPrefferedName(FString Name)
{
	PrefferedName = Name;
}
//
//bool UOgnamGameInstance::CreateSession(FOnHostSessionCompleteDelegate& Delegate, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
//{
//	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
//
//	if (OnlineSub)
//	{
//		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
//
//		if (Sessions.IsValid())
//		{
//			SessionSettings = MakeShared<FOnlineSessionSettings>();
//
//			SessionSettings->bIsLANMatch = bIsLAN;
//			SessionSettings->bUsesPresence = bIsPresence;
//			SessionSettings->NumPublicConnections = MaxNumPlayers;
//			SessionSettings->NumPrivateConnections = 0;
//			SessionSettings->bAllowInvites = true;
//			SessionSettings->bAllowJoinInProgress = true;
//			SessionSettings->bShouldAdvertise = true;
//			SessionSettings->bAllowJoinViaPresence = true;
//			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
//
//			SessionSettings->Set(SETTING_MAPNAME, FString("air_station_2"), EOnlineDataAdvertisementType::ViaOnlineService);
//
//			Sessions->addon
//			//OnCreateSessionCompleteDelegateHandle = Sessions- (OnCreateSessionCompleteDelegate);
//			return Sessions->CreateSession(0, SessionName, *SessionSettings);
//		}
//		else
//		{
//			O_MSG_E(TEXT("Session is invalid!"))
//		}
//	}
//	else
//	{
//		O_MSG_E(TEXT("No online subsystem"))
//	}
//
//	return false;
//}
//
//void UOgnamGameInstance::CreateSessionComplete(FName SessionName, bool bWasSuccessful)
//{
//	O_MSG(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful)
//}
