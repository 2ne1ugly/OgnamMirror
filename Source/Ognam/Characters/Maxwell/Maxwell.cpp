// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "MaxwellSniperRifle.h"
#include "MaxwellShadowShift.h"
#include "MaxwellVault.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AMaxwell::AMaxwell()
{
	CharacterName = FText::FromString("Maxwell");

	BaseMaxHealth = 150.f;
	MaxHealth = BaseMaxHealth;
	Health = BaseMaxHealth;

	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(
		TEXT("AnimBlueprint'/Game/Animation/Maxwell/MaxwellAnim.MaxwellAnim_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/Meshes/Maxwell/Maxwell.Maxwell'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
}

void AMaxwell::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UMaxwellSniperRifle>(this, TEXT("Weapon"));
	Mobility = NewObject<UMaxwellShadowShift>(this, TEXT("Mobility"));
	Unique = NewObject<UMaxwellVault>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
