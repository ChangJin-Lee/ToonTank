// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/MeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = ProjectileInitialSpeed;
	ProjectileMovement->MaxSpeed = ProjectileMaxSpeed;
	// RootComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* owner = GetOwner();
	
	// UE_LOG(LogTemp, Warning, TEXT("My Name is %s"), *owner->GetName());
	UE_LOG(LogTemp, Warning, TEXT("HitComp Name is %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherActor Name is %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp Name is %s"), *OtherComp->GetName());

	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
}