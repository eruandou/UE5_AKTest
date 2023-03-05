// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UBoxComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionInstance;
class UShootComponent;
UCLASS()
class ZAMBR_ARIONKODERTEST_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* RotateTankAction;
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* RotateCameraAction;
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Mapping")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category="Input|Mapping")
	int32 BaseMappingPriority;

	UPROPERTY(EditAnywhere, meta=(ToolTip = "Main movement speed", ClampMin= 1.f),
		Category= "Data|Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, meta=(ToolTip = "Turn speed", ClampMin= 0.1f),
		Category= "Data|Movement")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, meta=(ToolTip ="Camera component"), Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, meta=(ToolTip ="Camera Spring component"), Category="Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainTank;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MovableTankTurret;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cannon;

	UPROPERTY(EditDefaultsOnly)
	UShootComponent* ShootComponent;
	void Move(const FInputActionInstance& Instance);
	void Rotate(const FInputActionInstance& Instance);
	UFUNCTION(BlueprintCallable, meta=(ToolTip = "Shoot in the direction of the camera"))
	void Shoot(const FInputActionInstance& Instance);
	void RotateCamera(const FInputActionInstance& Instance);

	virtual void PawnClientRestart() override;
	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
