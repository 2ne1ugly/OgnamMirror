// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OgnamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	UOgnamGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnFindSessionsComplete(bool bWasSuccessful);

	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;

	FDelegateHandle OnSessionUserInviteAcceptedDelegateHandle;

	FOnSessionInviteReceived OnSessionInviteReceivedDelegate;

	FDelegateHandle InInviteReceivedDelegateHandle;

	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	//virtual bool SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend);

	void SessionReceiveInvite(const FUniqueNetId& UserID, const FUniqueNetId& FromID, const FString& AppID, const FOnlineSessionSearchResult& Result);

	void SessionAcceptInvite(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void FindOnlineGames();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();
};
