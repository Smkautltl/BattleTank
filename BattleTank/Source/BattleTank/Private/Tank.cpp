// Copyright - Matthew Pye 2019

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

//Creates a projectile as the position that the barrel is currently in
void ATank::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSecs;

	if (!ensure(ProjectileBlueprint))
	{
		UE_LOG(LogTemp, Error, TEXT("No Projectile Blueprint added to tank blueprint!"))
		return;
	}

	if (ensure(Barrel && isReloaded)) {

		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
															  Barrel->GetSocketLocation("Projectile"),
															  Barrel->GetSocketRotation("Projectile")
															 );
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}

	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}