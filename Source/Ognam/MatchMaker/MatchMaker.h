// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IPAddress.h"
#include "MatchMaker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMatchmakingEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchmakingEventFailure, FText, Message);


UENUM()
enum class EMatchMakingStatus : int32
{
	Success = 0,
	BadLogin,
	UserBanned,
	BadVersion,
	Maintenance,
	MatchmakingBanned,
	BadLevel,
	QueueDisabled,
	AlreadyInQueue,
	InvalidSession,
	AlreadyLoggedIn
};

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API UMatchMaker : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	UMatchMaker();
	
public:
	virtual void Tick(float DeltaTime);
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable)
	void ConnectToServer();

	UFUNCTION()
	void ConnectedDelegate();

	UFUNCTION()
	void Connect();

	UFUNCTION(BlueprintCallable)
	void Login(FString UserName, FString Password);

	void LoginResponse(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void JoinQueue(/*map / gamemode*/);

	void JoinQueueResponse(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void ExitQueue();

	void ExitQueueResponse(TSharedPtr<class FJsonObject> Response);

	void GameFoundEvent(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void GameFoundResponse(bool bAccepted);

	void GameReceiveDetails(TSharedPtr<class FJsonObject> Response);

	void GameCancelledEvent(TSharedPtr<class FJsonObject> Response);

	bool ListenForResponse(FString& Response);

	void SetGameInstance(class UOgnamGameInstance* Instance);

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsConnected;

	UPROPERTY(BlueprintReadOnly)
	bool bConnectionInProgress;

	UPROPERTY(BlueprintReadOnly)
	bool bWaitingToStart;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInQueue;

	UPROPERTY(BlueprintReadOnly)
	bool bGameFound;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnGameFound;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnGameCancelled;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEventFailure OnLoginFailure;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnLoginSuccess;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnSendMessageFailure;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnConnectToServerFailure;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnJoinMatch;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEvent OnJoinQueueSuccess;

	UPROPERTY(BlueprintAssignable)
	FMatchmakingEventFailure OnJoinQueueFailure;

private:
	class ISocketSubsystem* SocketSub;

	class UOgnamGameInstance* GameInstance;

	TSharedPtr<class FSocket> Sock;

	FString GameAcceptToken;

	/* If the Last sent request @see RequestToken is not retreived within this time, discard the request token and forget */
	float RequestTimeout = 10.f;

	/* The current session token, if it ever expires the client must re-login into the server */
	FString SessionToken;

	/* The most recently sent request. Used to ensure that the client is receiving the proper response */
	TSharedPtr<FString> RequestToken;
	
	/* The time the RequestToken was last updated, used for timeout */
	long RequestSentTimestamp;

public:
#define LOCTEXT_NAMESPACE "MatchMaking"

	const FText BadLogin = LOCTEXT("badlogin", "Your username or password is invalid.");
	const FText UserBanned = LOCTEXT("userbanned", "User is banned.");
	const FText BadVersion = LOCTEXT("badversion", "Version out of date!");
	const FText Maintenance = LOCTEXT("maintenance", "Game server under maintenance.");
	const FText MatchmakingBanned = LOCTEXT("matchmakingban", "You are banned from matchmaking.");
	const FText BadLevel = LOCTEXT("badlevel", "You are not a high enough level.");
	const FText QueueDisabled = LOCTEXT("queuedisabled", "Queue has been temporarily disabled.");
	const FText AlreadyInQueue = LOCTEXT("alreadyinqueue", "You are already in a queue!");
	const FText InvalidSession = LOCTEXT("invalidsession", "Invalid Session."); // Maybe say the user needs to relogin?
	const FText AlreadyLoggedIn = LOCTEXT("alreadyloggedin", "You are already logged in.");

#undef LOCTEXT_NAMESPACE

	FText GetTextFromStatus(EMatchMakingStatus Code);
};
