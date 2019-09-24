// Fill out your copyright notice in the Description page of Project Settings.


#include "IsmaelFlashedModifier.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerController.h"
#include "Engine/World.h"
#include "Components/PostProcessComponent.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
UIsmaelFlashedModifier::UIsmaelFlashedModifier()
{
	Duration = 3.f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("Material'/Game/Material/Blind.Blind'"));
	Material = Mat.Object;
}

void UIsmaelFlashedModifier::BeginModifier()
{
	Super::BeginModifier();
	UE_LOG(LogTemp, Warning, TEXT("BeginModifier"));
	if (Target->Controller && Target->Controller->IsLocalController())
	{
		Target->Camera->PostProcessSettings.AddBlendable(Material, 1.f);
	}
}

void UIsmaelFlashedModifier::EndModifier()
{
	Super::EndModifier();

	if (Target->Controller && Target->Controller->IsLocalController())
	{
		Target->Camera->PostProcessSettings.RemoveBlendable(Material);
	}
}