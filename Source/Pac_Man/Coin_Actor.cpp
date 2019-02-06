// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin_Actor.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACoin_Actor::ACoin_Actor()
{
	// Create and position a mesh component so we can see where our sphere is
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereVisual->SetWorldScale3D(FVector(1));
	}
}

// Called when the game starts or when spawned
void ACoin_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

