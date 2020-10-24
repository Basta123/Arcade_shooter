// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Arcade_shooterGameModeBase.h"
#include "Engine/World.h"



// Sets default values
AEnemyPawn::AEnemyPawn()
	
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	PawnCollision->SetCollisionProfileName("Pawn");
	
	RootComponent = PawnCollision;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);

	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);



}





void AEnemyPawn::OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
	if (AppliedDamage > 0.f) DestroyPawn();
	
}


void AEnemyPawn::KillPawn()
{
	
	AArcade_shooterGameModeBase * GameMode = Cast<AArcade_shooterGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(DestroyPoints);
	SpawnBonuses();


	DestroyPawn();
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	Destroy();
}

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	

	for (auto Bonus : PossibleBonuses)
	{
		float RandChance = Random.RandRange(1.f, 100.f);
		if (RandChance < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
		}
	}
}



// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float Xoffset = -200.f * DeltaTime;
//   AddActorWorldOffset(FVector(Xoffset, 0.0f, 0.0f));

}




