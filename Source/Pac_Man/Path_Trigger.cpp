// Fill out your copyright notice in the Description page of Project Settings.

#include "Path_Trigger.h"

FVector APath_Trigger::GetLocation()
{
	return GetActorLocation();
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
