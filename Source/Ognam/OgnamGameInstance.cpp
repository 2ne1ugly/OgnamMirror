// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "OgnamGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "MatchMaker/MatchMaker.h"

UOgnamGameInstance::UOgnamGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnCreateSessionComplete.BindUObject(this, &UOgnamGameInstance::CreateSessionComplete);
	OnFindSessionsComplete.BindUObject(this, &UOgnamGameInstance::FindSessionComplete);
	OnStartSessionComplete.BindUObject(this, &UOgnamGameInstance::StartSessionComplete);
	OnJoinSessionComplete.BindUObject(this, &UOgnamGameInstance::JoinSessionComplete);
}

void UOgnamGameInstance::Init()
{
	Super::Init();
	MatchMaker = NewObject<UMatchMaker>(this);
	MatchMaker->ConnectToServer();
}

bool UOgnamGameInstance::CreateSession(FName SessionName, bool bIsLAN, int32 MaxNumPlayers, FString MapName)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Start Creating Session..."));

	ULocalPlayer* Player = GetFirstGamePlayer();
	TSharedPtr<const FUniqueNetId> UserId = Player->GetPreferredUniqueNetId().GetUniqueNetId();

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			SessionSettings.NumPublicConnections = MaxNumPlayers;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bIsLANMatch = bIsLAN;
			SessionSettings.bIsDedicated = false;
			SessionSettings.bUsesStats = false;
			SessionSettings.Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);

			CreateSessionCompleteHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionComplete);
			return Sessions->CreateSession(*UserId, SessionName, SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
	}

	return false;
}

void UOgnamGameInstance::FindSession(bool bIsLAN, bool bIsPresence)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("StartFindingSession..")));
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	ULocalPlayer* Player = GetFirstGamePlayer();
	TSharedPtr<const FUniqueNetId> UserId = Player->GetPreferredUniqueNetId().GetUniqueNetId();

	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && UserId.IsValid())
		{
			SessionSearch = MakeShared<FOnlineSessionSearch>();
			SessionSearch->MaxSearchResults = 1;
			SessionSearch->bIsLanQuery = true;

			FindSessionsCompleteHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsComplete);
			Sessions->FindSessions(*UserId, SessionSearch.ToSharedRef());
		}
	}
	else
	{
		FindSessionComplete(false);
	}
}

void UOgnamGameInstance::CreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Creating Session %s result: %d"), *SessionName.ToString(), bWasSuccessful));
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		//Check if sessions are valid and start if they are
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteHandle);
			if (bWasSuccessful)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Starting Session...")));
				StartSessionCompleteHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionComplete);
				Sessions->StartSession(SessionName);
			}
		}
	}
}

void UOgnamGameInstance::StartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Start %s Session result: %d"), *SessionName.ToString(), bWasSuccessful));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	FString MapName;
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteHandle);
			Sessions->GetSessionSettings(SessionName)->Get(SETTING_MAPNAME, MapName);
		}
	}

	if (bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), *MapName, true, FString("?listen"));
	}
}

void UOgnamGameInstance::FindSessionComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Find Session Result: %d"), bWasSuccessful));

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteHandle);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Number Of Sessions: %d"), SessionSearch->SearchResults.Num()));
			for (FOnlineSessionSearchResult Result : SessionSearch->SearchResults)
			{
				FString Name = Result.Session.SessionSettings.Settings.FindRef("SESSION_NAME").Data.ToString();
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session %s"), *Name));
			}
			if (bWasSuccessful && SessionSearch->SearchResults.Num() > 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Joining Session...")));
				ULocalPlayer* Player = GetFirstGamePlayer();
				FOnlineSessionSearchResult SearchResult = SessionSearch->SearchResults[0];
				JoinSessionCompleteHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionComplete);
				Sessions->JoinSession(*Player->GetPreferredUniqueNetId().GetUniqueNetId(), TEXT("ProvingGround"), SearchResult);
			}
		}
	}
}

void UOgnamGameInstance::JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Join %s Session Result: %d"), *SessionName.ToString(), static_cast<int32>(Result)));
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteHandle);
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			FString TravelURL;

			if (Result == EOnJoinSessionCompleteResult::Success &&
				PlayerController &&
				Sessions->GetResolvedConnectString(SessionName, TravelURL))
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Connect Sring %s"), *TravelURL));
				PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute, true);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Join Session has failed!"));
			}
		}
	}
}

FString UOgnamGameInstance::GetPrefferedName() const
{
	return PrefferedName;
}

void UOgnamGameInstance::SetPrefferedName(FString Name)
{
	PrefferedName = Name;
}

UMatchMaker* UOgnamGameInstance::GetMatchMaker() const
{
	return MatchMaker;
}
