// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamStatics.h"
#include "OgnamEnum.h"
#include "OgnamPlayerstate.h"
#include "OgnamGameState.h"
#include "kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SoundSnapshot.h"
#include "Components/SkeletalMeshComponent.h"
#include "OgnamMacro.h"
#include "OgnamCharacter.h"

bool UOgnamStatics::CanDamage(const UObject* WorldContextObject, AOgnamPlayerState* DamageInstigator, IKillable* Reciever, EDamageMethod DamageMethod)
{
	return Reciever->CanBeKilledBy(DamageInstigator, DamageMethod);

	//return Cast<AOgnamGameState>(UGameplayStatics::GetGameState(WorldContextObject))->CanDamage(DamageInstigator, Reciever, DamageMethod);
}

bool UOgnamStatics::CanDamage(const UObject* WorldContextObject, APawn* DamageInstigator, IKillable* Reciever, EDamageMethod DamageMethod)
{
	AOgnamPlayerState* InstigatorPlayerState = DamageInstigator ? DamageInstigator->GetPlayerState<AOgnamPlayerState>() : nullptr;

	return Reciever->CanBeKilledBy(InstigatorPlayerState, DamageMethod);
	//AOgnamPlayerState* RecieverPlayerState = Reciever ? Reciever->CanBeKilledBy() : nullptr;
	//return Cast<AOgnamGameState>(UGameplayStatics::GetGameState(WorldContextObject))->CanDamage(InstigatorPlayerState, RecieverPlayerState, DamageMethod);
}

void UOgnamStatics::PlaySnapshotableSoundAtLocation(const UObject* WorldContextObject, class USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, AActor* OwningActor)
{
	UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, OwningActor);

	if (!OwningActor)
	{
		O_LOG(TEXT("No owning actor!"));
		return;
	}
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!MyPlayerController->IsLocalPlayerController())
	{
		return;
	}
	AOgnamCharacter* MyCharacter = Cast<AOgnamCharacter>(MyPlayerController->GetPawn());
	AOgnamPlayerState* MyPlayerState = Cast<AOgnamPlayerState>(MyPlayerController->GetPawn());

	//Use it only for enemies (only for pawns for now)
	if (OwningActor && MyCharacter &&
		MyCharacter->GetTacticalAmount() > 0.5f &&
		CanDamage(WorldContextObject, MyPlayerState, Cast<IKillable>(OwningActor), EDamageMethod::DamagesEnemy))
	{
		USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(OwningActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		FActorSpawnParameters Params;
		ASoundSnapshot* SnapshotActor = WorldContextObject->GetWorld()->SpawnActor<ASoundSnapshot>();
		SnapshotActor->Snapshot(SkeletalMesh);
	}
}
