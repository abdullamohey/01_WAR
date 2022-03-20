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
    //Finding Crosshair position in pixel coordinates
    int32 ViewportSizeX , ViewportSizeY;

    GetViewportSize(ViewportSizeX,ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation , ViewportSizeY*CrossHairYLocation);

    //Deproject screen position of the crosshair to a world direction
    FVector WorldDirection;
    
    if(GetLookDirection(ScreenLocation,WorldDirection))
    {
        //UE_LOG(LogTemp, Warning, TEXT("World Direction is : %s"), *WorldDirection.ToString()) ;

        // Line-trace along that LookDirection, and see what we hit (up to max range)
        GetLookVectorHitLocation(WorldDirection ,OutHitLocation);
    }


    return true;
}

bool ATank_PlayerController::GetLookDirection(FVector2D ScreenLocation , FVector& LookDirection) const
{
    FVector CameraLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X , ScreenLocation.Y , CameraLocation , LookDirection );
}

bool ATank_PlayerController::GetLookVectorHitLocation(FVector LookDirection , FVector& HitLocation) const
{
    FHitResult HitResult ;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection*LineTraceRange); 

    if(GetWorld()->LineTraceSingleByChannel(HitResult ,StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation=FVector(0);
    return false;
}

ATank* ATank_PlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}