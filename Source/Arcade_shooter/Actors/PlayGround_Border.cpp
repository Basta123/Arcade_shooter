// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayGround_Border.h"
#include "Components/BoxComponent.h"
#include "PlayerPawn.h"


// Sets default values
APlayGround_Border::APlayGround_Border()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionProfileName("OverlapAll");
}

void APlayGround_Border::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (!OtherActor) return;

	if (Cast<APlayerPawn>(OtherActor)) return;
	UE_LOG(LogTemp, Log, TEXT("OUT OF PLAYGROUND : %s"), *OtherActor->GetName());
	OtherActor->Destroy();
}
