// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

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
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s Aiming solution found"), *TankName)
		MoveBarrelTowards(AimDirection);
	}	
}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Convert location that the barrel need to move into a rotator
	//Use rotator to move the barrel to the correct location
	//Also, move the head where the barrel is attached to so that it can get into the correct position

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotaion: %s"), *AimAsRotation.ToString())

	Barrel->Elevate(DeltaRotation.Pitch);

}