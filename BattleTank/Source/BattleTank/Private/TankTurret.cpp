// Copyright - Matthew Pye 2019
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	//auto RotationClamped = FMath::Clamp(RawNewRotation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}