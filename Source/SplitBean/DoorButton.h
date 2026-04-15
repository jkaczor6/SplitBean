#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

class UStaticMeshComponent;
struct FTimerHandle;

UCLASS()
class SPLITBEAN_API ADoorButton : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorButton();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Activate();
	void Deactivate();
	void OnDeactivateButtonTimerTimeout();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonMesh;
	UPROPERTY(EditAnywhere)
	float DeactivateDelay = 1.0f;
	
	FTimerHandle DeactivateButtonTimer;
	bool IsActivated = false;
};
