#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

class UStaticMeshComponent;
class USoundBase;
struct FTimerHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonActivated, int32, ButtonIndex);

UCLASS()
class SPLITBEAN_API ADoorButton : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorButton();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	void Activate();
	void Deactivate();
	void OnDeactivateButtonTimerTimeout();
	
	UFUNCTION(Server, Reliable)
	void ServerActivate();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlaySound();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonMesh;
	UPROPERTY(EditAnywhere)
	float DeactivateDelay = 1.0f;
	UPROPERTY(EditAnywhere)
	USoundBase* ActivationSound;
	UPROPERTY(EditAnywhere)
	bool IsSequenceButton = false;
	FTimerHandle DeactivateButtonTimer;
	UPROPERTY(Replicated)
	bool IsActivated = false;
	
	UPROPERTY(BlueprintAssignable)
	FOnButtonActivated OnButtonActivated;
	UPROPERTY(EditAnywhere)
	int32 ButtonIndex = 0;
};
