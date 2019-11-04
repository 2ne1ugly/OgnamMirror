// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "MatchMaker.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Ognam/OgnamMacro.h"
#include "Async/Async.h"
#include "IPAddress.h"
#include "Dom/JsonObject.h"
#include "Json.h"
#include "JsonReader.h"
#include "JsonWriter.h"
#include "APIFunctions.h"
#include "JsonPrintPolicy.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "OgnamGameInstance.h"

UMatchMaker::UMatchMaker()
{
	SocketSub = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	Sock = MakeShareable(SocketSub->CreateSocket(NAME_Stream, TEXT("Connection to Matchmaking server")));
}

void UMatchMaker::Tick(float DeltaTime)
{
	if (bNotifyConnectionStatus)
	{
		bNotifyConnectionStatus = false;
		if (bIsConnected)
		{
			OnConnectToServerSuccess.Broadcast();
		}
		else
		{
			OnConnectToServerFailure.Broadcast();
		}
	}

	FString Response;
	if (!ListenForResponse(Response))
	{
		return;
	}
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response);
	TSharedPtr<FJsonObject> Object;
	FJsonSerializer::Deserialize(Reader, Object);

	// TODO
	// Make this not bad
	FString Function = Object->GetStringField("func");
	if (Function == LOGIN)
	{
		LoginResponse(Object);
	}
	else if (Function == JOIN_QUEUE)
	{
		JoinQueueResponse(Object);
	}
	else if (Function == EXIT_QUEUE)
	{
		ExitQueueResponse(Object);
	}
	else if (Function == GAME_FOUND)
	{
		GameFoundEvent(Object);
	}
	else if (Function == GAME_DETAILS)
	{
		GameReceiveDetails(Object);
	}
	else if (Function == GAME_CANCELLED)
	{
		GameCancelledEvent(Object);
	}
}

bool UMatchMaker::IsTickable() const
{
	return true;
}

TStatId UMatchMaker::GetStatId() const
{
	return GetStatID();
}

void UMatchMaker::ConnectToServer()
{
	if (bIsConnected)
	{
		return;
	}
	Async(EAsyncExecution::TaskGraph, [&] {Connect(); }, [&] {ConnectedDelegate(); });
}

void UMatchMaker::Connect()
{
	if (!Sock.IsValid())
	{
		O_LOG(TEXT("Sock is null"));
		return;
	}
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	Addr->SetIp(TEXT("127.0.0.1"), bIsValid);
	Addr->SetPort(1337);
	Sock->Connect(*Addr);
}

void UMatchMaker::ConnectedDelegate()
{
	if (!Sock.IsValid())
	{
		O_LOG(TEXT("Sock is null"));
		return;
	}
	bIsConnected = true;
	bNotifyConnectionStatus = true;
	if (Sock->GetConnectionState() != ESocketConnectionState::SCS_Connected)
	{
		bIsConnected = false;
	}
	O_LOG(TEXT("Connection To Server %s"), bIsConnected ? TEXT("Success") : TEXT("Failure"));
}

