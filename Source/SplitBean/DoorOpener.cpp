#include "DoorOpener.h"
#include "SplitBeanPlayerCharacter.h"
#include "Components/BoxComponent.h"

ADoorOpener::ADoorOpener()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
}

void ADoorOpener::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoorOpener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	BoxComp->GetOverlappingActors(OverlappingActors, ASplitBeanPlayerCharacter::StaticClass());
	
	if (OverlappingActors.Num() == ActorsNeededToActivate)
	{
		Door->Destroy();
		Destroy();
	}
}
