// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost_Actor.h"
#include "Engine/GameEngine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pac_Man/Pac_Man_Player.h"
#include "Pac_Man/Path_Trigger.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
AGhost_Actor::AGhost_Actor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}
}
// Called when the game starts or when spawned
void AGhost_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (RootComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGhost_Actor::OnBeginOverlap);
	}
}

// Called every frame
void AGhost_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(Speed * Direction * DeltaTime);
}

void AGhost_Actor::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	APath_Trigger * Trigger = Cast<APath_Trigger>(OtherActor);

	if (Trigger)
	{
		DirectionToChange = Trigger->GetDirection(MissChance);
		FVector temp = Direction * Speed;
		float time = (100/ temp.Size()) *0.88f;


		
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AGhost_Actor::ChangeDirection, time);
	}

	APac_Man_Player * PacMan = Cast<APac_Man_Player>(OtherActor);

	if (PacMan)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pierde"));
		PacMan->EndGame();
	}
}


void AGhost_Actor::ChangeDirection()
{
	Direction = DirectionToChange;
}

