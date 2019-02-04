// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ghost_MovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API UGhost_MovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
