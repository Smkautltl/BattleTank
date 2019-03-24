// Copyright - Matthew Pye 2019

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp Throttle Value

		auto ForceApplied = GetForwardVector() * Throttle * MaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}