// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController)
    {
        EndGame(false);
    }

    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead()) return;
    }
    EndGame(true);

}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    //True if player controller and bIsPlayerWinner
    //True if not player controller and not bIsPlayerWinner
    //False if player controller and not bIsPlayerWinner
    //False if not player controller and bIsplayerWinner

    for(AController* Controller : TActorRange<AController>(GetWorld()) )
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}