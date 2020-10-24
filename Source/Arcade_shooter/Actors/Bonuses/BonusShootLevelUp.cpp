// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade_shooterGameModeBase.h"



void ABonusShootLevelUp::BonusCollected_Implementation()
{

	AArcade_shooterGameModeBase * GameMode = Cast<AArcade_shooterGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	GameMode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();



}