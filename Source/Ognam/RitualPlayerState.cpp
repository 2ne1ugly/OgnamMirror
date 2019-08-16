// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerState.h"
#include "RitualGameState.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

ARitualPlayerState::ARitualPlayerState()
{
	Team = TEXT("Undefined");
}

void ARitualPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARitualPlayerState, Team);
}

void ARitualPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName ARitualPlayerState::GetTeam() const
{
	return Team;
}

void ARitualPlayerState::SetTeamIndex(int32 index)
{
	TeamIndex = index;
}

int32 ARitualPlayerState::GetTeamIndex() const
{
	//Get game state and find its index.
	//The reason why i do it this way is to make it always safe.
	//TODO: Find a efficient way to locate its index (Maybe a Key)
	//ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	//if (GameState == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Game state not valid!"));
	//	return INDEX_NONE;
	//}
	//if (Team.IsEqual(GameState->GreenName))
	//{
	//	return GameState->GreenPlayers.Find(this);
	//}
	//else if (Team.IsEqual(GameState->BlueName))
	//{
	//	return GameState->BluePlayers.Find(this);
	//}
	//UE_LOG(LogTemp, Warning, TEXT("Team name not valid!"));
	//return INDEX_NONE;
	return TeamIndex;
}

FName ARitualPlayerState::GetSide() const
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