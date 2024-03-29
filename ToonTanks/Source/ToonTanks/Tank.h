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

	void Move(float Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float moveSpeed = 300.0f;
	
};
