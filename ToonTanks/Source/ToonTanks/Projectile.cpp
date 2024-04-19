// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/MeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

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
	// 찍어보기
	// UE_LOG(LogTemp, Warning, TEXT("HitComp Name is %s"), *HitComp->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("OtherActor Name is %s"), *OtherActor->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("OtherComp Name is %s"), *OtherComp->GetName());

	auto MyOwner = GetOwner();
	if(MyOwner==nullptr)
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	// UDamageType을 블루프린트 기반으로 만들거나 별도 데이터를 설정하는게 아니기 때문에
	// TSubclassOf 변수는 필요 없다.

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		//SpawnEmitterAtLocation 사용전에 HitParticles 파티클 시스템이 존재하는지 확인해야한다.
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	
	Destroy();
}