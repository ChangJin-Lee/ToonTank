// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public: 
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	// Tank 뿐만 아니라 Turret도 회전이 되도록 만들거기 때문에 BasePawn.h에 선언해준다.
	// protected에 선언한 이유는 하위 클래스에서만 사용 가능하도록 만들기 위함임.
	void RotateTurret(FVector LookAtTarget);
	void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// UStaticMeshComponent* ProjectileSpawnPoint;
	USceneComponent* ProjectileSpawnPoint;

private:
	UPROPERTY(EditAnywhere, Category="Emitter")
	class UParticleSystem* DeathEffectParticle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	// int32 VisibleAnywhereInt2 = 32;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	// int32 EditAnyWhereInt2 = 32;

	// 발사체를 얻기 위함
	// 클래스 타입을 나타내는 c++ 변수를 갖게 되었다
	// 타입은 AProjectile이고 블루프린트 클래스도 이걸 바탕으로 만든다
	// UClass 타입을 저장한다. UClass에는 c++와 블루프린트 사이 리플렉션을 가능하게 하는
	// 함수가 내장되어 있다.
	// 왜 TSubcalssOf 인가? -> 이거 템플릿임
	// Spawn 액터가 어떻게 동작하는지를 봐야한다.
	// SpawnActor는 UWorld 클래스에 속하는 함수이다.
	// World를 가져오면 SpawnActor를 호출할 수 있다.
	// SpawnActor<>()
	// SpawnActor는 또 다른 템플릿 함수이고 기본 하위 객체를 생성하는 것과 유사하게
	// 새로운 객체를 생성하도록 되어 있다.
	// 기본 하위 객체를 생성하는 것은 컴포넌트를 생성하기 위해 설계되었고
	// 우리는 특정 클래스를 위한 생성자에서만 사용할 수 있다.
	// SpawnActor는 게임이 실행되는 동안 호출될 수 있고 액터를 생성한다 
	// 템플릿이기 때문에 타입이 필요하다.
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	class USoundBase* DeathSound;
};
