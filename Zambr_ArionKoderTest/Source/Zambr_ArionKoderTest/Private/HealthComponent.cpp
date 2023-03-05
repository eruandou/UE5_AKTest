// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 10.f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	// ...
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                  AActor* DamageCauser)
{
	if (DamageAmount <= 0.0f)
	{
		return;
	}

	const float ActualDamage = FMath::Min(CurrentHealth, DamageAmount);
	CurrentHealth -= ActualDamage;
	UE_LOG(LogTemp, Verbose, TEXT("Damaged by %s"), *DamageCauser->GetName());
	UpdateHealth(-ActualDamage);
}

void UHealthComponent::UpdateHealth(const float DeltaHealth) const
{
	if (CurrentHealth != 0)
	{
		OnHealthChanged.Broadcast(CurrentHealth, DeltaHealth);
		return;
	}

	OnDead.Broadcast();
}
