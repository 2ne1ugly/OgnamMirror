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

	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageTextureCH(TEXT("Texture2D'/Game/UI/CharacterImage/Maxwellmage.Maxwellmage'"));
	CharacterImage = ImageTextureCH.Object;

	BaseMaxHealth = 150.f;
	MaxHealth = BaseMaxHealth;
	Health = BaseMaxHealth;

	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(
		TEXT("AnimBlueprint'/Game/Animation/Maxwell/MaxwellAnim.MaxwellAnim_C'"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/Meshes/Maxwell/Maxwell.Maxwell'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	GetMesh()->SetAnimInstanceClass(AnimBP.Object);

	Info.CharacterImage = CharacterImage;
	Info.CharacterName = CharacterName;
	Info.CharacterDescription = FText::FromString("Wraith Sniper - uses a rifle that deals more damage on headshots.");
	Info.MobilityDes = FText::FromString("Turn into a shadow and dashes a short distance.");
	Info.MobilityIcon = Cast<UAbility>(UMaxwellShadowShift::StaticClass()->GetDefaultObject())->GetIcon();
	Info.SpecialDes = FText::FromString("");
	Info.SpecialIcon = nullptr;
	Info.UniqueDes = FText::FromString("Turns into a shadow and jumps vertically.");
	Info.UniqueIcon = Cast<UAbility>(UMaxwellVault::StaticClass()->GetDefaultObject())->GetIcon();
	Info.UtilityDes = FText::FromString("");
	Info.UtilityIcon = nullptr;
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
