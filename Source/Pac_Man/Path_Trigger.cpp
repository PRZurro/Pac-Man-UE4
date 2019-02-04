// Fill out your copyright notice in the Description page of Project Settings.

#include "Path_Trigger.h"


void APath_Trigger::UpdatePath(int Distance, FVector Direction)
{
	
}

FVector APath_Trigger::GetDirection(int MissChancePercentage)
{
	if (FMath::RandRange(0, 100) < MissChancePercentage)
	{
		//Get Path
	}
	else 
	{
		// Random direction
	}

	return BestDirection;
}

APath_Trigger * APath_Trigger::GetUpperPathTrigger()
{
	return UpperPathTrigger;
}

APath_Trigger * APath_Trigger::GetInferiorPathTrigger()
{
	return InferiorPathTrigger;
}

APath_Trigger * APath_Trigger::GetRightPathTrigger()
{
	return RightPathTrigger;
}

APath_Trigger * APath_Trigger::GetLeftPathTrigger()
{
	return LeftPathTrigger;
}
