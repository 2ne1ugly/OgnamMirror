// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaWhirlingBladesAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

UAshaWhirlingBladesAction::UAshaWhirlingBladesAction()
{
	PreDelayDuration = .08f;
	ChannelDuration = .25f;
	PostDelayDuration = .3f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	DamageBoxMaterial = Material.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	DamageBoxMesh = Mesh.Object;
}



void UAshaWhirlingBladesAction::BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger = NewObject<UStaticMeshComponent>(GetOwner());
	BoxTrigger->bHiddenInGame = false;

	BoxTrigger->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	BoxTrigger->SetStaticMesh(DamageBoxMesh);
	BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	BoxTrigger->SetRelativeScale3D(FVector(0.25f, 3.0f, 2.5f));
	BoxTrigger->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	BoxTrigger->SetMaterial(0, DamageBoxMaterial);
	BoxTrigger->SetVisibility(false);
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &UAshaWhirlingBladesAction::BeginOverlap);
	BoxTrigger->MoveIgnoreActors.Add(GetOwner());
	BoxTrigger->RegisterComponent();
}

void UAshaWhirlingBladesAction::BeginPreDelay()
{
	Target->TakeAction(EActionNotifier::Focus);

	FVector FacingDirection = Target->Camera->GetForwardVector();
	FacingDirection.Z = FMath::Min(FacingDirection.Z, 0.f);
	FacingDirection.Z += 0.25;

	Target->GetCharacterMovement()->Velocity.Z = 0.f;
	Target->GetCharacterMovement()->AddImpulse(FacingDirection.GetSafeNormal() * 200000.f);
}

void UAshaWhirlingBladesAction::BeginChannel()
{
	StrikedCharacters.Empty();
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxTrigger->SetVisibility(true);
}

void UAshaWhirlingBladesAction::EndChannel()
{
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetVisibility(false);
}

void UAshaWhirlingBladesAction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	APawn* Character = Cast<APawn>(OtherActor);
	if (!Character || StrikedCharacters.Contains(Character))
	{
		return;
	}
	StrikedCharacters.Add(Character);

	APawn* Owner = Cast<APawn>(GetOwner());
	//Get owners playerState
	if (UOgnamStatics::CanDamage(GetWorld(), Owner, Character, EDamageMethod::DamagesEnemy))
	{
		UGameplayStatics::ApplyDamage(Character, 50.f, Owner->GetController(), Owner, nullptr);
	}
}
