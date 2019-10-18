// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundClawsAction.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Ognam/OgnamPlayerstate.h"

UBloodhoundClawsAction::UBloodhoundClawsAction()
{
	PreDelayDuration = .25f;
	ChannelDuration = .25f;
	PostDelayDuration = .45f;

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Material/DamageZone.DamageZone'"));
	DamageBoxMaterial = Material.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	DamageBoxMesh = Mesh.Object;
}

void UBloodhoundClawsAction::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger = NewObject<UStaticMeshComponent>(GetOwner());
	BoxTrigger->bHiddenInGame = false;

	BoxTrigger->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	BoxTrigger->SetStaticMesh(DamageBoxMesh);
	BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	BoxTrigger->SetRelativeScale3D(FVector(1.f));
	BoxTrigger->SetMaterial(0, DamageBoxMaterial);
	BoxTrigger->SetVisibility(false);

	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &UBloodhoundClawsAction::BeginOverlap);
	BoxTrigger->MoveIgnoreActors.Add(GetOwner());

	BoxTrigger->RegisterComponent();
}

void UBloodhoundClawsAction::BeginChannel()
{
	StrikedCharacters.Empty();
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxTrigger->SetVisibility(true);
}

void UBloodhoundClawsAction::EndChannel()
{
	BoxTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxTrigger->SetVisibility(false);
}

void UBloodhoundClawsAction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (!Character || StrikedCharacters.Contains(Character))
	{
		return;
	}
	StrikedCharacters.Add(Character);

	//Get owners playerState
	AController* Controller = GetOwner()->GetInstigatorController();
	if (!Controller)
	{
		return ;
	}
	AOgnamPlayerState* PlayerState = Controller->GetPlayerState<AOgnamPlayerState>();
	if (!PlayerState)
	{
		return;
	}

	//Get affected Actor's playerState
	AController* OtherController = Character->GetInstigatorController();
	if (!OtherController)
	{
		return;
	}
	AOgnamPlayerState* OtherPlayerState = OtherController->GetPlayerState<AOgnamPlayerState>();
	if (!OtherPlayerState)
	{
		return;
	}

	if (PlayerState->GetTeam() != OtherPlayerState->GetTeam())
	{
		UGameplayStatics::ApplyDamage(Character, 40.f, Target->GetController(), Target, nullptr);
	}
}

void UBloodhoundClawsAction::StatusEffectApplied(EStatusEffect Effect)
{
	if (Stage == EActionStage::PreDelay)
	{
		return;
	}
}

void UBloodhoundClawsAction::ActionTaken(EActionNotifier ActionType)
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
