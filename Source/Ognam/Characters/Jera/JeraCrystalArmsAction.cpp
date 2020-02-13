// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraCrystalArmsAction.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamPlayerState.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

UJeraCrystalArmsAction::UJeraCrystalArmsAction()
{
	PreDelayDuration = .2f;
	ChannelDuration = .2f;
	PostDelayDuration = .4f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	DamageBoxMaterial = Material.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	DamageBoxMesh = Mesh.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> PunchSoundCueFinder(TEXT("SoundCue'/Game/Sounds/Jera/Jera_punch_Cue.Jera_punch_Cue'"));
	PunchSoundCue = PunchSoundCueFinder.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundCueFinder(TEXT("SoundCue'/Game/Sounds/Jera/Jera_punch_connected_Cue.Jera_punch_connected_Cue'"));
	HitSoundCue = HitSoundCueFinder.Object;
}

void UJeraCrystalArmsAction::BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger = NewObject<UStaticMeshComponent>(GetOwner());
	BoxTrigger->bHiddenInGame = false;

	BoxTrigger->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	BoxTrigger->SetStaticMesh(DamageBoxMesh);
	BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	BoxTrigger->SetRelativeScale3D(FVector(2.5f));
	BoxTrigger->SetMaterial(0, DamageBoxMaterial);
	BoxTrigger->SetVisibility(false);
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &UJeraCrystalArmsAction::BeginOverlap);
	BoxTrigger->MoveIgnoreActors.Add(GetOwner());
	BoxTrigger->RegisterComponent();

	PunchSound = NewObject<UAudioComponent>(GetOwner());
	PunchSound->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	PunchSound->SetRelativeLocation(FVector::ZeroVector);
	PunchSound->SetAutoActivate(false);
	PunchSound->SetSound(PunchSoundCue);
	PunchSound->RegisterComponent();

	HitSound = NewObject<UAudioComponent>(GetOwner());
	HitSound->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	HitSound->SetRelativeLocation(FVector::ZeroVector);
	HitSound->SetAutoActivate(false);
	HitSound->SetSound(HitSoundCue);
	HitSound->RegisterComponent();
}

void UJeraCrystalArmsAction::BeginChannel()
{
	StrikedCharacters.Empty();
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxTrigger->SetVisibility(true);
	PunchSound->Activate();
}

void UJeraCrystalArmsAction::EndChannel()
{
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetVisibility(false);
}

void UJeraCrystalArmsAction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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
		NetPlayHitSound();
	}
}

void UJeraCrystalArmsAction::StatusEffectApplied(EStatusEffect Effect)
{
	if (Stage == EActionStage::PreDelay)
	{
		return;
	}
}

void UJeraCrystalArmsAction::ActionTaken(EActionNotifier ActionType)
{
	if (Stage == EActionStage::PreDelay)
	{
		return;
	}
	if ((ActionType & EActionNotifier::Death) != EActionNotifier::None)
	{
		Interrupt();
	}
}

void UJeraCrystalArmsAction::NetPlayHitSound_Implementation()
{
	HitSound->Activate();
}
