// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZAMBR_ARIONKODERTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, DeltaHealth);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category="Game|Damage")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Game|Damage")
	FOnDeadSignature OnDead;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category="Health")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
					AActor* DamageCauser);

private:
	void UpdateHealth(float DeltaHealth) const;
		
};
