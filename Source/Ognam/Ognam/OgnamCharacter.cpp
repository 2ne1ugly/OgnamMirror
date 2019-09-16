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
#include "OgnamPlayerstate.h"

// Sets default values
AOgnamCharacter::AOgnamCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	//Create Spring arm and Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetOffset = FVector(0, 0, 120);
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SetActorScale3D(FVector(.75f, .75f, .75f));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	//Default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//Animations for the mesh, if animation starts to get buggy, check if this code is right.
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(
		TEXT("/Game/Animation/OgnamCharacterAnimBlueprint.OgnamCharacterAnimBlueprint_C"));
	//static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP_PIE(
	//	TEXT("AnimBlueprint'/Game/Animation/OgnamCharacterAnimBlueprint.OgnamCharacterAnimBlueprint'"));
	//if (AnimBP_PIE.Object != nullptr)
	//{
	//	GetMesh()->SetAnimInstanceClass(AnimBP_PIE.Object->GeneratedClass);
	//}
	//else
	//{
		GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	//}

	BaseMaxHealth = 200.f;
	BaseDefense = 0.0f;
	BaseSpeed = 600.0f;

	MaxHealth = BaseMaxHealth;
	Defense = BaseDefense;
	Speed = BaseSpeed;

	Health = MaxHealth;

	GetCharacterMovement()->MaxAcceleration = 1536.f;
	GetCharacterMovement()->BrakingFrictionFactor = .5f;
	GetCharacterMovement()->AirControl = 2.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->JumpZVelocity = 510.f;

	this->bReplicates = true;
	bIsAlive = true;
}

void AOgnamCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamCharacter, Health);
	DOREPLIFETIME(AOgnamCharacter, BaseMaxHealth);
	DOREPLIFETIME(AOgnamCharacter, MaxHealth);
	DOREPLIFETIME(AOgnamCharacter, BaseDefense);
	DOREPLIFETIME(AOgnamCharacter, Defense);
	DOREPLIFETIME(AOgnamCharacter, BaseSpeed);
	DOREPLIFETIME(AOgnamCharacter, Speed);
	DOREPLIFETIME(AOgnamCharacter, bIsJumping);
	DOREPLIFETIME(AOgnamCharacter, bIsAlive);
}

void AOgnamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MaxHealth = BaseMaxHealth;
	Defense = BaseDefense;
	Speed = BaseSpeed;

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
}

// Called to bind functionality to input
void AOgnamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFoward", this, &AOgnamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOgnamCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AOgnamCharacter::Jump);

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

void AOgnamCharacter::MobilityPressed()
{
	if (!HasStatusEffect(EStatusEffect::Silenced))
	{
		OnMobilityPressed.Broadcast();
	}
}

void AOgnamCharacter::MobilityReleased()
{
	OnMobilityReleased.Broadcast();
}

void AOgnamCharacter::UniquePressed()
{
	if (!HasStatusEffect(EStatusEffect::Silenced))
	{
		OnUniquePressed.Broadcast();
	}
}

void AOgnamCharacter::UniqueReleased()
{
	OnUniqueReleased.Broadcast();
}

void AOgnamCharacter::UtilityPressed()
{
	if (!HasStatusEffect(EStatusEffect::Silenced))
	{
		OnUtilityPressed.Broadcast();
	}
}

void AOgnamCharacter::UtilityReleased()
{
	OnUtilityReleased.Broadcast();
}

void AOgnamCharacter::SpecialPressed()
{
	if (!HasStatusEffect(EStatusEffect::Silenced))
	{
		OnSpecialPressed.Broadcast();
	}
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
	if (!HasStatusEffect(EStatusEffect::Unarmed))
	{
		OnBasicPressed.Broadcast();
	}
}

void AOgnamCharacter::BasicReleased()
{
	if (!HasStatusEffect(EStatusEffect::Unarmed))
	{
		OnBasicReleased.Broadcast();
	}
}

void AOgnamCharacter::SubPressed()
{
	if (!HasStatusEffect(EStatusEffect::Unarmed))
	{
		OnSubPressed.Broadcast();
	}
}

void AOgnamCharacter::SubReleased()
{
	if (!HasStatusEffect(EStatusEffect::Unarmed))
	{
		OnSubReleased.Broadcast();
	}
}
 
void AOgnamCharacter::MoveForward(float Amount)
{
	if (Controller != nullptr && Amount != 0.f && !HasStatusEffect(EStatusEffect::Rooted))
	{
		InputVector += FVector::ForwardVector * Amount;
		InputAmount += FMath::Abs(Amount);
		NumInputs++;
	}
}

void AOgnamCharacter::MoveRight(float Amount)
{
	if (Controller != nullptr && Amount != 0.f && !HasStatusEffect(EStatusEffect::Rooted))
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
	//shoot ray from camera to see where it should land.
	FVector RayFrom = Camera->GetComponentLocation() + near;
	FVector RayTo = RayFrom + Camera->GetForwardVector() * far;
	FCollisionQueryParams Params(TEXT("cameraPath"), true, this);
	GetWorld()->LineTraceSingleByProfile(HitResult, RayFrom, RayTo, TEXT("BlockAll"), Params);
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

void AOgnamCharacter::ServerJump_Implementation()
{
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

void AOgnamCharacter::Jump()
{
	ACharacter::Jump();
	bIsJumping = true;
	ServerJump();
}

void AOgnamCharacter::Landed(const FHitResult& FHit)
{
	bIsJumping = false;
}

float AOgnamCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HasAuthority())
	{
		Health -= Damage;
		if (Health <= 0)
		{
			Die();
		}
	}
	return Damage;
}

void AOgnamCharacter::Die_Implementation()
{
	GetMesh()->SetCollisionProfileName(TEXT("RagDoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	bIsAlive = false;

	//For local player
	AOgnamPlayerController* PlayerController = Cast<AOgnamPlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		return;
	}
	DisableInput(PlayerController);
	PlayerController->OnPawnDeath();
}
