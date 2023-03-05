// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HealthComponent.h"
#include "Tank.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health system"));

	//Initialize others
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body mesh"));
	SetRootComponent(MainMesh);
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetupAttachment(MainMesh);
	CollisionComponent->InitSphereRadius(51.f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDead.AddDynamic(this, &AEnemy::KillEntity);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlapHandler);
}

void AEnemy::OnBeginOverlapHandler(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (const ATank* PlayerTank = Cast<ATank>(OtherActor))
	{
		UHealthComponent* PlayerHealthComponent = PlayerTank->GetHealthComponent();
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = DamageType;
		PlayerHealthComponent->TakeDamage(Damage, DamageEvent, nullptr, this);;
	}
}

void AEnemy::KillEntity()
{
	//Leave as is to add future elements, like particles and what not
	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
