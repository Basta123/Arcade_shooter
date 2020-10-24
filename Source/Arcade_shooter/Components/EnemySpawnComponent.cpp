// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"




// Called when the game starts
void UEnemySpawnComponent::BeginPlay()
	
{
	Super::BeginPlay();

	Random.GenerateNewSeed();
	
	StartSpawnStage();
	
}


void UEnemySpawnComponent::StartSpawnStage()
{

	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];

	EnemiesSpawned = 0;
	SpawnEnemy();
	
	float ChangeStageTime = Random.RandRange(StageMinDelay, StageMaxDelay) * ChangeStageTimeMultiplier;
	GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnComponent::StartSpawnStage, ChangeStageTime, true);
}

void UEnemySpawnComponent::SpawnEnemy()
{
	
	FActorSpawnParameters SpawnParametrs;

	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParametrs);

	EnemiesSpawned++;
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnComponent::SpawnEnemy, SpawnStage.SpawnDelay, false);
	}


	

}

void UEnemySpawnComponent::Deactivate()
{

	Super::Deactivate();
	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);

}



