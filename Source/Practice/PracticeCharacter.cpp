// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeCharacter.h"

// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create first person camera component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FerstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to the capsule component
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Positioning camera slightly above eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	//Enable the pawn to control camera rotation
	FPSCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APracticeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APracticeCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APracticeCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APracticeCharacter::AddControllerYawInput);
}

void APracticeCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void APracticeCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

