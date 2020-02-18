// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonBlueprintLibrary.h"
#include "OgnamGameInstance.h"
#include "LaytonLobby.h"
#include "Engine/World.h"

UOgnamLaytonClient* ULaytonBlueprintLibrary::GetLaytonClient(UObject* WorldContextObject)
{
	UOgnamGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance<UOgnamGameInstance>();
	return GameInstance->LaytonClient;
}

void ULaytonBlueprintLibrary::ProcessGrpcStatus(UGrpcStatus* Status, FString& ErrorMsg, EBlueprintParameterCheck& Result)
{
	ErrorMsg = "";
	if (Status->GetErrorCode() == EGrpcStatusCode::Ok)
	{
		Result = EBlueprintParameterCheck::OnOk;
		return;
	}
	Result = EBlueprintParameterCheck::OnError;
	ErrorMsg = FString::Printf(TEXT("%d: %s\n%s"), static_cast<uint8>(Status->GetErrorCode()), *Status->GetErrorMessage(), *Status->GetErrorDetails());
}

void ULaytonBlueprintLibrary::ProcessLoginResponse(const FLaytonLoginResponse& Response, UGrpcStatus* Status, const FLaytonLoginRequest& Request, UOgnamLaytonClient* Client, FString& Reason, EBlueprintExecutionResult& Result)
{
	EBlueprintParameterCheck StatusCheck;

	Result = EBlueprintExecutionResult::OnFailure;
	ProcessGrpcStatus(Status, Reason, StatusCheck);
	if (StatusCheck != EBlueprintParameterCheck::OnOk)
	{
		return;
	}

	switch (Response.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		Client->SetAccount(Request.Username, Response.AuthToken);
		Result = EBlueprintExecutionResult::OnSuccess;
		return;
	case ELaytonResultCode::RC_ERROR:
		Reason = "Error";
		return;
	case ELaytonResultCode::RC_FAIL:
		Reason = "Fail";
		return;
	default:
		Reason = "Unknown";
		return;
	}
}

void ULaytonBlueprintLibrary::ProcessCreateAccountResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
{
	EBlueprintParameterCheck StatusCheck;

	Result = EBlueprintExecutionResult::OnFailure;
	ProcessGrpcStatus(Status, Reason, StatusCheck);
	if (StatusCheck != EBlueprintParameterCheck::OnOk)
	{
		return;
	}

	switch (Response.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		Result = EBlueprintExecutionResult::OnSuccess;
		return;
	case ELaytonResultCode::RC_ERROR:
		Reason = "Error";
		return;
	case ELaytonResultCode::RC_FAIL:
		Reason = "Fail";
		return;
	default:
		Reason = "Unknown";
		return;
	}
}

void ULaytonBlueprintLibrary::ProcessCreateLobbyResponse(const FLaytonCreateLobbyResponse& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
{
	EBlueprintParameterCheck StatusCheck;

	Result = EBlueprintExecutionResult::OnFailure;
	ProcessGrpcStatus(Status, Reason, StatusCheck);
	if (StatusCheck != EBlueprintParameterCheck::OnOk)
	{
		return;
	}

	switch (Response.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		Result = EBlueprintExecutionResult::OnSuccess;
		return;
	case ELaytonResultCode::RC_ERROR:
		Reason = "Error";
		return;
	case ELaytonResultCode::RC_FAIL:
		Reason = "Fail";
		return;
	default:
		Reason = "Unknown";
		return;
	}
}

void ULaytonBlueprintLibrary::ProcessFindLobbiesResponse(UObject* WorldContextObject, const FLaytonFindLobbiesResponse& Response, UGrpcStatus* Status, TArray<ULaytonLobby*>& OutSessions, FString& Reason, EBlueprintExecutionResult& Result)
{
	EBlueprintParameterCheck StatusCheck;
	
	Result = EBlueprintExecutionResult::OnFailure;
	OutSessions.Empty();
	ProcessGrpcStatus(Status, Reason, StatusCheck);
	if (StatusCheck != EBlueprintParameterCheck::OnOk)
	{
		return;
	}
	
	switch (Response.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		Result = EBlueprintExecutionResult::OnSuccess;
		for (const auto& Lobby : Response.Lobbies)
		{
			ULaytonLobby* LobbyWrapper = NewObject<ULaytonLobby>(WorldContextObject);
			LobbyWrapper->LobbyInfo = Lobby;
			OutSessions.Add(LobbyWrapper);
		}
		return;
	case ELaytonResultCode::RC_ERROR:
		Reason = "Error";
		return;
	case ELaytonResultCode::RC_FAIL:
		Reason = "Fail";
		return;
	default:
		Reason = "Unknown";
		return;
	}
}

void ULaytonBlueprintLibrary::ProcessLeaveLobbyResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
{
	EBlueprintParameterCheck StatusCheck;

	Result = EBlueprintExecutionResult::OnFailure;
	ProcessGrpcStatus(Status, Reason, StatusCheck);
	if (StatusCheck != EBlueprintParameterCheck::OnOk)
	{
		return;
	}

	switch (Response.ResultCode)
	{
	case ELaytonResultCode::RC_SUCCESS:
		Result = EBlueprintExecutionResult::OnSuccess;
		return;
	case ELaytonResultCode::RC_ERROR:
		Reason = "Error";
		return;
	case ELaytonResultCode::RC_FAIL:
		Reason = "Fail";
		return;
	default:
		Reason = "Unknown";
		return;
	}
}

