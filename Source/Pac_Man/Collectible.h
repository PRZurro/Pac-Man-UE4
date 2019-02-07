// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECollectibleTypeEnum : uint8
{
	CTE_Coin			UMETA(DisplayName = "Coin"),
	CTE_CornerPowerUp 	UMETA(DisplayName = "Corner Power Up"),
	CTE_HunterPowerUp	UMETA(DisplayName = "Hunter Power Up"),
};

UCLASS()
class PAC_MAN_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent * SphereVisual;

	UPROPERTY(EditAnywhere)
		ECollectibleTypeEnum Type;

public:	
	// Sets default values for this actor's properties
	ACollectible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
