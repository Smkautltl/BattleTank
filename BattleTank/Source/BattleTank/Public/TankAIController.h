// Copyright - Matthew Pye 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	//How close the AI tank can get to the player
	UPROPERTY(EditAnywhere, Category = "Firing")
		float AcceptanceRadius = 80000;

private:

	

};
