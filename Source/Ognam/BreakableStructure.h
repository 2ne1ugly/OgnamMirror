// Fill out your copyright notice in the Description page of Project Settings.


// Breakable walls 
// Health, MaxHealth, Alive
// Takes Damage
// Sets visibility and collision

#pragma once

#include "CoreMinimal.h"
#include "OgnamEntity.h"
#include "Interfaces/Killable.h"
#include "BreakableStructure.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ABreakableStructure : public AOgnamEntity, public IKillable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
public:
	// Sets default values for this actor's properties
	ABreakableStructure();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BluePrintCallable)
	int32 GetHealth() const;

	UFUNCTION(BluePrintCallable)
	int32 GetMaxHealth() const;

	UFUNCTION(NetMulticast, Reliable)
	void NetDie();
	virtual void NetDie_Implementation();

	virtual bool CanBeKilledBy(class AOgnamPlayerState* DamageInstigator, EDamageMethod DamageMethod);

	virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere, Replicated)
	int32 MaxHealth;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 Health;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DefaultMaterial;
};
