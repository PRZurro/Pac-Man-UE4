// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Ghost_NavMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API UGhost_NavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	virtual void RequestPathMove(const FVector & MoveInput)override;
	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)override;
};
