// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade_shooterGameModeBase.h"


void ABonusPoints::BonusCollected_Implementation()
{

	AArcade_shooterGameModeBase * GameMode = Cast<AArcade_shooterGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->AddPoints(Points);
	}

	Super::BonusCollected_Implementation();



}

