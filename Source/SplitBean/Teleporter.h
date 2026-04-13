#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

class UBoxComponent;
class USceneComponent;
struct FTimerHandle;

UCLASS()
class SPLITBEAN_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleporter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnTeleportDelayTimerTimeout();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere)
	AActor* ComponentToTeleportTo;
	
	FTimerHandle TeleportDelay;
};
