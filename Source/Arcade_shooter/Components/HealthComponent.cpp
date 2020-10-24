// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	Health = 100;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamaged);
	
}



void UHealthComponent::OnOwnerDamaged(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * Instigator, AActor * DamageCauser)
{
	ChangeHealth(-Damage);
}



float UHealthComponent::GetHealth()
{
	return Health;
}

void UHealthComponent::ChangeHealth(float value)
{
	this->Health += value;
	if (Health <= 0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamaged);

		
		OnHealthEnded.Broadcast();

	}


}

