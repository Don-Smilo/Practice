// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PracticeCharacter.generated.h"

UCLASS()
class PRACTICE_API APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APracticeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input forward/backward
	UFUNCTION()
	void MoveForward(float value);
	
	// Handles input left/right
	UFUNCTION()
	void MoveRight(float value);

public:
	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;


};
