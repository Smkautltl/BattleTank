// Copyright - Matthew Pye 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet)
{
	if (!TrackLeftToSet || !TrackRightToSet) { return; }

	LeftTrack = TrackLeftToSet;
	RightTrack = TrackRightToSet;
}

void UTankMovementComponent::IntentMoveForward(float Throws)
{
		LeftTrack->SetThrottle(Throws);
		RightTrack->SetThrottle(Throws);
}

void UTankMovementComponent::IntentTurnRight(float Throws)
{
	LeftTrack->SetThrottle(Throws);
	RightTrack->SetThrottle(-Throws);
}
