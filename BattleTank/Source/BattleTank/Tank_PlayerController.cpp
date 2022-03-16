// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank_PlayerController.h"


void ATank_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Tank Controlled")) ;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controlling posses : %s"), *(ControlledTank->GetName())) ;
    }

}

void ATank_PlayerController::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
    AimTowardsCrosshair();
}

void ATank_PlayerController::AimTowardsCrosshair()
{
    FVector OutHitLocation; 

    if(!GetControlledTank())
    {
        return;
    }
    
    if(GetSightRayHitLocation(OutHitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit Location : %s"), *OutHitLocation.ToString()) ;
    }

}

bool ATank_PlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
    OutHitLocation = FVector(1.0);
    return true;
}

ATank* ATank_PlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}