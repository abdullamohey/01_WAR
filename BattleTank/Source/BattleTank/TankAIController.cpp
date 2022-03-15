// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();

    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Player Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank is %s"),*(PlayerTank->GetName()));
    }
}


ATank* ATankAIController::GetAIControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn= GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!PlayerPawn)
    {   
        return nullptr;
    }
    else
    {   
        return Cast<ATank>(PlayerPawn);
    }
}


