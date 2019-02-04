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

private:

	FVector Direction;
	int Distance;
	bool Updatable;

	static TArray<FVector> PossibleMoves;

public:

	UPROPERTY(EditAnywhere)
	class APath_Trigger	*		UpperPathTrigger;

	UPROPERTY(EditAnywhere)
	class APath_Trigger *		RightPathTrigger;

	UPROPERTY(EditAnywhere)
	class APath_Trigger *		InferiorPathTrigger;
	
	UPROPERTY(EditAnywhere)
	class APath_Trigger *		LeftPathTrigger;

public:

	APath_Trigger();

public:

	virtual void Tick(float DeltaTime)override;

public:

	void UpdatePath(int InputDistance, FVector InputDirection);
	FVector GetDirection(int MissChancePercentage);	
};