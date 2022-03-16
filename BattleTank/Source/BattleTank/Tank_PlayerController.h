// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATank_PlayerController : public APlayerController
{
	GENERATED_BODY()

	public: 
		ATank* GetControlledTank() const;

		virtual void BeginPlay() override;

		virtual void Tick(float Deltatime) override;

	private:
		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	
};
