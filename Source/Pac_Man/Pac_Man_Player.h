// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pac_Man_Player.generated.h"

UCLASS()
class PAC_MAN_API APac_Man_Player : public APawn
{
	GENERATED_BODY()

private:

	//class AGhost;
	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(VisibleAnywhere) // It was not seen anywhere
		UStaticMeshComponent* SphereVisual;

	UPROPERTY(EditAnywhere)
		float HunterPowerUpAffectionDuration; 

	UPROPERTY(EditAnywhere)
		float CornerPowerUpAffectionDuration;

	UPROPERTY(EditAnywhere)
		FLinearColor HunterColor; // Color of the hunter's power up 

	UPROPERTY(EditAnywhere)
		FLinearColor InvencibleColor; // Color of the corner's power up

private:

	class USphereComponent* SphereComponent; // Sphere collider

	class UPac_Man_MovementComponent* MovementComponent; // Component that let's this player to move

	class UMaterialInstanceDynamic * Materialnstance; // Material Instance of this pawn

	FVector Direction; //Current direction of this pawn
	FLinearColor StartingColor; 

	bool bIsHunting; 

	FTimerHandle UnusedHandle; // Unused FTimerHandle

protected:

	UPROPERTY(BlueprintReadOnly)
		int Score;

public:
	// Sets default values for this pawn's properties
	APac_Man_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/**
	 * Method trigger by input set in project settings (Axis). Move the pawn in X axis
	 */
	void MoveForward(float AxisValue);
	/**
	 * Method trigger by input set in project settings (Axis). Move the pawn in Y axis.
	 */
	void MoveRight(float AxisValue);

private:
	/**
	 * Event triggered when this pawn is starting to overlap another actor 
	 */
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Event triggered when this pawn is ending of overlap another actor
	 */
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	 * Reset members and variables from all effects
	 */
	UFUNCTION()
		void ResetState();

public:

	/**
	 * Adds the input value to the score of this pawn. 
	 */
	void AddScore(int ScoreToAdd);

public:

	/**
	 * Member that return the hunting state of this pawn. Hunting is the state in which the player can eat ghosts. 
	 */
	bool IsHunting();

	/**
	 * Return the movement direction of this pawn. 
	 */
	FVector GetMovementDirection();

	/**
	 * Necessary member to bind the Movement Component with the engine. 
	 */
	virtual UPawnMovementComponent* GetMovementComponent() const override;
};