// Fill out your copyright notice in the Description page of Project Settings.


#include "LaytonBlueprintLibrary.h"
#include "OgnamGameInstance.h"
#include "LaytonLobby.h"
#include "Engine/World.h"
#include "CastUtils.h"

UOgnamLaytonClient* ULaytonBlueprintLibrary::GetLaytonClient(UObject* WorldContextObject)
{
	UOgnamGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance<UOgnamGameInstance>();
	return GameInstance->LaytonClient;
}

bool ULaytonBlueprintLibrary::CheckGrpcStatus(const grpc::Status& Status, FString& ErrorMsg)
{
	ErrorMsg = "";
	if (casts::Proto_Cast<EGrpcStatusCode>(Status.error_code()) == EGrpcStatusCode::Ok)
	{
		return true;
	}
	ErrorMsg = FString::Printf(TEXT("%d: %s\n%s"), Status.error_code(),
		*casts::Proto_Cast<FString>(Status.error_message()),
		*casts::Proto_Cast<FString>(Status.error_details()));
	return false;
}
//
//void ULaytonBlueprintLibrary::ProcessLoginResponse(const FLaytonLoginResponse& Response, UGrpcStatus* Status, const FLaytonLoginRequest& Request, UOgnamLaytonClient* Client, FString& Reason, EBlueprintExecutionResult& Result)
//{
//	EBlueprintParameterCheck StatusCheck;
//
//	Result = EBlueprintExecutionResult::OnFailure;
//	ProcessGrpcStatus(Status, Reason, StatusCheck);
//	if (StatusCheck != EBlueprintParameterCheck::OnOk)
//	{
//		return;
//	}
//
//	switch (Response.ResultCode)
//	{
//	case ELaytonResultCode::RC_SUCCESS:
//		Client->SetAccount(Request.Username, Response.AuthToken);
//		Result = EBlueprintExecutionResult::OnSuccess;
//		return;
//	case ELaytonResultCode::RC_ERROR:
//		Reason = "Error";
//		return;
//	case ELaytonResultCode::RC_FAIL:
//		Reason = "Fail";
//		return;
//	default:
//		Reason = "Unknown";
//		return;
//	}
//}
//
//void ULaytonBlueprintLibrary::ProcessCreateAccountResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
//{
//	EBlueprintParameterCheck StatusCheck;
//
//	Result = EBlueprintExecutionResult::OnFailure;
//	ProcessGrpcStatus(Status, Reason, StatusCheck);
//	if (StatusCheck != EBlueprintParameterCheck::OnOk)
//	{
//		return;
//	}
//
//	switch (Response.ResultCode)
//	{
//	case ELaytonResultCode::RC_SUCCESS:
//		Result = EBlueprintExecutionResult::OnSuccess;
//		return;
//	case ELaytonResultCode::RC_ERROR:
//		Reason = "Error";
//		return;
//	case ELaytonResultCode::RC_FAIL:
//		Reason = "Fail";
//		return;
//	default:
//		Reason = "Unknown";
//		return;
//	}
//}
//
//void ULaytonBlueprintLibrary::ProcessCreateLobbyResponse(const FLaytonCreateLobbyResponse& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
//{
//	EBlueprintParameterCheck StatusCheck;
//
//	Result = EBlueprintExecutionResult::OnFailure;
//	ProcessGrpcStatus(Status, Reason, StatusCheck);
//	if (StatusCheck != EBlueprintParameterCheck::OnOk)
//	{
//		return;
//	}
//
//	switch (Response.ResultCode)
//	{
//	case ELaytonResultCode::RC_SUCCESS:
//		Result = EBlueprintExecutionResult::OnSuccess;
//		return;
//	case ELaytonResultCode::RC_ERROR:
//		Reason = "Error";
//		return;
//	case ELaytonResultCode::RC_FAIL:
//		Reason = "Fail";
//		return;
//	default:
//		Reason = "Unknown";
//		return;
//	}
//}
//
//void ULaytonBlueprintLibrary::ProcessFindLobbiesResponse(UObject* WorldContextObject, const FLaytonFindLobbiesResponse& Response, UGrpcStatus* Status, TArray<ULaytonLobby*>& OutSessions, FString& Reason, EBlueprintExecutionResult& Result)
//{
//	EBlueprintParameterCheck StatusCheck;
//	
//	Result = EBlueprintExecutionResult::OnFailure;
//	OutSessions.Empty();
//	ProcessGrpcStatus(Status, Reason, StatusCheck);
//	if (StatusCheck != EBlueprintParameterCheck::OnOk)
//	{
//		return;
//	}
//	
//	switch (Response.ResultCode)
//	{
//	case ELaytonResultCode::RC_SUCCESS:
//		Result = EBlueprintExecutionResult::OnSuccess;
//		for (const auto& Lobby : Response.Lobbies)
//		{
//			ULaytonLobby* LobbyWrapper = NewObject<ULaytonLobby>(WorldContextObject);
//			LobbyWrapper->LobbyInfo = Lobby;
//			OutSessions.Add(LobbyWrapper);
//		}
//		return;
//	case ELaytonResultCode::RC_ERROR:
//		Reason = "Error";
//		return;
//	case ELaytonResultCode::RC_FAIL:
//		Reason = "Fail";
//		return;
//	default:
//		Reason = "Unknown";
//		return;
//	}
//}
//
//void ULaytonBlueprintLibrary::ProcessLeaveLobbyResponse(const FLaytonResult& Response, UGrpcStatus* Status, FString& Reason, EBlueprintExecutionResult& Result)
//{
//	EBlueprintParameterCheck StatusCheck;
//
//	Result = EBlueprintExecutionResult::OnFailure;
//	ProcessGrpcStatus(Status, Reason, StatusCheck);
//	if (StatusCheck != EBlueprintParameterCheck::OnOk)
//	{
//		return;
//	}
//
//	switch (Response.ResultCode)
//	{
//	case ELaytonResultCode::RC_SUCCESS:
//		Result = EBlueprintExecutionResult::OnSuccess;
//		return;
//	case ELaytonResultCode::RC_ERROR:
//		Reason = "Error";
//		return;
//	case ELaytonResultCode::RC_FAIL:
//		Reason = "Fail";
//		return;
//	default:
//		Reason = "Unknown";
//		return;
//	}
//}
//
