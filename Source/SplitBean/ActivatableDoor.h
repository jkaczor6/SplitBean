#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivatableDoor.generated.h"

class UStaticMeshComponent;
class ADoorButton;

UCLASS()
class SPLITBEAN_API AActivatableDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	AActivatableDoor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(EditAnywhere)
	TArray<ADoorButton*> Activators;
	int32 ActiveActivators = 0;
};
