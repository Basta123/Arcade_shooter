// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayGround_Border.generated.h"

UCLASS()
class ARCADE_SHOOTER_API APlayGround_Border : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayGround_Border();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent * Trigger;

	virtual void NotifyActorEndOverlap(AActor * OtherActor) override;
	
	
};
