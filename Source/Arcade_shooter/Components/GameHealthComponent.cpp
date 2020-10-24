// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"




// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	Healths = 3;

	// ...
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	
	Super::BeginPlay();

	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No PlayerPawn!!!"));
		return;
	}



	

	
}








// Called every frame
void UGameHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}



void UGameHealthComponent::ChangeHealths(int ByValue)
{

	Healths += ByValue;

	HealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}

	UE_LOG(LogTemp, Log, TEXT("Health Changed : %i"), Healths);

}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}



