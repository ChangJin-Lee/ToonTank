// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	// 콜백함수가 작동하려면 UFUNCTION이어야만 함
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnyWhere, Category="Combat")
	USoundBase* LaunchSound;
	
	UPROPERTY(EditAnyWhere, Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ProjectileInitialSpeed = 1800.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float ProjectileMaxSpeed = 2000.f;
};
