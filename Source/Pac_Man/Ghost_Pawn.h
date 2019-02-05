// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ghost_Pawn.generated.h"

UCLASS()
class PAC_MAN_API AGhost_Pawn : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	int MissChance;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	FVector Direction;

	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere) // It was not seen anywhere
	UStaticMeshComponent* SphereVisual;

	//class UGhost_PawnMovementComponent*  GhostMovementComponent;

public:
	// Sets default values for this pawn's properties
	AGhost_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
