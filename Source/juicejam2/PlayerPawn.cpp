// Nathaniel Richards All Rights Reserved 2023

#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

