// Copyright - Matthew Pye 2019

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp Throttle Value

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle: %f"), *Name, Throttle)
}
