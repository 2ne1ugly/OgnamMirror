// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonBlueprintLibrary.h"
#include "OgnamGameInstance.h"
#include "LaytonSession.h"
#include "Engine/World.h"

ULaytonRpcClient* ULaytonBlueprintLibrary::GetLaytonClient(UObject* WorldContextObject)
{
	UOgnamGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance<UOgnamGameInstance>();
	return GameInstance->LaytonClient;
}

void ULaytonBlueprintLibrary::ProcessGrpcStatus(const FGrpcStatus& Status, FString& ErrorMsg, EBlueprintParameterCheck& Result)
{
	ErrorMsg = "";
	if (Status.ErrorCode == EGrpcStatusCode::Ok)
	{
		Result = EBlueprintParameterCheck::OnOk;
		return;
	}
	Result = EBlueprintParameterCheck::OnError;
	ErrorMsg = FString::Printf(TEXT("%d: %s\n%s"), static_cast<uint8>(Status.ErrorCode), *Status.ErrorMessage, *Status.ErrorDetails);
}

void ULaytonBlueprintLibrary::ProcessLoginResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result)
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

void ULaytonBlueprintLibrary::ProcessCreateAccountResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result)
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

void ULaytonBlueprintLibrary::ProcessCreateSessionResponse(const FLaytonCreateSessionResponse& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result)
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

void ULaytonBlueprintLibrary::ProcessFindSessionsResponse(UObject* WorldContextObject, const FLaytonFindSessionsResponse& Response, const FGrpcStatus& Status, TArray<ULaytonSession*>& OutSessions, FString& Reason, EBlueprintExecutionResult& Result)
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
		for (const auto& Session : Response.Sessions)
		{
			ULaytonSession* SessionWrapper = NewObject<ULaytonSession>(WorldContextObject);
			SessionWrapper->SessionInfo = Session;
			OutSessions.Add(SessionWrapper);
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

void ULaytonBlueprintLibrary::ProcessJoinSessionResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result)
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

void ULaytonBlueprintLibrary::ProcessStartSessionResponse(const FLaytonResult& Response, const FGrpcStatus& Status, FString& Reason, EBlueprintExecutionResult& Result)
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
