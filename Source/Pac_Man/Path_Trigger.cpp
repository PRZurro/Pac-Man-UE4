// Fill out your copyright notice in the Description page of Project Settings.

#include "Path_Trigger.h"

APath_Trigger::APath_Trigger()
{
	if (PossibleMoves.Num() != 0)
	{
		PossibleMoves = { GetActorForwardVector(), GetActorRightVector(), -GetActorForwardVector(), -GetActorRightVector() }; //Clockwise: Up, Right, Down, Left
	}
}

void APath_Trigger::Tick(float DeltaTime)
{
	Updatable = true;
}

FVector APath_Trigger::GetDirection(int MissChancePercentage)
{
	if (FMath::RandRange(0, 100) < MissChancePercentage)
	{
		return PossibleMoves[FMath::RandRange(0, 3)]; // Get a random direction from the static possible moves member
	}
	else 
	{
		return Direction;
	}
}

void APath_Trigger::UpdatePath(int InputDistance, FVector InputDirection)
{
	if (Updatable)
	{
		Distance = 10000;
		Updatable = false;
	}

	if (Distance < InputDistance) // Avoid backward editing 
	{
		Distance = InputDistance;
		Direction = InputDirection;

		++InputDistance;
		{
			if (UpperPathTrigger)
				UpperPathTrigger->UpdatePath(InputDistance, PossibleMoves[0]);

			if (RightPathTrigger)
				RightPathTrigger->UpdatePath(InputDistance, PossibleMoves[1]);

			if (InferiorPathTrigger)
				InferiorPathTrigger->UpdatePath(InputDistance, PossibleMoves[2]);

			if (LeftPathTrigger)
				LeftPathTrigger->UpdatePath(InputDistance, PossibleMoves[3]);
		}
	}
}