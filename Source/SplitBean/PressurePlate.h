#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AMovingActor;

UCLASS()
class SPLITBEAN_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	APressurePlate();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PressurePlateMesh;
	UPROPERTY(EditAnywhere)
	AMovingActor* MovingActor;
	
	bool IsTriggered = false;
	int32 ActivatorCount = 0;
};
