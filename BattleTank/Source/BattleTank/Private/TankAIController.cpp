// Copyright - Matthew Pye 2019

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		TankAimingComponent = AimingComponent;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at begin play"))
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius  

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		if(TankAimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			TankAimingComponent->Fire(); //TODO Limit Firing rate
		}
		
	}
}

