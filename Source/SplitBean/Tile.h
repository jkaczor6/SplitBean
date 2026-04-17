#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPLITBEAN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TileMesh;
	
	UPROPERTY(EditAnywhere)
	bool IsSafe = false;
	
	UPROPERTY()
	AActor* SpawnPoint;
	
	UFUNCTION()
	void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
