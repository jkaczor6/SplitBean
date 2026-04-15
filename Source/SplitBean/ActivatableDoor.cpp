#include "ActivatableDoor.h"
#include "DoorButton.h"

AActivatableDoor::AActivatableDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);
}

void AActivatableDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActivatableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActiveActivators = 0;
	
	for (ADoorButton* DoorButton : Activators)
	{
		if (DoorButton->IsActivated)
		{
			ActiveActivators++;
		}
	}
	
	if (ActiveActivators >= Activators.Num())
	{
		Destroy();
	}
}

