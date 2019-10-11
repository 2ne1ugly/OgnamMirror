// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundLeap.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBloodhoundLeap::UBloodhoundLeap()
{

}

bool UBloodhoundLeap::ShouldEnd()
{
	return bHit;
}

void UBloodhoundLeap::BeginModifier()
{
	FVector Direction = Target->GetActorForwardVector() + FVector::UpVector;
	Direction = Direction.GetSafeNormal();
	Target->GetCharacterMovement()->AddImpulse(Direction * 120000.f);
	Target->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &UBloodhoundLeap::OnHit);
}

void UBloodhoundLeap::TickModifier(float DeltaTime)
{
	Target->AirControl = 0.f;
	Target->Gravity += Target->BaseGravity;
}

void UBloodhoundLeap::EndModifier()
{
	Target->GetCapsuleComponent()->OnComponentHit.RemoveDynamic(this, &UBloodhoundLeap::OnHit);
}

void UBloodhoundLeap::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bHit = true;
}
