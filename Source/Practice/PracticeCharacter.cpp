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

	// Create first person mesh component
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only player sees this mesh
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach this mesh to FPS camera
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable enviromental shadows
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// Switch off visibility of third person mesh
	GetMesh()->SetOwnerNoSee(true);

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APracticeCharacter::Fire);
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

void APracticeCharacter::Fire()
{
	// Attempt to fire a projectile
	if (ProjectileClass)
	{
		// Get the camera location
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset 
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		//Transform MuzzleOffset to world space
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetInstigator();

			// S[awn the projectile at the muzzle
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

