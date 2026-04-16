#include "DoorButton.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ADoorButton::ADoorButton()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
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

void ADoorButton::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADoorButton, IsActivated);
}

void ADoorButton::Activate()
{
	if (!HasAuthority())
	{
		ServerActivate();
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"));
	IsActivated = true;
	if (IsSequenceButton) OnButtonActivated.Broadcast(ButtonIndex);
	MulticastPlaySound();
	GetWorldTimerManager().SetTimer(DeactivateButtonTimer, this, &ADoorButton::OnDeactivateButtonTimerTimeout, 1.0f, false, DeactivateDelay);
}

void ADoorButton::Deactivate()
{
	IsActivated = false;
}

void ADoorButton::OnDeactivateButtonTimerTimeout()
{
	Deactivate();
}

void ADoorButton::MulticastPlaySound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ActivationSound);
}

void ADoorButton::ServerActivate_Implementation()
{
	Activate();
}

