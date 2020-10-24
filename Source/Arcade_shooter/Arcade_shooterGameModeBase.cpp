// Fill out your copyright notice in the Description page of Project Settings.

#include "Arcade_shooterGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"




AArcade_shooterGameModeBase::AArcade_shooterGameModeBase()
{
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
	PlayerRecoverTime = 3;
	CurrentShootLevel = -1;
	IncreaseDifficultyPeriod = 4.f;

}

void AArcade_shooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AArcade_shooterGameModeBase::EndGame);
	
	APawn * Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	PlayerPawn = Cast<APlayerPawn>(Pawn);
	if (!PlayerPawn) return;

	ChangeShootLevel(true);

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[0].FShootInfos;
	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcade_shooterGameModeBase::ExplodePawn);
	
	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &AArcade_shooterGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);

	

}



void AArcade_shooterGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	HealthsComponent->ChangeHealths(-1);

	ChangeShootLevel(false);
	
	if (!isGameOver)
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcade_shooterGameModeBase::RecoverPawn, PlayerRecoverTime, false);
	}
}

void AArcade_shooterGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoveryPawn();
}






void AArcade_shooterGameModeBase::EndGame()
{

	isGameOver = true;
	EnemySpawnComponent->SetActive(false);
	GameOver.Broadcast();
	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Log, TEXT("Game Over!!!"));
}

void AArcade_shooterGameModeBase::AddPoints(int Points)
{
	GamePoint = GamePoint + Points;
}

void AArcade_shooterGameModeBase::IncreaseDifficulty()
{
	EnemySpawnComponent->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnComponent->ChangeStageTimeMultiplier *0.95, 0.1);
	UE_LOG(LogTemp, Warning, TEXT("Difficulty increased: %f"), EnemySpawnComponent->ChangeStageTimeMultiplier);
}

bool AArcade_shooterGameModeBase::ChangeShootLevel(bool Up)
{
	APlayerPawn * PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].FShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	return true;
}





