#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SequenceDisplay.generated.h"

class UPointLightComponent;
class UTextRenderComponent;
class ASequenceDoor;

UCLASS()
class SPLITBEAN_API ASequenceDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	ASequenceDisplay();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> ButtonColors;
	UPROPERTY(EditAnywhere)
	ASequenceDoor* SequenceDoor;
	
	void UpdateDisplay();
	
private:
	UPROPERTY(VisibleAnywhere)
	TArray<UPointLightComponent*> Lights;
	UPROPERTY(VisibleAnywhere)
	TArray<UTextRenderComponent*> Numbers;
};
