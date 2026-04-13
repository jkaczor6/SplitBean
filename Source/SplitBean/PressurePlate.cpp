#include "PressurePlate.h"

#include "MovingActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SplitBeanPlayerCharacter.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	
	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Mesh"));
	PressurePlateMesh->SetupAttachment(RootComponent);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASplitBeanPlayerCharacter* Player = Cast<ASplitBeanPlayerCharacter>(OtherActor))
	{
		ActivatorCount++;
		
		MovingActor->SetShouldMove(true);
	}
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ActivatorCount--;
	if (ActivatorCount == 0)
	{
		MovingActor->SetShouldMove(false);
	}
}

