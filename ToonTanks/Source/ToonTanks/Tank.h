// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "components")
	class USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere, Category = "components")
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float moveSpeed = 800.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 80.0f;

	void Move(float Value);
	void Turn(float Value);
};
