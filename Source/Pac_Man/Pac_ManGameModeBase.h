// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Collectible.h"
#include "Pac_ManGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class PAC_MAN_API APac_ManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	FTimerHandle UnusedHandle;

public: 

	void SendEffectToGhosts(ECollectibleTypeEnum Effect, float Duration);
	void ResetGhostsEffects();


};
