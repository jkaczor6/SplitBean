#include "DoorButton.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ADoorButton::ADoorButton()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	SetRootComponent(ButtonMesh);
}

void ADoorButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoorButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorButton::Activate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Activated button"));
	IsActivated = true;
	UGameplayStatics::PlaySound2D(GetWorld(), ActivationSound);
	GetWorldTimerManager().SetTimer(DeactivateButtonTimer, this, &ADoorButton::OnDeactivateButtonTimerTimeout, 1.0f, false, DeactivateDelay);
}

void ADoorButton::Deactivate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Deactivated button"));
	IsActivated = false;
}

void ADoorButton::OnDeactivateButtonTimerTimeout()
{
	Deactivate();
}

