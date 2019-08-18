// Fill out your copyright notice in the Description page of Project Settings.


#include "BallDude.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimBlueprint.h"

ABallDude::ABallDude()
{
	//Default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/Animation/BallDude.BallDude'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//Animations for the mesh
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBP(TEXT("AnimBlueprint'/Game/Animation/OgnamCharacterAnimBlueprint.OgnamCharacterAnimBlueprint'"));
	GetMesh()->SetAnimInstanceClass(AnimBP.Object->GeneratedClass);


}
