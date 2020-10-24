// Fill out your copyright notice in the Description page of Project Settings.

#include "Shoot_Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values
AShoot_Projectile::AShoot_Projectile()

	:

	SpeedProjectile(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));

	RootComponent = Collision;
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Perticle"));

	Particle->SetupAttachment(Collision);

	

}


// Called when the game starts or when spawned
void AShoot_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShoot_Projectile::OnProjectileOverlap);

	if (GetOwner())
	{
		
		
		UBoxComponent * OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
		Collision->IgnoreComponentWhenMoving(OwnerCollision, true);
		OwnerCollision->IgnoreComponentWhenMoving(Collision, true);

		
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	}

}

void AShoot_Projectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{

	if (!OtherActor || !Cast<APawn>(OtherActor)) return;
	if (!GetOwner()) return;
	APawn *PawnOnwer = Cast<APawn>(GetOwner());
	if (!PawnOnwer) return;
	AController * Instigator = PawnOnwer->GetController();
	
	if (!PawnOnwer->GetController() && !Cast<APawn>(OtherActor)->GetController()) return;


	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigator, this, UDamageType::StaticClass());

	Destroy();

}



// Called every frame
void AShoot_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(SpeedProjectile * DeltaTime, 0.f, 0.f));

}

