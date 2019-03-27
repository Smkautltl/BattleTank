// Copyright - Matthew Pye 2019

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

//Calculates a possible projectile velocity
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculates the launch velocity
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
																		this,
																		OutLaunchVelocity,
																		StartLocation,
																		HitLocation,
																		LaunchSpeed,
																		false,
																		0,
																		0,
																		ESuggestProjVelocityTraceOption::DoNotTrace
																	  );

	if  (HaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Error, TEXT("No barrel refrence set unable to move barrel"))
		return;
	}
	

	//Convert location that the barrel need to move into a rotator
	//Use rotator to move the barrel to the correct location
	//Also, move the head where the barrel is attached to so that it can get into the correct position

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

}
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret))
	{
		UE_LOG(LogTemp, Error, TEXT("No turret refrence set unable to move turret"))
		return;
	}

	auto TurretRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - TurretRotation;

	Turret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSecs;

	if (!ensure(ProjectileBlueprint))
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile Blueprint added to tank blueprint!"))
			return;
	}

	if (ensure(Barrel)) {
		if (isReloaded)
		{



			auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
				Barrel->GetSocketLocation("Projectile"),
				Barrel->GetSocketRotation("Projectile")
				);
			projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
	}

}