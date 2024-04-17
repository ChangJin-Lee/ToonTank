// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual/Sound Effect
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			55.f));
}

void ABasePawn::Fire()
{
	// ProjectileSpawnPoint로 발사 위치를 알고 있으니까 GetComponentLocation로 해당 위치를 가져온다.
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	// ProjectileSpawnPoint로 발사 위치를 알고 있으니까 GetComponentLocation로 해당 회전을 가져온다.
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	// AProjectile로 Location, Rotation을 넘긴다.
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

	// 위치를 보기 위함.
	// DrawDebugSphere(
	// 	GetWorld(),
	// 	Location,
	// 	24.f,
	// 	24,
	// 	FColor::Red,
	// 	false,
	// 	3.0f
	// 	);
}