// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Ghost_PawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API UGhost_PawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
