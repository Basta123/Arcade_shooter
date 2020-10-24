// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShield.h"
#include "PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
APawnShield::APawnShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShieldTime = 5;
}

void APawnShield::ActivateShield(APlayerPawn * PlayerPawn)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}
	ShieldForPawn = PlayerPawn;
	PlayerPawn->bCanBeDamaged = false;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	AttachToActor(PlayerPawn, AttachRules);
	
	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield::DeactivateShield, ShieldTime, false);

}

void APawnShield::DeactivateShield()
{
	if (!ShieldForPawn) return;
	ShieldForPawn->bCanBeDamaged = true;
	Destroy();
}


