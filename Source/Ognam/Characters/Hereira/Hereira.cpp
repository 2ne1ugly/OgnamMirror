// Fill out your copyright notice in the Description page of Project Settings.

#include "Hereira.h"
#include "HereiraSprint.h"
#include "HereiraCrossbow.h"
#include "HereiraThrowMolotov.h"
#include "Sound/SoundCue.h"
#include "Components/SkeletalMeshComponent.h"

AHereira::AHereira()
{
	CharacterName = FText::FromString(TEXT("Hereira"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageTextureCH(TEXT("Texture2D'/Game/UI/CharacterImage/HereraImage.HereraImage'"));
	CharacterImage = ImageTextureCH.Object;

	Info.CharacterImage = CharacterImage;
	Info.CharacterName = CharacterName;
	Info.CharacterDescription = FText::FromString("Masked Woman - Uses a crossbow that deals high damage.");
	Info.MobilityDes = FText::FromString("Increases movement speed for 6 seconds.");
	Info.MobilityIcon = Cast<UAbility>(UHereiraSprint::StaticClass()->GetDefaultObject())->GetIcon();
	Info.SpecialDes = FText::FromString("");
	Info.SpecialIcon = nullptr;
	Info.UniqueDes = FText::FromString("Throws a molotov that explodes and leaves a pool of fire that can burn allies and opponents.");
	Info.UniqueIcon = Cast<UAbility>(UHereiraThrowMolotov::StaticClass()->GetDefaultObject())->GetIcon();
	Info.UtilityDes = FText::FromString("");
	Info.UtilityIcon = nullptr;
}

void AHereira::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UHereiraCrossbow>(this, TEXT("Weapon"));
	Mobility = NewObject<UHereiraSprint>(this, TEXT("Mobility"));
	Unique = NewObject<UHereiraThrowMolotov>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
