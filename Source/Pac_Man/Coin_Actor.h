// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin_Actor.generated.h"

UCLASS()
class PAC_MAN_API ACoin_Actor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SphereVisual;

public:	
	// Sets default values for this actor's properties
	ACoin_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
