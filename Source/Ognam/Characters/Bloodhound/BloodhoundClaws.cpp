// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundClaws.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "BloodhoundMarked.h"
#include "BloodhoundHuntingHour.h"
#include "BloodhoundLeap.h"

UBloodhoundClaws::UBloodhoundClaws()
{
	//TriggerClass = UStaticMeshComponent::StaticClass();
	//PreSwing = .25f;
	//PeriSwing = .25f;
	//PostSwing = .45f;
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	//DamageBoxMaterial = Material.Object;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	//DamageBoxMesh = Mesh.Object;
}

void UBloodhoundClaws::BeginPlay()
{
	Super::BeginPlay();
	//BoxTrigger = Cast<UStaticMeshComponent>(Trigger);
	//BoxTrigger->bHiddenInGame = false;

	//BoxTrigger->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	//BoxTrigger->SetStaticMesh(DamageBoxMesh);
	//BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	//BoxTrigger->SetRelativeScale3D(FVector(1.f));
	//BoxTrigger->SetMaterial(0, DamageBoxMaterial);
	//BoxTrigger->SetVisibility(false);
}

//void UBloodhoundClaws::ServerBasicPressed_Implementation()
//{
//	UBloodhoundHuntingHour* Hour = Target->GetModifier<UBloodhoundHuntingHour>();
//	if (!Hour)
//	{
//		Super::ServerBasicPressed_Implementation();
//	}
//	else
//	{
//		NewObject<UBloodhoundLeap>(Target)->RegisterComponent();
//	}
//}

//void UBloodhoundClaws::StartPeriSwing()
//{
//	Super::StartPeriSwing();
//	NetStartPeriSwing();
//}

//void UBloodhoundClaws::NetStartPeriSwing_Implementation()
//{
//	BoxTrigger->SetVisibility(true);
//	//if (!Target->HasAuthority())
//	//{
//		GetWorld()->GetTimerManager().SetTimer(BoxVisualizeTimer, this, &UBloodhoundClaws::EndPeriSwing, PeriSwing, false);
//	//}
//}

//void UBloodhoundClaws::EndPeriSwing()
//{
//	BoxTrigger->SetVisibility(false);
//}

//void UBloodhoundClaws::CharacterStrike(AOgnamCharacter* OtherCharacter)
//{
//	//UGameplayStatics::ApplyDamage(OtherCharacter, 40.f, Target->GetController(), Target, nullptr);
//	//UBloodhoundMarked* Marked = OtherCharacter->GetModifier<UBloodhoundMarked>();
//	//if (Marked)
//	//{
//	//	Marked->Consume();
//	//}
//}
