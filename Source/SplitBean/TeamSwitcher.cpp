#include "TeamSwitcher.h"
#include "Components/BoxComponent.h"
#include "SplitBeanPlayerCharacter.h"

ATeamSwitcher::ATeamSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
}

void ATeamSwitcher::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeamSwitcher::OnBeginOverlap);
}

void ATeamSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeamSwitcher::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASplitBeanPlayerCharacter* Player = Cast<ASplitBeanPlayerCharacter>(OtherActor))
	{
		Player->SwitchTeams(TeamIndexToSwitch);
	}
}

