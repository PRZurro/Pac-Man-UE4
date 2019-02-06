// Fill out your copyright notice in the Description page of Project Settings.

#include "Pac_Man_Player.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/GameEngine.h"
#include "Components/StaticMeshComponent.h"
#include "Pac_Man_MovementComponent.h"
#include "Path_Trigger.h"
<<<<<<< HEAD
#include "Coin_Actor.h"
=======
#include "Coin.h"
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> 8d5a671... Transfered Ghost's Class from Pawn to actor
#include "Ghost_Actor.h"

// Sets default values
APac_Man_Player::APac_Man_Player()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bQuitGame = false;
}

// Called when the game starts or when spawned
void APac_Man_Player::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APac_Man_Player::OnEndOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this, &APac_Man_Player::OnHit);
}

// Called every frame
void APac_Man_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(Speed * Direction * DeltaTime,true);
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

void APac_Man_Player::EndGame()
{
	bQuitGame = true;
}

void APac_Man_Player::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	ACoin_Actor* Coin = Cast<ACoin_Actor>(OtherActor);

	if (Coin)
	{
		++Score;
		Destroy(Coin);

		return;
	}
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 8d5a671... Transfered Ghost's Class from Pawn to actor

	AGhost_Actor * Ghost = Cast<AGhost_Actor>(OtherActor);

	if(Ghost)
	{
		EndGame();
	}
}
>>>>>>> master

	APath_Trigger* PathTrigger = Cast<APath_Trigger>(OtherActor);

	if (PathTrigger)
	{
		PathTrigger->UpdatePath(0, Direction);
		return;
	}
}

void APac_Man_Player::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AGhost_Actor * Ghost = Cast<AGhost_Actor>(OtherActor);

	if (Ghost)
	{
		EndGame();
	}
}

FVector APac_Man_Player::GetMovementDirection()
{
	return Direction;
}
