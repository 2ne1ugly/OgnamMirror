// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraExplosiveArrow.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "HereiraExplosion.h"
#include "HereiraWillExplode.h"

void AHereiraExplosiveArrow::EndLifeSpan()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Instigator;
	AHereiraExplosion* Explosion = GetWorld()->SpawnActor<AHereiraExplosion>(GetActorLocation(), FRotator::ZeroRotator, SpawnParameters);
	Explosion->SetReplicates(true);
	Destroy();
}

void AHereiraExplosiveArrow::OnCharacterHit(AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* ControllerPlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (OtherPlayerState && ControllerPlayerState && OtherPlayerState->GetTeam() != ControllerPlayerState->GetTeam())
	{
		AController* Controller = Instigator->GetController();
		float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
		FVector Acceleration = Gravity * FVector::DownVector;
		FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

		UGameplayStatics::ApplyPointDamage(OtherCharacter, 45, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);
		UHereiraWillExplode* Explosion = NewObject<UHereiraWillExplode>(this);
		Explosion->SetInstigator(Instigator);
		OtherCharacter->ApplyModifier(Explosion);
	}
	Destroy();
}

void AHereiraExplosiveArrow::OnActorHit(AActor* OtherCharacter, const FHitResult& SweepResult)
{
	if (Instigator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s No Instigator!"), __FUNCTIONW__);
		return;
	}

	AController* Controller = Instigator->GetController();
	float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(LifeSpan);
	FVector Acceleration = Gravity * FVector::DownVector;
	FVector Velocity = InitialVelocity + ElapsedTime * Acceleration;

	UGameplayStatics::ApplyPointDamage(OtherCharacter, 45, Velocity.GetSafeNormal(), SweepResult, Controller, this, nullptr);
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraExplosiveArrow::EndLifeSpan, 0.5f, false);
}
