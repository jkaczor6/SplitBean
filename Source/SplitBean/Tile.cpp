#include "Tile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	SetRootComponent(TileMesh);
	TileMesh->SetCollisionProfileName(TEXT("OverlapAll"));

	TileMesh->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnPlayerEntered);
}

void ATile::OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	if (!OtherActor || !OtherActor->IsA<ACharacter>()) return;
	if (IsSafe) return;
	
	if (SpawnPoint)
	{
		OtherActor->SetActorLocation(SpawnPoint->GetActorLocation());
	}
}

