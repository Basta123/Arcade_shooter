// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));

	RootComponent = Collision;
	
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	/*Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);*/
	Collision->SetSphereRadius(100);
	

}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABonus::NotifyActorBeginOverlap(AActor * OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("BonusOverlap!!!"));
	if (!OtherActor) return;

	if (!Cast<APlayerPawn>(OtherActor)) return;

	BonusCollected();

	UE_LOG(LogTemp, Log, TEXT("Bonus Char Overlap!!!"));
}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
	Destroy();
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Xoffset = -400.f * DeltaTime;

	AddActorWorldOffset(FVector(Xoffset, 0.0f, 0.0f));

}
