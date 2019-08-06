// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"

// Sets default values
AOgnamCharacter::AOgnamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetOffset = FVector(0, 0, 90);
	SpringArm->SetRelativeRotation(FRotator(-30, 0, 0));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/Animation/OgnamCharacterAnimBlueprint.OgnamCharacterAnimBlueprint'"));
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GeneratedClass);
}

// Called when the game starts or when spawned
void AOgnamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOgnamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOgnamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFoward", this, &AOgnamCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOgnamCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
}

void AOgnamCharacter::MoveFoward(float Amount)
{
	if (Controller != nullptr && Amount != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Amount);
	}
}

void AOgnamCharacter::MoveRight(float Amount)
{
	if (Controller != nullptr && Amount != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Amount);
	}
}
