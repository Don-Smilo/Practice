// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set isAlive true
	isAlive = true;

	// Set current health equal to max
	Health = MaxHealth;
	
}


bool UHealthComponent::IsHealthComponent()
{
	return true;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(float Value)
{
	Health -= Value;
	if (Health <= 0)
	{
		isAlive = false;
	}
}

void UHealthComponent::UpdateMaxHealth(float Value)
{
	// Diffrernce between previous ammount and new
	float Diff = Value - MaxHealth;

	MaxHealth = Value;
	Health += Diff;
	if (Health < 0)
	{
		isAlive = false;
	}

}

float UHealthComponent::GetPecentage()
{
	return Health / MaxHealth;
}

