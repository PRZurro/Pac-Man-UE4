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

	int Distance; // Needed to iterate through the path trigger hierarchy. It avoids modifying the direction of the one who modified this direction.
		
	bool Updatable;

public:

	static TArray<FVector> PossibleMoves; // Array with the possible directions that can make a ghost after passing through this trigger

public:
	// Adjacent path triggers
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

	/**
	 * Method that updates to the current direction of all the connected path triggers.
	 */
	void UpdatePath(int InputDistance, FVector InputDirection);

public:

	/**
	 * Return the direction of this path trigger if the random number is greater than the miss chance
	 */
	FVector GetDirection(int MissChancePercentage);	

	/**
	 * Return the directions available in this actor
	 */
	TArray<FVector> GetDirectionsAvailable();

	/**
	 * Return an available random direction
	 */
	FVector GetRandomDirectionAvailable();
};