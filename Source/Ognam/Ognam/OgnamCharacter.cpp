// Fill out your copyright notice in the Description page of Project Settings.

#include "OgnamCharacter.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"
#include "UnrealNetwork.h"
#include "OgnamPlayerController.h"
#include "Weapon.h"
#include "Ability.h"
#include "Modifier.h"
#include "OgnamPlayerstate.h"
#include "Interfaces/Dispellable.h"
#include "OverwallHidden.h"
#include "OverwallTransparency.h"
#include "OgnamMacro.h"
#include "OgnamGameState.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "OgnamWidgetComponent.h"
#include "OgnamUserWidget.h"
#include "Engine/ActorChannel.h"

// Sets default values
AOgnamCharacter::AOgnamCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Spring arm and Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetArmLength = 250.f;
	SpringArm->SocketOffset = FVector(0.f, 40.f, 80.f);
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	//Default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(2);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(
		TEXT("/Game/Animation/OgnamCharacterAnimBlueprint.OgnamCharacterAnimBlueprint_C"));

	GetMesh()->SetAnimInstanceClass(AnimBP.Object);

	//For now, hide mesh only.
	OverwallHidden = CreateDefaultSubobject<UOverwallHidden>(TEXT("Overwall Hide"));
	OverwallHidden->AddTargetComponents(GetMesh());

	BaseMaxHealth = 200.f;
	BaseDefense = 0.f;
	BaseSpeed = 650.f;
	BaseHealthRegen = 0.5f;

	MaxHealth = BaseMaxHealth;

	Defense = BaseDefense;
	Speed = BaseSpeed;

	Health = MaxHealth;

	BaseAcceleration = 1536.f;
	BaseAirControl = 2.f;
	BaseGravity = 1.5f;

	GetCharacterMovement()->BrakingFrictionFactor = .5f;
	GetCharacterMovement()->JumpZVelocity = 510.f;
	GetCharacterMovement()->SetWalkableFloorAngle(38.f);
	bReplicates = true;
	bIsAlive = true;
	bCanMove = true;

	CharacterName = FText::FromString("Ognam Character");

	static ConstructorHelpers::FObjectFinder<UMaterial> RecievedMaterial(TEXT("Material'/Game/PostProcess/DamageRecieved.DamageRecieved'"));
	DamageRecievedMaterial = RecievedMaterial.Object;

	static ConstructorHelpers::FClassFinder<UUserWidget> NameTagWidgetClass(TEXT("/Game/UI/NameTag"));
	NameTagComponent = CreateDefaultSubobject<UOgnamWidgetComponent>(TEXT("Name Tag"));
	NameTagComponent->SetupAttachment(RootComponent);
	NameTagComponent->SetWidgetSpace(EWidgetSpace::World);
	NameTagComponent->SetRelativeLocation(FVector(0, 0, 90));
	NameTagComponent->SetOwnerNoSee(true);
	NameTagComponent->SetWidgetClass(NameTagWidgetClass.Class);
	NameTagComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<USoundCue> WalkingCue(TEXT("/Game/Animation/Step_Cue.Step_Cue"));
	WalkingSoundCue = WalkingCue.Object;
}

void AOgnamCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamCharacter, Health);
	DOREPLIFETIME(AOgnamCharacter, bIsJumping);
	DOREPLIFETIME(AOgnamCharacter, bIsAlive);
}

void AOgnamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MaxHealth = BaseMaxHealth;
	Defense = BaseDefense;
	Speed = BaseSpeed;
	Acceleration = BaseAcceleration;
	AirControl = BaseAirControl;
	Gravity = BaseGravity;
	HealthRegen = BaseHealthRegen;

	//Check ending conditions of Modiifers and apply tick.
	for (int i = Modifiers.Num() - 1; i >= 0; i--)
	{
		if (Modifiers[i]->ShouldEnd())
		{
			Modifiers[i]->DestroyComponent();
		}
		else
		{
			Modifiers[i]->TickModifier(DeltaTime);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	GetCharacterMovement()->MaxAcceleration = Acceleration;
	GetCharacterMovement()->AirControl = AirControl;
	GetCharacterMovement()->GravityScale = Gravity;

	if (NumInputs > 0)
	{
		InputAmount /= NumInputs;
		FVector Normal = InputVector.GetSafeNormal();
		float InputSpeed = GetSpeedFromVector(Normal);
		AddMovementInput(GetActorTransform().TransformVector(Normal), InputSpeed * InputAmount);

	}
	InputVector = FVector::ZeroVector;
	InputAmount = 0;
	NumInputs = 0;

	//Find Camera blocking plane
	if (HasAuthority() || (Controller && Controller->IsLocalPlayerController()))
	{
		UpdateCameraBlockingPlane();
	}

	//TODO: make this modular
	float Amount = GetWorldTimerManager().IsTimerActive(DamageTimer) ? GetWorldTimerManager().GetTimerRemaining(DamageTimer) / 3.f : 0.f;

	DamageInstance->SetScalarParameterValue(TEXT("Amount"), Amount);

	FVector CamLoc = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
	FVector CompLoc = NameTagComponent->GetComponentLocation();

	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(CompLoc, CamLoc);
	NameTagComponent->SetWorldRotation(FRotator(Rot.Pitch, Rot.Yaw, 0.f));

	//Health Regen
	if (IsAlive())
	{
		Health += HealthRegen * DeltaTime;
	}
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

void AOgnamCharacter::BeginPlay()
{
	Super::BeginPlay();

	DamageInstance = UMaterialInstanceDynamic::Create(DamageRecievedMaterial, this);
	Camera->PostProcessSettings.AddBlendable(DamageInstance, 1.f);
	NameTagComponent->InitWidget();
}

// Called to bind functionality to input
void AOgnamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFoward", this, &AOgnamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOgnamCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Basic", IE_Pressed, this, &AOgnamCharacter::BasicPressed);
	PlayerInputComponent->BindAction("Basic", IE_Released, this, &AOgnamCharacter::BasicReleased);
	PlayerInputComponent->BindAction("Sub", IE_Pressed, this, &AOgnamCharacter::SubPressed);
	PlayerInputComponent->BindAction("Sub", IE_Released, this, &AOgnamCharacter::SubReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AOgnamCharacter::ReloadPressed);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &AOgnamCharacter::ReloadReleased);
	PlayerInputComponent->BindAction("Mobility", IE_Pressed, this, &AOgnamCharacter::MobilityPressed);
	PlayerInputComponent->BindAction("Mobility", IE_Released, this, &AOgnamCharacter::MobilityReleased);
	PlayerInputComponent->BindAction("Unique", IE_Pressed, this, &AOgnamCharacter::UniquePressed);
	PlayerInputComponent->BindAction("Unique", IE_Released, this, &AOgnamCharacter::UniqueReleased);
	PlayerInputComponent->BindAction("Utility", IE_Pressed, this, &AOgnamCharacter::UtilityPressed);
	PlayerInputComponent->BindAction("Utility", IE_Released, this, &AOgnamCharacter::UtilityReleased);
	PlayerInputComponent->BindAction("Special", IE_Pressed, this, &AOgnamCharacter::SpecialPressed);
	PlayerInputComponent->BindAction("Special", IE_Released, this, &AOgnamCharacter::SpecialReleased);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AOgnamCharacter::Jump);
}

void AOgnamCharacter::OnRep_PlayerState()
{
	// Assign team color
	UMaterialInstanceConstant* Material = nullptr;
	AOgnamPlayerState* OgnamPlayerState = GetPlayerState<AOgnamPlayerState>();

	if (!OgnamPlayerState)
	{
		return;
	}

	if (OgnamPlayerState->GetTeam() == TEXT("Green"))
	{
		Material = LoadObject<UMaterialInstanceConstant>(this, TEXT("/Game/AnimStarterPack/UE4_Mannequin/Materials/M_GreenTeamBody.M_GreenTeamBody"));
	}
	else if (OgnamPlayerState->GetTeam() == TEXT("Blue"))
	{
		Material = LoadObject<UMaterialInstanceConstant>(this, TEXT("/Game/AnimStarterPack/UE4_Mannequin/Materials/M_BlueTeamBody.M_BlueTeamBody"));
	}

	GetMesh()->SetMaterial(0, Material);
}

