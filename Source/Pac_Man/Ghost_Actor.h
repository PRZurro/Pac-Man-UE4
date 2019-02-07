// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.h"
#include "Ghost_Actor.generated.h"


UCLASS()
class PAC_MAN_API AGhost_Actor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		int MissChance;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		FVector Direction;

	FVector DirectionToChange;

	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere) // It was not seen anywhere
		class UStaticMeshComponent* SphereVisual;

	FTimerHandle UnusedHandle;

public:
	// Sets default values for this pawn's properties
	AGhost_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:

	UFUNCTION()
		void ChangeDirection();
		
	void Affect(ECollectibleTypeEnum Type);
};