// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class ARCADE_SHOOTER_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;
	

	UFUNCTION(BlueprintNativeEvent)
	void BonusCollected();
	virtual void BonusCollected_Implementation();

	void Tick(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		class USphereComponent * Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem * CollectParticle;
	
};
