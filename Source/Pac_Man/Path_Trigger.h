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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	UPROPERTY(EditAnywhere)
>>>>>>> master
=======
	UPROPERTY(EditAnywhere)
>>>>>>> 8d5a671... Transfered Ghost's Class from Pawn to actor
	FVector Direction;

	int Distance;
	bool Updatable;

public:

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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; 

public:

	void UpdatePath(int InputDistance, FVector InputDirection);

public:

	FVector GetDirection(int MissChancePercentage);	
	TArray<FVector> GetDirectionsAvailable();
<<<<<<< HEAD
<<<<<<< HEAD
	FVector GetRandomDirectionAvailable();
=======
>>>>>>> master
=======
>>>>>>> 8d5a671... Transfered Ghost's Class from Pawn to actor
};