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

	class USphereComponent* SphereComponent;

	FVector Direction;

private:

	class UPac_Man_MovementComponent* PacManMovementComponent;

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

public:

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:

	virtual UPawnMovementComponent * GetMovementComponent() const override;
	FVector GetMovementDirection();
};