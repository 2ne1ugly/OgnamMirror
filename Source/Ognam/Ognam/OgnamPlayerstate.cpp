// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerState.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

AOgnamPlayerState::AOgnamPlayerState()
{
	Name = "Name me";
	NumKill = 0;
	NumDeath = 0;
	Team = TEXT("No Team");
}

void AOgnamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamPlayerState, Name);
	DOREPLIFETIME(AOgnamPlayerState, NumKill);
	DOREPLIFETIME(AOgnamPlayerState, NumDeath);
	DOREPLIFETIME(AOgnamPlayerState, Team);
}

void AOgnamPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
			OgnamPlayerState->Name = Name;
		}
	}
}

void AOgnamPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
			Name = OgnamPlayerState->Name;
		}
	}
}

void AOgnamPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName AOgnamPlayerState::GetTeam() const
{
	return Team;
}

void AOgnamPlayerState::NetReceiveMessage_Implementation(const FString& Message, APlayerState* Sender)
{
	if (GEngine->GetFirstLocalPlayerController(GetWorld()) &&
		GEngine->GetFirstLocalPlayerController(GetWorld())->GetPlayerState<APlayerState>() != Sender)
	{
		DisplayMessage(Message, Sender);
	}
}

void AOgnamPlayerState::ServerSendMessage_Implementation(const FString& Message)
{
	NetReceiveMessage(Message, this);
}

void AOgnamPlayerState::DisplayMessage(const FString& Message, APlayerState* Sender)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%s: %s"), *Sender->GetPlayerName(), *Message));
}
