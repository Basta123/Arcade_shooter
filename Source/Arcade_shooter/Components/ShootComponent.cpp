// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"



// Sets default values for this component's properties
UShootComponent::UShootComponent()

	:
	ShootPeriod(0.1)

{
	
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();

	
}

void UShootComponent::Shoot()
{
	


	for (FShootInfo ShootInfo : ShootInfos)
	{
		FActorSpawnParameters SpawnParametrs;
		SpawnParametrs.Owner = GetOwner();
		SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation =
			GetOwner()->GetActorLocation() +
			GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);

			FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

		AShoot_Projectile * Projectile = GetWorld()->SpawnActor<AShoot_Projectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParametrs);
		if (Projectile)
		{
			Projectile->Damage = ShootInfo.Damage;
		}
	}



	

}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}


