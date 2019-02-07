// Fill out your copyright notice in the Description page of Project Settings.

#include "Pac_Man_Player.h"
#include "Pac_ManGameModeBase.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Pac_Man_MovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Path_Trigger.h"
#include "Ghost_Actor.h"
#include "Collectible.h"

// Sets default values
APac_Man_Player::APac_Man_Player()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsHunting = false;

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

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComponent = CreateDefaultSubobject<UPac_Man_MovementComponent>(TEXT("CustomMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	Score = 0;
}

// Called when the game starts or when spawned
void APac_Man_Player::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APac_Man_Player::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APac_Man_Player::OnEndOverlap);
}

// Called every frame
void APac_Man_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
	{
		MovementComponent->AddInputVector(Direction*Speed);
	}
}

// Called to bind functionality to input
void APac_Man_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APac_Man_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APac_Man_Player::MoveRight);
}

void APac_Man_Player::MoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		Direction = GetActorForwardVector() * AxisValue;
	}
}

void APac_Man_Player::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		Direction = GetActorRightVector() * AxisValue;
	}
}

void APac_Man_Player::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACollectible* Collectible = Cast<ACollectible>(OtherActor);

	if (Collectible)
	{
		if (Collectible->Type == ECollectibleTypeEnum::CTE_Coin)
			++Score;
		else if (Collectible->Type == ECollectibleTypeEnum::CTE_CornerPowerUp || Collectible->Type == ECollectibleTypeEnum::CTE_HunterPowerUp)
		{

			APac_ManGameModeBase * GameMode = (APac_ManGameModeBase*)GetWorld()->GetAuthGameMode();



			if (Collectible->Type == ECollectibleTypeEnum::CTE_CornerPowerUp)
			{
				GameMode->SendEffectToGhosts(Collectible->Type, CornerPowerUpAffectionDuration);
			}

			if (Collectible->Type == ECollectibleTypeEnum::CTE_HunterPowerUp) 
			{
				bIsHunting = true;
				GameMode->SendEffectToGhosts(Collectible->Type, HunterPowerUpAffectionDuration);
				GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &APac_Man_Player::HuntFalse, HunterPowerUpAffectionDuration);
			}
		}
			
		Collectible->Destroy();
		return;
	}
}

void APac_Man_Player::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APath_Trigger* PathTrigger = Cast<APath_Trigger>(OtherActor);

	if (PathTrigger)
	{
		PathTrigger->UpdatePath(0, Direction);
		return;
	}
}

void APac_Man_Player::HuntFalse()
{
	bIsHunting = false;
}

void APac_Man_Player::AddScore(int ScoreToAdd)
{
	Score += ScoreToAdd;
}

bool APac_Man_Player::IsHunting()
{
	return bIsHunting;
}

FVector APac_Man_Player::GetMovementDirection()
{
	return Direction;
}

UPawnMovementComponent * APac_Man_Player::GetMovementComponent() const
{
	return MovementComponent;
}
