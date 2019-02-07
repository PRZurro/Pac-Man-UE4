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

private:

	class USphereComponent* SphereComponent;

	class UPac_Man_MovementComponent* MovementComponent;

	FVector Direction;

	bool bIsHunting; 

	FTimerHandle UnusedHandle;

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

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void HuntFalse();

public:

	void AddScore(int ScoreToAdd);

public:

	bool IsHunting();

	FVector GetMovementDirection();

	virtual UPawnMovementComponent* GetMovementComponent() const override;
};