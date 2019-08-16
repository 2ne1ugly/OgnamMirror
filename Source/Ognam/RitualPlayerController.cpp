// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerController.h"
#include "RitualPlayerState.h"
#include "RitualGameState.h"
#include "Engine/World.h"

bool ARitualPlayerController::GetIsReady() const
{
	return bIsReady;
}

FName ARitualPlayerController::GetTeam() const
{
	return Team;
}

void ARitualPlayerController::SetTeam(FName name)
{
	Team = name;
}

int32 ARitualPlayerController::GetTeamIndex() const
{
	return TeamIndex;
}

void ARitualPlayerController::SetTeamIndex(int32 index)
{
	TeamIndex = index;
}

void ARitualPlayerController::GetReady_Implementation(int32 index, FName team)
{
	// init pre-game, player state is not valid on pregame.
	ARitualPlayerState* PlayerState = GetPlayerState<ARitualPlayerState>();
	Team = team;
	TeamIndex = index;

	// send "Ready" sign to server.
	ServerReady();
}

void ARitualPlayerController::ServerReady_Implementation()
{
	bIsReady = true;
}

FName ARitualPlayerController::GetSide() const
{
	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game state not valid!"));
		return FName();
	}

	if (Team.IsEqual(GameState->GetCurrentOffenseTeam()))
	{
		return GameState->OffenseName;
	}
	else if (Team.IsEqual(GameState->GetCurrentDefenseTeam()))
	{
		return GameState->DefenseName;
	}
	UE_LOG(LogTemp, Warning, TEXT("Team name not valid!"));
	return FName();
}