void AOgnamCharacter::PossessedBy(AController * aController)
{
	Super::PossessedBy(aController);
	// Assign team color
	UMaterialInstanceConstant* Material = nullptr;
	AOgnamPlayerState* OgnamPlayerState = aController->GetPlayerState<AOgnamPlayerState>();

	if (!OgnamPlayerState)
	{
		return;
	}

	if (OgnamPlayerState->GetTeam() == TEXT("Green"))
	{
		Material = LoadObject<UMaterialInstanceConstant>(this, TEXT("/Game/AnimStarterPack/UE4_Mannequin/Materials/M_GreenTeamBody.M_GreenTeamBody"));
	}
	else if (OgnamPlayerState->GetTeam() == TEXT("Blue"))
	{
		Material = LoadObject<UMaterialInstanceConstant>(this, TEXT("/Game/AnimStarterPack/UE4_Mannequin/Materials/M_BlueTeamBody.M_BlueTeamBody"));
	}

	GetMesh()->SetMaterial(0, Material);
	OgnamPlayerState->SetPawnClass(GetClass());

	NameTagComponent->SetOwningState(OgnamPlayerState);
}

bool AOgnamCharacter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = false;

	for (UActorComponent* ActorComp : ReplicatedComponents)
	{
		if (ActorComp && ActorComp->GetIsReplicated())
		{
			bool bNetInitial = RepFlags->bNetInitial;
			RepFlags->bNetInitial = Channel->ReplicationMap.Find(ActorComp) == nullptr;

			WroteSomething |= ActorComp->ReplicateSubobjects(Channel, Bunch, RepFlags); // Lets the component add subobjects before replicating its own properties.
			WroteSomething |= Channel->ReplicateSubobject(ActorComp, *Bunch, *RepFlags); // (this makes those subobjects 'supported', and from here on those objects may have reference replicated)

			RepFlags->bNetInitial = bNetInitial;
		}
	}

	return WroteSomething;
}

void AOgnamCharacter::MobilityPressed()
{
	OnMobilityPressed.Broadcast();
}

void AOgnamCharacter::MobilityReleased()
{
	OnMobilityReleased.Broadcast();
}

void AOgnamCharacter::UniquePressed()
{
	OnUniquePressed.Broadcast();
}

void AOgnamCharacter::UniqueReleased()
{
	OnUniqueReleased.Broadcast();
}

void AOgnamCharacter::UtilityPressed()
{
	OnUtilityPressed.Broadcast();
}

void AOgnamCharacter::UtilityReleased()
{
	OnUtilityReleased.Broadcast();
}

void AOgnamCharacter::SpecialPressed()
{
	OnSpecialPressed.Broadcast();
}

void AOgnamCharacter::SpecialReleased()
{
	OnSpecialReleased.Broadcast();
}

void AOgnamCharacter::ReloadPressed()
{
	OnReloadPressed.Broadcast();
}

void AOgnamCharacter::ReloadReleased()
{
	OnReloadReleased.Broadcast();
}

void AOgnamCharacter::BasicPressed()
{
	OnBasicPressed.Broadcast();
}

void AOgnamCharacter::BasicReleased()
{
	OnBasicReleased.Broadcast();
}

void AOgnamCharacter::SubPressed()
{
	OnSubPressed.Broadcast();
}

void AOgnamCharacter::SubReleased()
{
	OnSubReleased.Broadcast();
}

void AOgnamCharacter::SetCamera(float ArmLength, FVector SocketOffset, float FOV)
{
	SpringArm->TargetArmLength = ArmLength;
	SpringArm->SocketOffset = SocketOffset;
	Camera->FieldOfView = FOV;
}
 
void AOgnamCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0.f && !HasStatusEffect(EStatusEffect::Rooted) && bCanMove)
	{
		InputVector += FVector::ForwardVector * Amount;
		InputAmount += FMath::Abs(Amount);
		NumInputs++;
	}
}

void AOgnamCharacter::MoveRight(float Amount)
{
	if (Controller != nullptr && Amount != 0.f && !HasStatusEffect(EStatusEffect::Rooted) && bCanMove)
	{
		InputVector += FVector::RightVector * Amount;
		InputAmount += FMath::Abs(Amount);
		NumInputs++;
	}
}

float AOgnamCharacter::GetHealth() const
{
	return Health;
}

float AOgnamCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

bool AOgnamCharacter::GetIsJumping() const
{
	return bIsJumping;
}

bool AOgnamCharacter::IsAlive() const
{
	return bIsAlive;
}

bool AOgnamCharacter::CanMove() const
{
	return bCanMove;
}

void AOgnamCharacter::SetCanMove(bool b)
{
	bCanMove = b;
}

UWeapon* AOgnamCharacter::GetWeapon() const
{
	return Weapon;
}

UAbility* AOgnamCharacter::GetUnique() const
{
	return Unique;
}

UAbility* AOgnamCharacter::GetUtility() const
{
	return Utility;
}

UAbility* AOgnamCharacter::GetSpecial() const
{
	return Special;
}

UAbility* AOgnamCharacter::GetMobility() const
{
	return Mobility;
}

FVector AOgnamCharacter::GetInputVector() const
{
	return InputVector;
}

void AOgnamCharacter::GetAimHitResult(FHitResult& HitResult, float near, float far)
{
	TArray<UCameraComponent*> Cameras;
	GetComponents(Cameras);
	
	UCameraComponent* ActiveCamera = nullptr;

	for (UCameraComponent* CameraComponent : Cameras)
	{
		if (CameraComponent->IsActive())
		{
			ActiveCamera = CameraComponent;
			break;
		}
	}
	if (!ActiveCamera)
	{
		O_LOG(TEXT("No active camera!"));
		ActiveCamera = Camera;
	}

	//shoot ray from camera to see where it should land.
	FVector RayFrom = ActiveCamera->GetComponentLocation() + near;
	FVector RayTo = RayFrom + ActiveCamera->GetForwardVector() * far;
	FCollisionQueryParams Params(TEXT("cameraPath"), true, this);
	Params.AddIgnoredActor(this);
	for (FHitResult& Hit : CameraHits)
	{
		Params.AddIgnoredActor(Hit.GetActor());
	}
	GetWorld()->LineTraceSingleByChannel(HitResult, RayFrom, RayTo, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

bool AOgnamCharacter::HasStatusEffect(EStatusEffect StatusEffect)
{
	for (UModifier* Modifier : Modifiers)
	{
		if ((Modifier->GetStatusEffect() & StatusEffect) != EStatusEffect::None)
		{
			return true;
		}
	}
	return false;
}

void AOgnamCharacter::TakeAction(EActionNotifier ActionType)
{
	//Give them a chance to dispell.
	if (Weapon && Weapon->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Weapon)->ActionTaken(ActionType);
	}
	if (Mobility && Mobility->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Mobility)->ActionTaken(ActionType);
	}
	if (Unique && Unique->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Unique)->ActionTaken(ActionType);
	}
	if (Utility && Utility->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Utility)->ActionTaken(ActionType);
	}
	if (Special && Special->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Special)->ActionTaken(ActionType);
	}
	for (UModifier* Modifier : Modifiers)
	{
		if (Modifier && Modifier->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
		{
			Cast<IDispellable>(Modifier)->ActionTaken(ActionType);
		}
	}
}

