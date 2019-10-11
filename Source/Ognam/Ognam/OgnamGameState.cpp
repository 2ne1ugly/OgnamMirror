// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameState.h"
#include "OgnamMacro.h"
#include "UnrealNetwork.h"
#include "OgnamPlayerState.h"
#include "OgnamCharacter.h"
#include "Subsystem.h"
#include "OnlineSubsystem.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

AOgnamGameState::AOgnamGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AOgnamGameState::BeginPlay()
{
	Super::BeginPlay();

	bool bCanBind;
	TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get()->GetLocalHostAddr(*GLog, bCanBind);
	ServerAddress = FString::Printf(TEXT("%s:%d"), *(LocalIP->ToString(false)), GetWorld()->URL.Port);
}

void AOgnamGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Count number of players on both teams(maybe find a better way)
	int32 ACount = 0;
	int32 BCount = 0;
	for (APlayerState* PlayerState : PlayerArray)
	{
		AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(PlayerState->GetPawn());
		if (OgnamCharacter != nullptr && OgnamCharacter->IsAlive())
		{
			ACount++;
		}
	}
	TeamBCount = BCount;
	TeamACount = ACount;
}

void AOgnamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamGameState, TeamACount);
	DOREPLIFETIME(AOgnamGameState, TeamBCount);
}

int32 AOgnamGameState::GetTeamACount() const
{
	return TeamACount;
}

int32 AOgnamGameState::GetTeamBCount() const
{
	return TeamBCount;
}

FString AOgnamGameState::GetServerIP() const
{
	return ServerAddress;
}
