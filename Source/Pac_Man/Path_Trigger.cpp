// Fill out your copyright notice in the Description page of Project Settings.

#include "Path_Trigger.h"
#include "Components/BoxComponent.h"
#include "Engine/GameEngine.h"

TArray<FVector> APath_Trigger::PossibleMoves;

APath_Trigger::APath_Trigger()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (PossibleMoves.Num() == 0)
	{
		PossibleMoves = { GetActorForwardVector(), GetActorRightVector(), -GetActorForwardVector(), -GetActorRightVector() }; //Clockwise: Up, Right, Down, Left
	}
}

void APath_Trigger::BeginPlay()
{
	Super::BeginPlay();
}

void APath_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Updatable = true;
}

FVector APath_Trigger::GetDirection(int MissChancePercentage)
{
	if (FMath::RandRange(0, 100) < MissChancePercentage)
	{
		return GetRandomDirectionAvailable();
	}
	else 
	{
		if(Direction != FVector(0.f, 0.f, 0.f))
			return Direction;

		else return GetRandomDirectionAvailable();
	}
}

TArray<FVector> APath_Trigger::GetDirectionsAvailable()
{
<<<<<<< HEAD
	TArray<FVector> DirectionsAvailable = {};

	if (UpperPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[0]);

	if (RightPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[1]);

	if (InferiorPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[2]);

	if (LeftPathTrigger)
		DirectionsAvailable.Add(PossibleMoves[3]);

	return DirectionsAvailable;
}

FVector APath_Trigger::GetRandomDirectionAvailable()
{
	TArray<FVector> TempDirections = GetDirectionsAvailable();
	return TempDirections[FMath::RandRange(0, TempDirections.Num() - 1)]; // Get a random direction from the static possible moves member
=======
	TArray<FVector> DirectionsAvailable();

	if(UpperPathTrigger)
		DirectionsAvailable.

	return TArray<FVector>();
>>>>>>> master
}

void APath_Trigger::UpdatePath(int InputDistance, FVector InputDirection)
{
	if (Updatable)
	{

		Distance = 10000;
		Updatable = false;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Distance: %d"), Distance);
	//UE_LOG(LogTemp, Warning, TEXT("InputDistance: %d"), InputDistance);
	//UE_LOG(LogTemp, Warning, TEXT("InputDirection: %s"), *InputDirection.ToString());
	if (InputDistance < Distance) // Avoid backward editing 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());
		Distance = InputDistance;
		Direction = InputDirection;

		++InputDistance;
		{
			//UE_LOG(LogTemp, Warning, TEXT("hola"));
			if (UpperPathTrigger)
				UpperPathTrigger->UpdatePath(InputDistance, PossibleMoves[2]);

			if (RightPathTrigger)
				RightPathTrigger->UpdatePath(InputDistance, PossibleMoves[3]);

			if (InferiorPathTrigger)
				InferiorPathTrigger->UpdatePath(InputDistance, PossibleMoves[0]);

			if (LeftPathTrigger)
				LeftPathTrigger->UpdatePath(InputDistance, PossibleMoves[1]);
		}
	}
}