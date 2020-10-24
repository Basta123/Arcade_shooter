// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"





// Sets default values
APlayerPawn::APlayerPawn()

	:
	TouchMoveSensivity(1.f),
	MoveLimit(FVector2D(500.f, 600.f))
	
	

{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));

	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);


	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);


	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

}

void APlayerPawn::PossessedBy(AController * NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

void APlayerPawn::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);
	ShootComponent->StopShooting();
	PawnMesh->SetMaterial(0, RecoveryMaterial);
	
	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	for (UActorComponent * Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Deactivate();
	}
	    
}



void APlayerPawn::RecoveryPawn_Implementation()
{
	SetActorEnableCollision(true);

	ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);
	
	for (UActorComponent * Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Activate(true);
	}


}


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	PawnMaterial = PawnMesh->GetMaterial(0);
	
	
}




float APlayerPawn::TakeDamage(float DamageAmount, const FDamageEvent  & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{

	if (!bCanBeDamaged) return 0.f;
	
	
	
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	PawnDamaged.Broadcast();

	return DamageAmount;

}



void APlayerPawn::TouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location);
	Touching = false;
}

void APlayerPawn::TouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{

	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	
	TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);

}





// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
	
	
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::TouchMove);

	//InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::TouchPress);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::TouchPress);



	

}







