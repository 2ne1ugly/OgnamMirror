// Fill out your copyright notice in the Description page of Project Settings.


#include "Jera.h"
#include "JeraCrystalArms.h"
#include "JeraRadiantDive.h"
#include "JeraSuppressiveImpact.h"
#include "Ognam/OgnamMacro.h"
#include "Components/SkeletalMeshComponent.h"

AJera::AJera()
{
	GetMesh()->SetRelativeScale3D(FVector(1.1f));
	BaseMaxHealth = 250.f;

	CharacterName = FText::FromString("Jera");

	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageTextureCH(TEXT("Texture2D'/Game/UI/CharacterImage/JeraImage.JeraImage'"));
	CharacterImage = ImageTextureCH.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> WalkingCue(TEXT("SoundCue'/Game/Sounds/Jera/Jera_walk_Cue.Jera_walk_Cue'"));
	WalkingSoundCue = WalkingCue.Object;

	Info.CharacterImage = CharacterImage;
	Info.CharacterName = CharacterName;
	Info.CharacterDescription = FText::FromString("Frost Elemental - Uses melee attacks, and a secondary attack that launches a spear of ice. Has more health, allowing him to be used as a tank.");
	Info.MobilityDes = FText::FromString("Leaps forward dealing damage on impact.");
	Info.MobilityIcon = Cast<UAbility>(UJeraRadiantDive::StaticClass()->GetDefaultObject())->GetIcon();
	Info.SpecialDes = FText::FromString("");
	Info.SpecialIcon = nullptr;
	Info.UniqueDes = FText::FromString("Launches a large spear of ice.");
	Info.UniqueIcon = Cast<UAbility>(UJeraSuppressiveImpact::StaticClass()->GetDefaultObject())->GetIcon();
	Info.UtilityDes = FText::FromString("");
	Info.UtilityIcon = nullptr;
}

void AJera::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UJeraCrystalArms>(this, TEXT("Weapon"));
	Mobility = NewObject<UJeraRadiantDive>(this, TEXT("Mobility"));
	Unique = NewObject<UJeraSuppressiveImpact>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
