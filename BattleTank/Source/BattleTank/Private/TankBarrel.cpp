// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ElevationClamped = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(ElevationClamped, 0, 0));

}
