#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorOpener.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SPLITBEAN_API ADoorOpener : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorOpener();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere)
	AActor* Door;
	UPROPERTY(EditAnywhere)
	int32 ActorsNeededToActivate;
};
