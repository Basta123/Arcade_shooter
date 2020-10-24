// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ShootComponent.h"
#include "CoreMinimal.h"
#include "PlayerPawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class ARCADE_SHOOTER_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchPress(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void PossessedBy(AController * NewController) override;

	APlayerController * PlayerController;
	
	FVector2D MoveLimit;

	
	

	/*
	UFUNCTION()
	void ExpodePawn_Implementaion();
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
    void RecoveryPawn();
	UFUNCTION()
	void RecoveryPawn_Implementaion();
	*/


	

	
		
	
		


	float TakeDamage
	(
		float DamageAmount,
		const FDamageEvent & DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;


private:

	FVector2D TouchLocation;

	bool Touching;

	bool Touch;

	float TouchX;
	float TouchY;


	UMaterialInterface * PawnMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UBoxComponent * PawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UCameraComponent * PawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UShootComponent * ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
		float TouchMoveSensivity;

	
	
	UPROPERTY(BlueprintAssignable, Category = "Healths")
		FPawnDamagedEvent PawnDamaged;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
		void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
		void RecoveryPawn();

	void RecoveryPawn_Implementation();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UMaterialInterface * RecoveryMaterial;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem * DestroyParticle;
};

