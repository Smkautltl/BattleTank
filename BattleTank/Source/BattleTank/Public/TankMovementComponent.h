// Copyright - Matthew Pye 2019
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 *  Responsible for driving the tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntentMoveForward(float Throws);
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntentTurnRight(float Throws);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrack* TrackLeftToSet, UTankTrack* TrackRightToSet);

private:
	
	UTankTrack* LeftTrack = nullptr;	
	UTankTrack* RightTrack = nullptr;

};