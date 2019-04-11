// Copyright - Matthew Pye 2019

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) { return; }

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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		if(TankAimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			TankAimingComponent->Fire(); 
		}
		
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if(!PossessedTank) {return;}

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}
void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetClosestTank(ATank* Tank)
{
	ClosestTank = Tank;
}