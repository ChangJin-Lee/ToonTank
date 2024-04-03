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

	// 어디서든 보임
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	// int32 VisibleAnywhereInt = 32;
	//
	// // 어디서든 보이고 편집도 가능
	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// int32 EditAnywhereInt = 32;
	//
	// // 인스턴스에서만 보이고 디폴트 블루프린트에서 안보임
	// UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	// int32 VisibleInstanceOnlyInt = 32;
	//
	// // 디폴트 블루프린트에서만 보임
	// UPROPERTY(VisibleDefaultsOnly)
	// int32 VisibleDefulatsOnlyInt = 5;
	//
	// // 인스턴스에서만 보임
	// UPROPERTY(VisibleInstanceOnly)
	// int32 RunSpeed = 10;
	//
	// UPROPERTY(EditDefaultsOnly)
	// int32 EditDefaultsOnlyInt = 9;
	//
	// UPROPERTY(EDitInstanceOnly)
	// int32 EditInstanceOnlyInt = 14;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// int32 EditAnywhere = 2323;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// UStaticMeshComponent* ProjectileSpawnPoint;
	USceneComponent* ProjectileSpawnPoint;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	// int32 VisibleAnywhereInt2 = 32;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Super Duper Variables", meta = (AllowPrivateAccess = "true"))
	// int32 EditAnyWhereInt2 = 32;
};
