// Fill out your copyright notice in the Description page of Project Settings.


#include "Asha.h"
#include "Ognam/OgnamMacro.h"
#include "AshaThrowingDaggers.h"
#include "AshaWhirlingBlades.h"
#include "AshaFanofKnives.h"
#include "Components/SkeletalMeshComponent.h"

AAsha::AAsha()
{
	GetMesh()->SetRelativeScale3D(FVector(0.95f));
	BaseMaxHealth = 200.f;

	CharacterName = FText::FromString("Asha");

	static ConstructorHelpers::FObjectFinder<UTexture2D> ImageTextureCH(TEXT("Texture2D'/Game/UI/CharacterImage/Asha.Asha'"));
	CharacterImage = ImageTextureCH.Object;

	Info.CharacterImage = CharacterImage;
	Info.CharacterName = CharacterName;
	Info.CharacterDescription = FText::FromString("Left Hand of Fort Kyo - Asha is an assassin. Her throwing knives deal low damage, but her skills are powerful.");
	Info.MobilityDes = FText::FromString("Dashes forward, slicing enemies with her blade.");
	Info.MobilityIcon = Cast<UAbility>(UAshaWhirlingBlades::StaticClass()->GetDefaultObject())->GetIcon();
	Info.SpecialDes = FText::FromString("");
	Info.SpecialIcon = nullptr;
	Info.UniqueDes = FText::FromString("Throws knives in a cone.");
	Info.UniqueIcon = Cast<UAbility>(UAshaFanofKnives::StaticClass()->GetDefaultObject())->GetIcon();
	Info.UtilityDes = FText::FromString("");
	Info.UtilityIcon = nullptr;
}

void AAsha::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UAshaThrowingDaggers>(this, TEXT("Weapon"));
	Mobility = NewObject<UAshaWhirlingBlades>(this, TEXT("Mobility"));
	Unique = NewObject<UAshaFanofKnives>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
