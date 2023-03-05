// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInput/Public/EnhancedInputComponent.h>

#include "ShootComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Components
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("Shoot component"));

	//Initialize Root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionBox);

	//Add hierarchy
	MainTank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Tank"));
	MainTank->SetupAttachment(RootComponent);

	MovableTankTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Movable tank turret"));
	MovableTankTurret->SetupAttachment(MainTank);

	Cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	Cannon->SetupAttachment(MovableTankTurret);

	//Setup default values
	MovementSpeed = 140.f;
	TurnSpeed = 60.f;

	//Camera setup

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(Cannon);
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 300.f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

//Enhanced Input system boilerplate 
void ATank::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(InputMappingContext, BaseMappingPriority);
		}
	}
}

void ATank::Move(const FInputActionInstance& Instance)
{
#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::yellow, "Move");
#endif
}

void ATank::Rotate(const FInputActionInstance& Instance)
{	
#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::red, "Rotate Tank");
#endif
}

void ATank::Shoot(const FInputActionInstance& Instance)
{
#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::blue, "Shoot");
#endif
}

void ATank::RotateCamera(const FInputActionInstance& Instance)
{
#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::green, "Rotate camera");
#endif
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		BindActions(EnhancedInputComponent);
	}
}

void ATank::BindActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
	}

	if (ShootAction)
	{
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATank::Shoot);
	}

	if (RotateTankAction)
	{
		EnhancedInputComponent->BindAction(RotateTankAction, ETriggerEvent::Triggered, this, &ATank::Rotate);
	}

	if (RotateCameraAction)
	{
		EnhancedInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &ATank::RotateCamera);
	}
}
