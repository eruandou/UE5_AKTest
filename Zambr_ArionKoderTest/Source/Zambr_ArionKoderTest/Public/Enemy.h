// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.generated.h"

class UHealthComponent;
class USphereComponent;
UCLASS()
class ZAMBR_ARIONKODERTEST_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MainMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;
	void OnBeginOverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                           const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* HealthComponent;

	void KillEntity();
public:
	virtual void Tick(float DeltaTime) override;
	// Called every frame
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }
};
