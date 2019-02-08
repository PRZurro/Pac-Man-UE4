// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost_Actor.h"
#include "Engine/GameEngine.h"
#include "Engine/GameEngine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pac_Man/Pac_Man_Player.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Pac_Man/Path_Trigger.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
AGhost_Actor::AGhost_Actor()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanEat = true;

	// Our root component will be a sphere that reacts to physics
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0);
	SphereComponent->SetCollisionProfileName(TEXT("Actor"));

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


	StartPosition = GetActorLocation();
	StartDirection = Direction;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGhost_Actor::OnBeginOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this, &AGhost_Actor::OnHit);

	UMaterialInterface *  Material = SphereVisual->GetMaterial(0);
	Materialnstance = UMaterialInstanceDynamic::Create(Material, SphereVisual);
	StartingColor = Materialnstance->K2_GetVectorParameterValue(TEXT("BaseColor"));
	SphereVisual->SetMaterial(0, Materialnstance);
}	

// Called every frame
void AGhost_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(Speed * Direction * DeltaTime,false);
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
}

void AGhost_Actor::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	APac_Man_Player * PacMan = Cast<APac_Man_Player>(OtherActor);

	if (PacMan)
	{
	
		if (PacMan->IsHunting())
		{
			Destroy();
			PacMan->AddScore(200);
		}

		if (bCanEat)
		{
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
		else
		{
			SetActorLocation(StartPosition);
			DirectionToChange = Direction = StartDirection;
		}
	}
}

void AGhost_Actor::ChangeDirection()
{
	Direction = DirectionToChange;
}


void AGhost_Actor::Affect(ECollectibleTypeEnum EffectType)
{

	if (EffectType == ECollectibleTypeEnum::CTE_CornerPowerUp)
	{
		bCanEat = false;
	}
	else if (EffectType == ECollectibleTypeEnum::CTE_HunterPowerUp)
	{
		bCanEat = false;
		Materialnstance->SetVectorParameterValue("BaseColor", FrightenedColor);
	}
}

void AGhost_Actor::ResetEffectsState()
{
	bCanEat = true;
	Materialnstance->SetVectorParameterValue("BaseColor", StartingColor);
	//Reset material
}

