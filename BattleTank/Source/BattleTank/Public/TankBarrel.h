// Copyright - Matthew Pye 2019
#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Tank Barrel is use to get the end of the barrel in the correct position
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSec = 10;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevation = 40;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevation = 0;
};
