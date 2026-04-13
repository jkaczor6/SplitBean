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
	if (ASplitBeanPlayerCharacter* Player = Cast<ASplitBeanPlayerCharacter>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(TeleportDelay, this, &ATeleporter::OnTeleportDelayTimerTimeout, 1.0f, false, 2.0f);
	}
}


void ATeleporter::OnTeleportDelayTimerTimeout()
{
	FVector TeleportLocation = ComponentToTeleportTo->GetActorLocation();
	
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(TeleportLocation);
}

