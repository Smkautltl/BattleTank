// Copyright - Matthew Pye 2019
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSecs = 3;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> ProjectileBlueprint;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);	
};
