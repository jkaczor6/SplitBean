#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeamSwitcher.generated.h"

class UBoxComponent;

UCLASS()
class SPLITBEAN_API ATeamSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeamSwitcher();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere)
	int32 TeamIndexToSwitch = 0;
};
