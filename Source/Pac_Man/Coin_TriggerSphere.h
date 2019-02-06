// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "Coin_TriggerSphere.generated.h"

/**
 * 
 */
UCLASS()
class PAC_MAN_API ACoin_TriggerSphere : public ATriggerSphere
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SphereVisual;

public:

	ACoin_TriggerSphere();
	
};
