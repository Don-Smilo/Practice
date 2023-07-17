// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Don't remember why i need it, but i won't delete this
	// Well, it returns true
	bool IsHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateMaxHealth(float Value);

	UFUNCTION(BlueprintCallable)
	float GetPercentage();

	// Default value 100
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth = 100;
	
	// Current ammount of health
	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(BlueprintReadOnly)
	bool isAlive = true;
};
