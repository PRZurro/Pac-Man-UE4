// Fill out your copyright notice in the Description page of Project Settings.

#include "Pac_Man_Character.h"


// Sets default values
APac_Man_Character::APac_Man_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APac_Man_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APac_Man_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APac_Man_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

