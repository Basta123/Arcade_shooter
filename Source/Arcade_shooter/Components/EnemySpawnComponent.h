// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade_shooter/Actors/Pawns/EnemyPawn.h"
#include "EnemySpawnComponent.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{

	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		float SpawnDelay;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_SHOOTER_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartSpawnStage();

	void SpawnEnemy();
	
	FEnemySpawnInfo SpawnStage;
	int EnemiesSpawned;


	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;

	FRandomStream Random;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		TArray<FEnemySpawnInfo> SpawnStages;


	virtual void Deactivate() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float ChangeStageTimeMultiplier;


	
};
