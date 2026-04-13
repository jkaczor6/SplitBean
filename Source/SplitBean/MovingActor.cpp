#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartingLocation = GetActorLocation();
	SetShouldMove(false);
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentLocation = GetActorLocation();
	ReachedTarget = CurrentLocation.Equals(TargetLocation);
	
	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;
		
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		
		SetActorLocation(NewLocation);
	}
}

bool AMovingActor::GetShouldMove()
{
	return ShouldMove;
}

void AMovingActor::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
	
	if (ShouldMove)
	{
		TargetLocation = StartingLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartingLocation;		
	}
}

