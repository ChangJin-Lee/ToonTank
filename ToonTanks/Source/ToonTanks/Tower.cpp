// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(InFireRange())
	{
		// If in range, rotate turret toward Tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// 타이머는 BeginPlay에 설정해서 게임 시작 시 타이머가 실행되도록 할 수 있음.
	// FTimerManager 오브젝트를 반환함. 이 타입을 이용하기 때문에 FTimerManager의
	// 헤더 파일을 포함해야함.
	// SetTimer()는 몇 가지 다른 함수, 즉 오버로드를 지원함.
	// 함수를 타이머와 바인딩하고 2초마다 호출되도록 설정
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true
		);
}

void ATower::CheckFireCondition()
{
	if(InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if(Tank)
	{
		// Find the distance to the Tank
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		// Check to see if the Tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
