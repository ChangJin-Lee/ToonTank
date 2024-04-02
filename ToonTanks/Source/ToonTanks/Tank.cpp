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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// "AController*의 타입 APlayerController*에 대입할 수 없습니다"
	// AController가 상위 타입의 오브젝트이다
	// 상위 타입의 오브젝트를 가져와 하위 타입 포인터에 저장할 수 없다.
	// Cast을 해주어야한다!
	// AController 포인터 타입의 값이 있을 경우, Cast라는 함수를 사용해
	// 포인터 타입을 APlayerController로 바꿀 수 있다.
	// 오브젝트 자체가 캐스팅하려는 타입에 해당한다면, 캐스팅은 한 포인터 타입을
	// 다른 포인터 타입으로 바꿔준다
	// 유효하지 않은 타입으로 캐스팅하려고 할 경우, 예를들어 APlayerController 오브젝트를
	// 가리키는 AController 타입을 ACharacter에 캐스팅하려고 한다면 Cast 함수가 Null을 반환하고
	// 캐스팅에 실패한다.
	// Cast<타입>(포인터변수) 로 쓴다.
	PlayerControllerRef = Cast<APlayerController>(GetController()); 
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