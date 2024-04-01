// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springarm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springarm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 문자열 리터럴(축 이름), 함수를 바인드하는 대상 객체의 포인터(게임 안에 있는 폰 탱크), 함수의 주소 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
	// UE_LOG(LogTemp, Display, TEXT("Value : %f"), Value);
	// FVector DeltaLocation;
	// DeltaLocation = FVector(0.0f,0.0f,0.0f);
	
	FVector DeltaLocation = FVector::ZeroVector;
	double deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	// 수도코드
	// X = Value * DeltaTime * Speed
	// DeltaLocation.X = Value;
	DeltaLocation.X = Value * deltaTime * moveSpeed;
	// 2번째 매개변수는 bSweep이고 물체가 부딪치게끔 해준다
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	// Yaw = Value * DeltaTime * TurnRate
	double deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * deltaTime * turnRate;
	AddActorLocalRotation(DeltaRotation, true);
}