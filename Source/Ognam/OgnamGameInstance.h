// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OgnamGameInstance.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(DECLARE_DELEGATE_OneParam, FOnHostSessionCompleteDelegate)

UCLASS()
class OGNAM_API UOgnamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UOgnamGameInstance(const FObjectInitializer& ObjectInitializer);

	bool CreateSession(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	virtual void CreateSessionComplete(FName SessionName, bool bWasSuccessful);

	//void FindSessionComplete(bool bWasSuccessful);
	//void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	//FDelegateHandle CreateSessionCompleteHandle;
	//FDelegateHandle StartSessionCompleteHandle;
	//FDelegateHandle FindSessionsCompleteHandle;
	//FDelegateHandle JoinSessionCompleteHandle;

	UFUNCTION(BlueprintCallable)
	void SetPrefferedName(FString Name);

	FString GetPrefferedName() const;

	UFUNCTION(BlueprintCallable)
	void HostSession();

private:
	FString PrefferedName;

};
