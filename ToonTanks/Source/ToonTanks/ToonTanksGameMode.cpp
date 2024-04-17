// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		// if(Tank->GetTankPlayerController())
		// {
		// 	Tank->DisableInput(Tank->GetTankPlayerController());
		// 	Tank->GetTankPlayerController()->bShowMouseCursor = false;
		// }
		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTower();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();
	
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
			);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
			);
	}
}

int32 AToonTanksGameMode::GetTargetTower()
{
	TArray<AActor*> TActors;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), TSubclassOf<ATower>(), TActors);
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TActors);
	UE_LOG(LogTemp, Display, TEXT("%d"), TActors.Num());
	return TActors.Num();
}