// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IPAddress.h"
#include "MatchMaker.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom))
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
};
