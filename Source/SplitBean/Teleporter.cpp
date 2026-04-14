#include "Teleporter.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "SplitBeanPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!HasAuthority()) return;
	if (ASplitBeanPlayerCharacter* Player = Cast<ASplitBeanPlayerCharacter>(OtherActor))
	{
		OverlappingPlayer = Player;
		
		GetWorldTimerManager().SetTimer(TeleportDelayTimer, this, &ATeleporter::OnTeleportDelayTimerTimeout, 1.0f, false, TeleportDelay);
	}
}


void ATeleporter::OnTeleportDelayTimerTimeout()
{
	if(!HasAuthority()) return;
	if (OverlappingPlayer)
	{
		FVector TeleportLocation = ComponentToTeleportTo->GetActorLocation();
		OverlappingPlayer->SetActorLocation(TeleportLocation);
	}
	
	Destroy();
}

