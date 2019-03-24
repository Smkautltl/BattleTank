// Copyright - Matthew Pye 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet)
{
	if (!TrackLeftToSet || !TrackRightToSet) { return; }

	LeftTrack = TrackLeftToSet;
	RightTrack = TrackRightToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntentMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
	IntentTurnRight(-FVector::CrossProduct(TankForward, AIForwardIntention).Z);
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
