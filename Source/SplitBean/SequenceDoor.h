#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SequenceDoor.generated.h"

class UStaticMeshComponent;
class ADoorButton;
class ASequenceDisplay;
class USoundBase;

UCLASS()
class SPLITBEAN_API ASequenceDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASequenceDoor();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlaySound(USoundBase* SFX);
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere)
	TArray<ADoorButton*> Buttons;
	UPROPERTY(EditAnywhere)
	ASequenceDisplay* Display;
	UPROPERTY(EditAnywhere)
	USoundBase* SuccessSFX;
	UPROPERTY(EditAnywhere)
	USoundBase* FailSFX;
	UPROPERTY(Replicated, VisibleAnywhere)
	TArray<int32> CorrectSequence;
	
	
private:
	TArray<int32> PlayerSequence;
	
	UFUNCTION()
	void OnButtonPressed(int32 Index);
	
	void ShuffleSequence();
	void CheckSequence();
	void ResetPlayerSequence();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnFail();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnSuccess();
};
