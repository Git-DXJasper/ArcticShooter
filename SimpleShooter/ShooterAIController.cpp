// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }

}

void AShooterAIController::Tick(float DeltaSeconds)
{  
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    /*Version One*/
    // if(LineOfSightTo(PlayerPawn)){
    //     //the order of focus and move doesn't matter
    //     SetFocus(PlayerPawn);
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    // }else{
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }


    /*Version Two*/
    // if(LineOfSightTo(PlayerPawn))
    // {
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    // }
    // else
    // {
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    // }
}

bool AShooterAIController::IsDead() const
{   
    AMyCharacter* ControllerCharacter = Cast<AMyCharacter>(GetPawn());
    if(ControllerCharacter)
    {
        return ControllerCharacter->IsDead();
    }

    return true;
}