void AOgnamCharacter::ApplyStatusEffect(EStatusEffect StatusEffect)
{
	//Give them a chance to dispell.
	if (Weapon && Weapon->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Weapon)->StatusEffectApplied(StatusEffect);
	}
	if (Mobility && Mobility->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Mobility)->StatusEffectApplied(StatusEffect);
	}
	if (Unique && Unique->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Unique)->StatusEffectApplied(StatusEffect);
	}
	if (Utility && Utility->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Utility)->StatusEffectApplied(StatusEffect);
	}
	if (Special && Special->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
	{
		Cast<IDispellable>(Special)->StatusEffectApplied(StatusEffect);
	}
	for (UModifier* Modifier : Modifiers)
	{
		if (Modifier && Modifier->GetClass()->ImplementsInterface(UDispellable::StaticClass()))
		{
			Cast<IDispellable>(Modifier)->StatusEffectApplied(StatusEffect);
		}
	}
}

void AOgnamCharacter::ServerJump_Implementation()
{
	if (!GetCharacterMovement()->IsMovingOnGround() || HasStatusEffect(EStatusEffect::Rooted) || GetCharacterMovement()->Velocity.Z > 0.f)
	{
		return;
	}
	TakeAction(EActionNotifier::Jump);
	ACharacter::Jump();
	bIsJumping = true;
}

float AOgnamCharacter::GetDamageAfterDefense(float Damage)
{
	return Damage * Defense;
}

float AOgnamCharacter::GetSpeedFromVector(FVector Vector)
{
	return FMath::Square(Vector.Y) * .75f +
		((Vector.X > 0.f) ? (FMath::Square(Vector.X) * 1.f) : (FMath::Square(Vector.X) * .6f));
}

void AOgnamCharacter::UpdateCameraBlockingPlane()
{
	bCameraBlocked = false;
	FVector From = GetActorLocation();
	FVector To = Camera->GetComponentLocation();
	GetWorld()->LineTraceMultiByChannel(CameraHits, From, To, ECollisionChannel::ECC_Camera,
		FCollisionQueryParams::DefaultQueryParam, ECollisionResponse::ECR_Overlap);
	

	if (CameraHits.Num() > 0 && CameraHits[0].GetActor()->GetComponentByClass(UOverwallTransparency::StaticClass()))
	{
		bCameraBlocked = true;
		CameraBlockingPlane = FPlane(CameraHits[0].ImpactPoint, CameraHits[0].ImpactNormal);
	}
}

void AOgnamCharacter::Jump()
{
	if (!GetCharacterMovement()->IsMovingOnGround() || HasStatusEffect(EStatusEffect::Rooted) || !bCanMove)
	{
		return;
	}
	TakeAction(EActionNotifier::Jump);
	ACharacter::Jump();
	bIsJumping = true;
	ServerJump();
}

void AOgnamCharacter::Landed(const FHitResult& FHit)
{
	//Instant decel when reached the ground, consider method of having "Jump" cooldown
	if (GetCharacterMovement()->Velocity.Size() > GetCharacterMovement()->GetMaxSpeed())
	{
		GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity.GetSafeNormal() * GetCharacterMovement()->GetMaxSpeed();
	}
	bIsJumping = false;
}

float AOgnamCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AppliedDamage = Damage;
	if (HasStatusEffect(EStatusEffect::Unbreakable))
	{
		AppliedDamage = 0.f;
	}

	if (HasAuthority() && bIsAlive)
	{
		Health -= AppliedDamage;

		AOgnamGameState* GameState = GetWorld()->GetGameState<AOgnamGameState>();
		if (!GameState)
		{
			O_LOG(TEXT("Not Ognam GameState"));
			return AppliedDamage;
		}
		GameState->NotifyDamageEvent(DamageCauser, this, EventInstigator, GetController(), Damage);	//for now, we don't pass location info.
		if (Health <= 0)
		{
			NetDie();
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController)
			{
				DisableInput(PlayerController);
			}
			GameState->NotifyKillEvent(DamageCauser, this, EventInstigator, GetController());
		}
	}
	return AppliedDamage;
}

void AOgnamCharacter::NetDie_Implementation()
{
	GetMesh()->SetCollisionProfileName(TEXT("RagDoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	bIsAlive = false;
	TakeAction(EActionNotifier::Death);

	//For local player
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}
	DisableInput(PlayerController);
}

USoundCue* AOgnamCharacter::GetWalkingSound() const
{
	return WalkingSoundCue;
}
