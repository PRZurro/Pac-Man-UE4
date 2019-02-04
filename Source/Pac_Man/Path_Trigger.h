// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Path_Trigger.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API APath_Trigger : public ATriggerBox
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class APath_Trigger	*	UpperPathTrigger;
	UPROPERTY(EditAnywhere)
	class APath_Trigger *	InferiorPathTrigger;
	UPROPERTY(EditAnywhere)
	class APath_Trigger *	RightPathTrigger;
	UPROPERTY(EditAnywhere)
	class APath_Trigger *	LeftPathTrigger;

	
public:

	FVector GetLocation();
	
	APath_Trigger * GetUpperPathTrigger();
	APath_Trigger * GetInferiorPathTrigger();
	APath_Trigger * GetRightPathTrigger();
	APath_Trigger * GetLeftPathTrigger();
};
