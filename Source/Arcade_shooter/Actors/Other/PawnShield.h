// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnShield.generated.h"

class APlayerPawn;

UCLASS()
class ARCADE_SHOOTER_API APawnShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnShield();

protected:
	FTimerHandle ShieldTimer;
	class APlayerPawn * ShieldForPawn; 



public:
	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(APlayerPawn * PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shield")
		float ShieldTime;
	
};