void UMatchMaker::Login(FString UserName, FString Password)
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetLogin(UserName, Password, RequestToken);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, Object);

	if (!bSuccess)
	{
		OnSendMessageFailure.Broadcast();
	}
	O_LOG(TEXT("Login Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::LoginResponse(TSharedPtr<FJsonObject> Response)
{
	int32 Status = Response->GetIntegerField("ret");

	EMatchMakingStatus MStatus = (EMatchMakingStatus)Status;
	
	if (Status)
	{
		FText StatusString = GetTextFromStatus(MStatus);
		OnLoginFailure.Broadcast(StatusString);
		return;
	}
	SessionToken = Response->GetStringField("session_token");
	OnLoginSuccess.Broadcast();
}

void UMatchMaker::JoinQueue()
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetJoinQueue(SessionToken, RequestToken);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, Object);

	if (!bSuccess)
	{
		OnSendMessageFailure.Broadcast();
	}
	O_LOG(TEXT("Join Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::JoinQueueResponse(TSharedPtr<FJsonObject> Response)
{
	int32 Status = Response->GetIntegerField("ret");

	EMatchMakingStatus MStatus = (EMatchMakingStatus)Status;

	if (Status)
	{
		FText StatusString = GetTextFromStatus(MStatus);
		OnJoinQueueFailure.Broadcast(StatusString);
		return;
	}

	OnJoinQueueSuccess.Broadcast();
}

void UMatchMaker::ExitQueue()
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetExitQueue(SessionToken, RequestToken);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, Object);

	if (!bSuccess)
	{
		OnSendMessageFailure.Broadcast();
	}
	O_LOG(TEXT("Exit Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::ExitQueueResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::GameCancelledEvent(TSharedPtr<FJsonObject> Response)
{
	OnGameCancelled.Broadcast();
}

void UMatchMaker::GameFoundEvent(TSharedPtr<FJsonObject> Response)
{
	OnGameFound.Broadcast();
	GameAcceptToken = Response->GetStringField(REQUEST_TOKEN);
}

void UMatchMaker::GameFoundResponse(bool bAccepted)
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetGameAccepted(SessionToken, bAccepted, MakeShared<FString>(GameAcceptToken));
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, Object);

	if (!bSuccess)
	{
		OnSendMessageFailure.Broadcast();
	}
}

void UMatchMaker::GameReceiveDetails(TSharedPtr<FJsonObject> Response)
{
	O_LOG(TEXT("Time to start! %s"), *Response->GetStringField("connection_string"));
	OnJoinMatch.Broadcast();

	//APlayerController* PC = GameInstance->GetWorld()->GetFirstPlayerController();

	//PC->ClientTravel(Response->GetStringField("connection_string"), ETravelType::TRAVEL_Absolute);
}

bool UMatchMaker::ListenForResponse(FString& Response)
{
	uint32 DataSize;
	if (!Sock->HasPendingData(DataSize))
	{
		return false;
	}
	// First we have to check the payload of bytes, saving it into HeaderBuff
	uint8 HeaderBuff[4] = { 0 };
	int32 Bread;
	Sock->Recv(HeaderBuff, 4, Bread);
	FMemory::Memcpy(&DataSize, HeaderBuff, 4);

	// We allocate Data with the amount of incoming bytes, to use it as a uint8* 
	TArray<uint8> Data;
	Data.SetNum(DataSize);
	Sock->Recv(Data.GetData(), DataSize, Bread);
	for (int32 i = 0; i < Bread; i++)
	{
		Data[i]--;
	}
	Response = BytesToString(Data.GetData(), Bread);
	// BytesToString adds 1 to every byte, so we then subtract one from each
	O_LOG(TEXT("%s"), *Response);
	return true;
}

void UMatchMaker::SetGameInstance(UOgnamGameInstance* Instance)
{
	GameInstance = Instance;
}

FText UMatchMaker::GetTextFromStatus(EMatchMakingStatus Code)
{
	switch (Code)
	{
	case EMatchMakingStatus::Success:
		return FText::FromString("Success");
	case EMatchMakingStatus::BadLogin:
		return BadLogin;
	case EMatchMakingStatus::UserBanned:
		return UserBanned;
	case EMatchMakingStatus::BadVersion:
		return BadVersion;
	case EMatchMakingStatus::Maintenance:
		return Maintenance;
	case EMatchMakingStatus::MatchmakingBanned:
		return MatchmakingBanned;
	case EMatchMakingStatus::BadLevel:
		return BadLevel;
	case EMatchMakingStatus::QueueDisabled:
		return QueueDisabled;
	case EMatchMakingStatus::AlreadyInQueue:
		return AlreadyInQueue;
	case EMatchMakingStatus::InvalidSession:
		return InvalidSession;
	case EMatchMakingStatus::AlreadyLoggedIn:
		return AlreadyLoggedIn;
	}
	return FText::FromString("Success"); // Unreachable
}
