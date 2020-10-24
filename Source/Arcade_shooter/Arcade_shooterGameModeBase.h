// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnComponent.h"
#include "Components/GameHealthComponent.h"
#include "PlayerPawn.h"
#include "Components/ShootComponent.h"
#include "Arcade_shooterGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);



USTRUCT(BlueprintType)
struct FShootInfoLevels
{

	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TArray<FShootInfo> FShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float ShootPeriod;

};



UCLASS()
class ARCADE_SHOOTER_API AArcade_shooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AArcade_shooterGameModeBase();
	
protected:

	virtual void BeginPlay() override;
	
		FTimerHandle RecoverTimer;
		FTimerHandle IncreaseDifficultyTimer;

		UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void ExplodePawn();
		void ExplodePawn_Implementation();

		UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void RecoverPawn();
		void RecoverPawn_Implementation();

		bool isGameOver;

public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
		UEnemySpawnComponent * EnemySpawnComponent;

		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
			UGameHealthComponent *HealthsComponent;
	
		UFUNCTION(BlueprintCallable, Category = "Game")
			void EndGame();

		UFUNCTION(BlueprintCallable, Category = "Game")
			void AddPoints(int Points);

		UFUNCTION(BlueprintCallable, Category = "Game")
			void IncreaseDifficulty();

		UFUNCTION(BlueprintCallable, Category = "Game")
			bool ChangeShootLevel(bool Up);

		UPROPERTY(BlueprintAssignable, Category = "Game")
			FGameOverEvent GameOver;

		UPROPERTY(EditAnywhere, Category = "Game")
			float PlayerRecoverTime;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
			float IncreaseDifficultyPeriod;

		UPROPERTY(BlueprintReadOnly, Category = "Game")
			APlayerPawn *PlayerPawn;

		UPROPERTY(BlueprintReadOnly, Category = "Game")
			int GamePoint;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
			TArray<FShootInfoLevels> ShootInfoLevels;

		UPROPERTY(BlueprintReadOnly, Category = "Game")
			int CurrentShootLevel;

		
};
