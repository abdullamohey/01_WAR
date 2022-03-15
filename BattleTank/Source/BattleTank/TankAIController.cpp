// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto AIControlledTank = GetAIControlledTank();

    if(!AIControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No AI possesed Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Possesing Tank is %s"),*(AIControlledTank->GetName()));
    }
}


ATank* ATankAIController::GetAIControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


