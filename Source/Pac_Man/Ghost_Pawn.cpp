// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost_Pawn.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pac_Man/Pac_Man_Player.h"
#include "Pac_Man/Path_Trigger.h"
#include "Ghost_PawnMovementComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AGhost_Pawn::AGhost_Pawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	if (SphereComponent)
	{
		RootComponent = SphereComponent;
		SphereComponent->InitSphereRadius(40.0f);
		SphereComponent->SetCollisionProfileName(TEXT("Character"));
	}
	
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	/*GhostMovementComponent = CreateDefaultSubobject<UGhost_PawnMovementComponent>(TEXT("CustomMovementComponent"));
	GhostMovementComponent->UpdatedComponent = RootComponent;*/
}

// Called when the game starts or when spawned
void AGhost_Pawn::BeginPlay()
{
	Super::BeginPlay();

	/*if(SphereComponent)
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGhost_Pawn::OnBeginOverlap);*/
}

// Called every frame
void AGhost_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (GhostMovementComponent)
	//{
	//	GhostMovementComponent->AddInputVector(Direction * Speed); //Deltatime is multiplied in the Movement Component Tick
	//}
}

// Called to bind functionality to input
void AGhost_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGhost_Pawn::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	APath_Trigger * Trigger = Cast<APath_Trigger>(OtherActor);

	if (Trigger)
	{
		Trigger->GetDirection(MissChance);
	}

	APac_Man_Player * PacMan = Cast<APac_Man_Player>(OtherActor);

	if (PacMan)
	{
		PacMan->EndGame();
	}
}
