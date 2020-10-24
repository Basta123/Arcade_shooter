// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Shoot_Projectile.generated.h"


class UParticleSystemComponent;

UCLASS()
class ARCADE_SHOOTER_API AShoot_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShoot_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	USphereComponent * Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UParticleSystemComponent * Particle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float SpeedProjectile;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		float Damage;
	
};
