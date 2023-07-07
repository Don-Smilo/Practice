// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSProjectile.h"
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

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Moving
	// Handles input forward/backward
	UFUNCTION()
	void MoveForward(float value);
	
	// Handles input left/right
	UFUNCTION()
	void MoveRight(float value);
#pragma endregion

#pragma region Firing
	// Handles firing
	UFUNCTION()
	void Fire();

	// Gun muzzle offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
#pragma endregion

#pragma region Camera
	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;
#pragma endregion

	// First person mesh (arms), visible only to player
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

};
