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
		int MissChance; // Chance to not to use the correct path trigger's direction

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		FVector Direction;

	UPROPERTY(VisibleAnywhere) // It was not seen anywhere without this unreal property
		class UStaticMeshComponent* SphereVisual;

	UPROPERTY(EditAnywhere)
		FLinearColor FrightenedColor; // Color of the material when the player is hunting

private:

	class UMaterialInstanceDynamic * Materialnstance;
	class USphereComponent* SphereComponent;

	bool bCanEat;

	FVector DirectionToChange; // 'Temporal' direction used by the timer's triggered method
	FVector StartDirection;
	FVector StartPosition;

	FLinearColor StartingColor;

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

	/**
	 * Method used to solve overlapping failures with the player. Errors still exist
	 */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:

	/**
	 * Method triggered by the timer to assign the correct direction
	 */
	UFUNCTION()
		void ChangeDirection();

public:

	/**
	 * Method to affect this actor with a collectible effect types
	 */
	void Affect(ECollectibleTypeEnum EffectType);

	/**
	 * Reset this actor's effect state
	 */
	void ResetEffectsState();
};