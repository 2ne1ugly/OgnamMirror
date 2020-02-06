// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableStructure.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamPlayerState.h"
#include "Ognam/OgnamGameState.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"

ABreakableStructure::ABreakableStructure()
{
	MaxHealth = 300;
	Health = MaxHealth;
	bIsAlive = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshCH(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(MeshCH.Object);
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetReplicates(true);
}

UFUNCTION(BluePrintCallable)
int32 ABreakableStructure::GetHealth() const
{
	return Health;
}

UFUNCTION(BluePrintCallable)
int32 ABreakableStructure::GetMaxHealth() const
{
	return MaxHealth;
}

void ABreakableStructure::Reset()
{
	Super::Reset();
	bIsAlive = true;
	MaxHealth = 300;
	Health = MaxHealth;
	// need to make mesh appear again
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetVisibility(true, false);
	//NetReset();
}

void ABreakableStructure::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABreakableStructure, MaxHealth);
	DOREPLIFETIME(ABreakableStructure, Health);
	DOREPLIFETIME(ABreakableStructure, bIsAlive);
}

float ABreakableStructure::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AppliedDamage = Damage;
	if (bIsAlive)
	{
		Health -= AppliedDamage;
		if (Health <= 0)
		{
			NetDie();
		}
	}
	O_LOG(TEXT("pewpew"));
	return AppliedDamage;
}
void ABreakableStructure::NetDie_Implementation()
{
	bIsAlive = false;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetVisibility(false, true);
}

bool ABreakableStructure::CanBeKilledBy(class AOgnamPlayerState* DamageInstigator, EDamageMethod DamageMethod)
{
	AOgnamPlayerState* OgnamPlayerState = nullptr;
	AOgnamGameState* OgnamGameState = GetWorld()->GetGameState<AOgnamGameState>();

	return OgnamGameState->CanDamage(DamageInstigator, OgnamPlayerState, DamageMethod);
}
