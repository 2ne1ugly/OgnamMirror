// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerState.h"
#include "RitualGameState.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"
#include "RitualSpectator.h"

ARitualPlayerState::ARitualPlayerState()
{
	Team = TEXT("Undefined");
	bIsAlive = false;
}

void ARitualPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARitualPlayerState, Team);
	DOREPLIFETIME(ARitualPlayerState, TeamIndex);
}

void ARitualPlayerState::NotifyDeath(AActor* Causer, AActor* Reciever, AController* DeathInstigator, AController* RecieverController)
{
	Super::NotifyDeath(Causer, Reciever, DeathInstigator, RecieverController);
	bIsAlive = false;
	ARitualSpectator* Spectator = GetWorld()->SpawnActor<ARitualSpectator>(Reciever->GetActorLocation(), Reciever->GetActorRotation());
	Spectator->SetReplicates(true);
	RecieverController->Possess(Spectator);
}

void ARitualPlayerState::SetTeamIndex(int32 index)
{
	TeamIndex = index;
}

int32 ARitualPlayerState::GetTeamIndex() const
{
	return TeamIndex;
}

FName ARitualPlayerState::GetSide() const
{
	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (!GameState)
	{
		O_LOG(TEXT("Game state not valid!"));
		return FName();
	}

	if (Team == GameState->GetCurrentOffenseTeam())
	{
		return GameState->OffenseName;
	}
	else if (Team == GameState->GetCurrentDefenseTeam())
	{
		return GameState->DefenseName;
	}
	O_LOG(TEXT("Team name not valid!"));
	return FName();
}

void ARitualPlayerState::ClientStartPreRound_Implementation()
{
	OnStartPreRound.Broadcast();
}

void ARitualPlayerState::ClientEndPreRound_Implementation()
{
	OnEndPreRound.Broadcast();
}

void ARitualPlayerState::ClientBeginRound_Implementation()
{
	O_LOG(TEXT("Beginning round"));

	OnBeginRound.Broadcast();
}

void ARitualPlayerState::ClientStartPostRound_Implementation()
{
	OnStartPostRound.Broadcast();
}

void ARitualPlayerState::ClientEndPostRound_Implementation()
{
	OnEndPostRound.Broadcast();
}

void ARitualPlayerState::ClientEndRound_Implementation()
{
	OnEndRound.Broadcast();
}
